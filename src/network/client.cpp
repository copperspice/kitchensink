/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "client.h"
#include "connection.h"
#include "peermanager.h"

#include <QAbstractSocket>
#include <QList>
#include <QString>

Client::Client()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(server.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, &PeerManager::newConnection, this, &Client::newConnection);
    QObject::connect(&server,     &Server::newConnection,      this, &Client::newConnection);
}

void Client::sendMessage(const QString &message)
{
   if (message.isEmpty()) {
      return;
   }

   QList<Connection *> connections = peers.values();
   for (Connection *connection : connections) {
        connection->sendMessage(message);
   }
}

QString Client::nickName() const
{
   return QString(peerManager->userName()) + '@' + QHostInfo::localHostName()
           + "  Port: " + QString::number(server.serverPort());
}

bool Client::hasConnection(const QHostAddress &senderIp, int senderPort) const
{
    if (senderPort == -1) {
        return peers.contains(senderIp);
    }

    if (! peers.contains(senderIp)) {
        return false;
    }

    QList<Connection *> connections = peers.values(senderIp);
    for (Connection *connection : connections) {
        if (connection->peerPort() == senderPort) {
            return true;
        }
    }

    return false;
}

void Client::newConnection(Connection *connection)
{
    connection->setGreetingMessage(peerManager->userName());

    connect(connection, &Connection::error,        this, &Client::connectionError);
    connect(connection, &Connection::disconnected, this, &Client::disconnected);
    connect(connection, &Connection::readyForUse,  this, &Client::readyForUse);
}

void Client::readyForUse()
{
    Connection *connection = qobject_cast<Connection *>(sender());

    if (! connection || hasConnection(connection->peerAddress(), connection->peerPort())) {
        return;
    }

    connect(connection, &Connection::newMessage, this, &Client::newMessage);

    peers.insert(connection->peerAddress(), connection);
    QString nick = connection->name();

    if (! nick.isEmpty()) {
        emit newParticipant(nick);
    }
}

void Client::disconnected()
{
   if (Connection *connection = qobject_cast<Connection *>(sender())) {
      removeConnection(connection);
   }
}

void Client::connectionError(QAbstractSocket::SocketError /* socketError */)
{
    if (Connection *connection = qobject_cast<Connection *>(sender())) {
        removeConnection(connection);
    }
}

void Client::removeConnection(Connection *connection)
{
    if (peers.contains(connection->peerAddress())) {
        peers.remove(connection->peerAddress());

        QString nick = connection->name();
        if (! nick.isEmpty()) {
            emit participantLeft(nick);
        }
    }

    connection->deleteLater();
}
