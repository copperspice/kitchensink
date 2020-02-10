/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
