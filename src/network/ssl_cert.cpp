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

#ifdef QT_SSL

#include "ssl_cert.h"

#include <QComboBox>
#include <QStringList>

Ssl_Cert::Ssl_Cert(QWidget *parent)
    : QDialog(parent), ui(new Ui::Ssl_Cert)
{
   ui->setupUi(this);

   connect(ui->closePB, &QPushButton::clicked, this, &Ssl_Cert::accept);

   // static_cast is required since this signal is overloaded
   connect(ui->certificationPathView, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                  this, &Ssl_Cert::updateCertificateInfo);
}

Ssl_Cert::~Ssl_Cert()
{
}

void Ssl_Cert::setCertificateChain(const QList<QSslCertificate> &chain)
{
    this->chain = chain;

    ui->certificationPathView->clear();

    for (int i = 0; i < chain.size(); ++i) {
        const QSslCertificate &cert = chain.at(i);

        ui->certificationPathView->addItem(tr("%1%2 (%3)").formatArg(! i ? QString() : tr("Issued by: "))
                          .formatArg(cert.subjectInfo(QSslCertificate::Organization).join(" "))
                          .formatArg(cert.subjectInfo(QSslCertificate::CommonName).join(" ")));
    }

    ui->certificationPathView->setCurrentIndex(0);
}

void Ssl_Cert::updateCertificateInfo(int index)
{
    ui->certificateInfoView->clear();

    if (index >= 0 && index < chain.size()) {
        const QSslCertificate &cert = chain.at(index);
        QStringList lines;

        lines << tr("Organization: %1").formatArg(cert.subjectInfo(QSslCertificate::Organization).join(" "))
              << tr("Subunit: %1").formatArg(cert.subjectInfo(QSslCertificate::OrganizationalUnitName).join(" "))
              << tr("Country: %1").formatArg(cert.subjectInfo(QSslCertificate::CountryName).join(" "))
              << tr("Locality: %1").formatArg(cert.subjectInfo(QSslCertificate::LocalityName).join(" "))
              << tr("State/Province: %1").formatArg(cert.subjectInfo(QSslCertificate::StateOrProvinceName).join(" "))
              << tr("Common Name: %1").formatArg(cert.subjectInfo(QSslCertificate::CommonName).join(" "))
              << QString()

              << tr("Issuer Organization: %1").formatArg(cert.issuerInfo(QSslCertificate::Organization).join(" "))
              << tr("Issuer Unit Name: %1").formatArg(cert.issuerInfo(QSslCertificate::OrganizationalUnitName).join(" "))
              << tr("Issuer Country: %1").formatArg(cert.issuerInfo(QSslCertificate::CountryName).join(" "))
              << tr("Issuer Locality: %1").formatArg(cert.issuerInfo(QSslCertificate::LocalityName).join(" "))
              << tr("Issuer State/Province: %1").formatArg(cert.issuerInfo(QSslCertificate::StateOrProvinceName).join(" "))
              << tr("Issuer Common Name: %1").formatArg(cert.issuerInfo(QSslCertificate::CommonName).join(" "));

        for (QString line : lines) {
            ui->certificateInfoView->addItem(line);
        }

    } else {
        ui->certificateInfoView->clear();
    }
}

#endif
