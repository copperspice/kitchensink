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

#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

class Client;
class Connection;

class PeerManager : public QObject
{
   CS_OBJECT(PeerManager)

   public:
      PeerManager(Client *client);

      void setServerPort(int port);
      QByteArray userName() const;
      void startBroadcasting();
      bool isLocalHostAddress(const QHostAddress &address);

      CS_SIGNAL_1(Public, void newConnection(Connection *connection))
      CS_SIGNAL_2(newConnection, connection)

   private:
      void updateAddresses();
      void sendBroadcastDatagram();
      void readBroadcastDatagram();

      Client *client;
      QList<QHostAddress> broadcastAddresses;
      QList<QHostAddress> ipAddresses;
      QUdpSocket broadcastSocket;
      QTimer broadcastTimer;
      QByteArray username;
      int serverPort;
};

#endif
