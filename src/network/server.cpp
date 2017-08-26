/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include <QtNetwork>

#include "connection.h"
#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
   Connection *connection = new Connection(this);
   connection->setSocketDescriptor(socketDescriptor);

   emit newConnection(connection);
}
