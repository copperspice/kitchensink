/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
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
