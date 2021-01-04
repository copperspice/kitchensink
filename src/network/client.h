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

#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

#include <QHostAddress>
#include <QMultiHash>
#include <qstringfwd.h>

class QAbstractSocket;
class PeerManager;

class Client : public QObject
{
   CS_OBJECT(Client)

   public:
      Client();

      void sendMessage(const QString &message);
      QString nickName() const;
      bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

      CS_SIGNAL_1(Public, void newMessage(const QString &from, const QString &message))
      CS_SIGNAL_2(newMessage, from, message)

      CS_SIGNAL_1(Public, void newParticipant(const QString &nick))
      CS_SIGNAL_2(newParticipant, nick)

      CS_SIGNAL_1(Public, void participantLeft(const QString &nick))
      CS_SIGNAL_2(participantLeft, nick)

   private:
      void removeConnection(Connection *connection);

      // slot declarations
      void newConnection(Connection *connection);
      void connectionError(QAbstractSocket::SocketError socketError);
      void disconnected();
      void readyForUse();

      PeerManager *peerManager;
      Server server;
      QMultiHash<QHostAddress, Connection *> peers;
};

#endif
