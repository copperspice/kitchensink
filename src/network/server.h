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

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Connection;

class Server : public QTcpServer
{
   CS_OBJECT(Server)

 public:
   Server(QObject *parent = nullptr);

   CS_SIGNAL_1(Public, void newConnection(Connection *connection))
   CS_SIGNAL_2(newConnection, connection)

 protected:
   void incomingConnection(qintptr socketDescriptor) override;

};

#endif
