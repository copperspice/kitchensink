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

#ifndef SSL_CERT_H
#define SSL_CERT_H

#ifdef QT_SSL
#include "ui_ssl_cert.h"

#include <QDialog>
#include <QList>
#include <QSslCertificate>
#include <QWidget>

class Ssl_Cert : public QDialog
{
   CS_OBJECT(Ssl_Cert)

   public:
      Ssl_Cert(QWidget *parent = nullptr);
      ~Ssl_Cert();

      void setCertificateChain(const QList<QSslCertificate> &chain);

   private:
      void updateCertificateInfo(int index);

      Ui::Ssl_Cert *ui;
      QList<QSslCertificate> chain;
};

#endif

#endif
