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

#ifndef QT_NO_OPENSSL

#include "ssl_cert.h"

#include <QComboBox>

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

        ui->certificationPathView->addItem(tr("%1%2 (%3)").arg(!i ? QString() : tr("Issued by: "))
                          .arg(cert.subjectInfo(QSslCertificate::Organization).join(QString(" ")))
                          .arg(cert.subjectInfo(QSslCertificate::CommonName).join(QString(" "))));
    }

    ui->certificationPathView->setCurrentIndex(0);
}

void Ssl_Cert::updateCertificateInfo(int index)
{
    ui->certificateInfoView->clear();

    if (index >= 0 && index < chain.size()) {
        const QSslCertificate &cert = chain.at(index);
        QStringList lines;

        lines << tr("Organization: %1").arg(cert.subjectInfo(QSslCertificate::Organization).join(QString(" ")))
              << tr("Subunit: %1").arg(cert.subjectInfo(QSslCertificate::OrganizationalUnitName).join(QString(" ")))
              << tr("Country: %1").arg(cert.subjectInfo(QSslCertificate::CountryName).join(QString(" ")))
              << tr("Locality: %1").arg(cert.subjectInfo(QSslCertificate::LocalityName).join(QString(" ")))
              << tr("State/Province: %1").arg(cert.subjectInfo(QSslCertificate::StateOrProvinceName).join(QString(" ")))
              << tr("Common Name: %1").arg(cert.subjectInfo(QSslCertificate::CommonName).join(QString(" ")))
              << QString()
              << tr("Issuer Organization: %1").arg(cert.issuerInfo(QSslCertificate::Organization).join(QString(" ")))
              << tr("Issuer Unit Name: %1").arg(cert.issuerInfo(QSslCertificate::OrganizationalUnitName).join(QString(" ")))
              << tr("Issuer Country: %1").arg(cert.issuerInfo(QSslCertificate::CountryName).join(QString(" ")))
              << tr("Issuer Locality: %1").arg(cert.issuerInfo(QSslCertificate::LocalityName).join(QString(" ")))
              << tr("Issuer State/Province: %1").arg(cert.issuerInfo(QSslCertificate::StateOrProvinceName).join(QString(" ")))
              << tr("Issuer Common Name: %1").arg(cert.issuerInfo(QSslCertificate::CommonName).join(QString(" ")));

        for (QString line : lines) {
            ui->certificateInfoView->addItem(line);
        }

    } else {
        ui->certificateInfoView->clear();
    }
}

#endif
