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

#include <QHostAddress>
#include <QNetworkInterface>
#include <QProcess>
#include <QStringList>

static const qint32 BroadcastInterval = 2000;
static const unsigned broadcastPort   = 45000;

PeerManager::PeerManager(Client *client)
    : QObject(client)
{
    this->client = client;

    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";

    QStringList environment = QProcess::systemEnvironment();

    for (QString string : envVariables) {
        int index = environment.indexOf(QRegularExpression(string));

        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');

            if (stringList.size() == 2) {
                username = stringList.at(1).toUtf8();
                break;
            }
        }
    }

    if (username.isEmpty()) {
        username = "unknown";
    }

    updateAddresses();
    serverPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(&broadcastSocket, &QUdpSocket::readyRead, this, &PeerManager::readBroadcastDatagram);

    broadcastTimer.setInterval(BroadcastInterval);
    connect(&broadcastTimer, &QTimer::timeout,        this, &PeerManager::sendBroadcastDatagram);
}

void PeerManager::setServerPort(int port)
{
    serverPort = port;
}

QByteArray PeerManager::userName() const
{
    return username;
}

void PeerManager::startBroadcasting()
{
    broadcastTimer.start();
}

bool PeerManager::isLocalHostAddress(const QHostAddress &address)
{
    for (QHostAddress localAddress : ipAddresses) {
        if (address == localAddress) {
            return true;
        }
    }
    return false;
}

void PeerManager::sendBroadcastDatagram()
{
    QByteArray datagram(username);
    datagram.append('@');
    datagram.append(QByteArray::number(serverPort));

    bool validBroadcastAddresses = true;
    for (QHostAddress address : broadcastAddresses) {
        if (broadcastSocket.writeDatagram(datagram, address, broadcastPort) == -1) {
            validBroadcastAddresses = false;
       }
    }

    if (! validBroadcastAddresses) {
        updateAddresses();
    }
}

void PeerManager::readBroadcastDatagram()
{
    while (broadcastSocket.hasPendingDatagrams()) {
        QHostAddress senderIp;
        quint16 senderPort;

        QByteArray datagram;
        datagram.resize(broadcastSocket.pendingDatagramSize());

        if (broadcastSocket.readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1) {
            continue;
        }

        QList<QByteArray> list = datagram.split('@');
        if (list.size() != 2)  {
            continue;
        }

        int senderServerPort = list.at(1).toInt();
        if (isLocalHostAddress(senderIp) && senderServerPort == serverPort) {
            continue;
        }

        if (! client->hasConnection(senderIp)) {
            Connection *connection = new Connection(this);
            emit newConnection(connection);
            connection->connectToHost(senderIp, senderServerPort);
        }
    }
}

void PeerManager::updateAddresses()
{
    broadcastAddresses.clear();
    ipAddresses.clear();

    for (QNetworkInterface interface : QNetworkInterface::allInterfaces()) {
        for (QNetworkAddressEntry entry : interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();

            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost) {
                broadcastAddresses << broadcastAddress;
                ipAddresses << entry.ip();
            }
        }
    }
}
