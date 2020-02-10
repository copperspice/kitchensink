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

#ifndef SSL_CLIENT_H
#define SSL_CLIENT_H

#ifdef QT_SSL

#include "ui_ssl_client.h"

#include <QAbstractSocket>
#include <QSslSocket>
#include <QWidget>

class QSslSocket;
class QToolButton;

class Ssl_Client : public QWidget
{
   CS_OBJECT(Ssl_Client)

   public:
      Ssl_Client(QWidget *parent = nullptr);
      ~Ssl_Client();

   private:
       void appendString(const QString &line);

      // slot declarations
      void updateEnabledState();
      void secureConnect();
      void socketStateChanged(QAbstractSocket::SocketState state);
      void socketEncrypted();
      void socketReadyRead();
      void sendData();
      void socketError(QAbstractSocket::SocketError error);
      void sslErrors(const QList<QSslError> &errors);
      void displayCertificateInfo();

      Ui::Ssl_Client *ui;

      QSslSocket  *socket;
      QToolButton *padLock;
      bool executingDialog;
};

#endif

#endif
