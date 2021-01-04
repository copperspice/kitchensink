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
#include "ssl_client.h"

#include "ui_ssl_error.h"

#include <QLineEdit>
#include <QMessageBox>
#include <QStyle>
#include <QSslCipher>
#include <QScrollBar>
#include <QToolButton>

Ssl_Client::Ssl_Client(QWidget *parent)
    : QWidget(parent), ui(new Ui::Ssl_Client), socket(0), padLock(0), executingDialog(false)
{
    ui->setupUi(this);

    ui->hostNameEdit->setSelection(0, ui->hostNameEdit->text().size());
    ui->sessionOutput->setHtml(tr("&lt;not connected&gt;"));

    connect(ui->hostNameEdit,  &QLineEdit::textChanged, this, &Ssl_Client::updateEnabledState);
    connect(ui->connectButton, &QPushButton::clicked,   this, &Ssl_Client::secureConnect);
    connect(ui->sendButton,    &QPushButton::clicked,   this, &Ssl_Client::sendData);
}

Ssl_Client::~Ssl_Client()
{
}

void Ssl_Client::updateEnabledState()
{
    bool unconnected = !socket || socket->state() == QAbstractSocket::UnconnectedState;

    ui->hostNameEdit->setReadOnly(!unconnected);
    ui->hostNameEdit->setFocusPolicy(unconnected ? Qt::StrongFocus : Qt::NoFocus);

    ui->hostNameLabel->setEnabled(unconnected);
    ui->portBox->setEnabled(unconnected);
    ui->portLabel->setEnabled(unconnected);
    ui->connectButton->setEnabled(unconnected && !ui->hostNameEdit->text().isEmpty());

    bool connected = socket && socket->state() == QAbstractSocket::ConnectedState;
    ui->sessionOutput->setEnabled(connected);
    ui->sessionInput->setEnabled(connected);
    ui->sessionInputLabel->setEnabled(connected);
    ui->sendButton->setEnabled(connected);
}

void Ssl_Client::secureConnect()
{
    ui->cipherLabel->setText(tr("Loading, please wait..."));

    if (! socket) {
        socket = new QSslSocket(this);

        connect(socket, &QSslSocket::stateChanged, this, &Ssl_Client::socketStateChanged);
        connect(socket, &QSslSocket::encrypted,    this, &Ssl_Client::socketEncrypted);
        connect(socket, &QSslSocket::error,        this, &Ssl_Client::socketError);
        connect(socket, &QSslSocket::sslErrors,    this, &Ssl_Client::sslErrors);
        connect(socket, &QSslSocket::readyRead,    this, &Ssl_Client::socketReadyRead);
    }

    socket->connectToHostEncrypted(ui->hostNameEdit->text(), ui->portBox->value());
    updateEnabledState();
}

void Ssl_Client::socketStateChanged(QAbstractSocket::SocketState state)
{
    if (executingDialog) {
        return;
    }

    updateEnabledState();

    if (state == QAbstractSocket::UnconnectedState) {
        ui->hostNameEdit->setPalette(QPalette());
        ui->hostNameEdit->setFocus();
        ui->cipherLabel->setText(tr("<none>"));

        if (padLock) {
            padLock->hide();
        }
    }
}

void Ssl_Client::socketEncrypted()
{
    if (! socket)  {
        return;                 // might have disconnected already
    }

    ui->sessionOutput->clear();
    ui->sessionInput->setFocus();

    QPalette palette;
    palette.setColor(QPalette::Base, QColor(255, 255, 192));
    ui->hostNameEdit->setPalette(palette);

    QSslCipher ciph = socket->sessionCipher();
    QString cipher = QString("%1, %2 (%3/%4)").formatArg(ciph.authenticationMethod())
                     .formatArg (ciph.name()).formatArg(ciph.usedBits()).formatArg(ciph.supportedBits());;

    ui->cipherLabel->setText(cipher);

    if (! padLock) {
        padLock = new QToolButton;
        padLock->setIcon(QIcon(":/resources/network/encrypted.png"));

        padLock->setCursor(Qt::ArrowCursor);
        padLock->setToolTip(tr("Display encryption details."));

        int extent = ui->hostNameEdit->height() - 2;
        padLock->resize(extent, extent);
        padLock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

        QHBoxLayout *layout = new QHBoxLayout(ui->hostNameEdit);
        layout->setMargin(ui->hostNameEdit->style()->pixelMetric(QStyle::PM_DefaultFrameWidth));
        layout->setSpacing(0);
        layout->addStretch();
        layout->addWidget(padLock);

        ui->hostNameEdit->setLayout(layout);

        connect(padLock, &QToolButton::clicked, this, &Ssl_Client::displayCertificateInfo);

    } else {
        padLock->show();
    }
}

void Ssl_Client::socketReadyRead()
{
    appendString(QString::fromUtf8(socket->readAll()));
}

void Ssl_Client::sendData()
{
    QString input = ui->sessionInput->text();
    appendString(input + '\n');
    socket->write(input.toUtf8() + "\r\n");

    ui->sessionInput->clear();
}

void Ssl_Client::socketError(QAbstractSocket::SocketError)
{
    ui->cipherLabel->setText(tr("<none>"));
    QMessageBox::critical(this, tr("Connection error"), socket->errorString());
}

void Ssl_Client::sslErrors(const QList<QSslError> &errors)
{
    ui->cipherLabel->setText(tr("<none>"));

    QDialog errorDialog(this);

    Ui::Ssl_Error ui_error;
    ui_error.setupUi(&errorDialog);

    connect(ui_error.certificateChainButton, &QPushButton::clicked, this, &Ssl_Client::displayCertificateInfo);

    for (const QSslError &error : errors) {
        ui_error.sslErrorList->addItem(error.errorString());
    }

    executingDialog = true;
    if (errorDialog.exec() == QDialog::Accepted) {
        socket->ignoreSslErrors();
    }

    executingDialog = false;

    // did the socket state change?
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socketStateChanged(socket->state());
    }
}

void Ssl_Client::displayCertificateInfo()
{
    Ssl_Cert *info = new Ssl_Cert(this);

    info->setCertificateChain(socket->peerCertificateChain());
    info->exec();
    info->deleteLater();
}

void Ssl_Client::appendString(const QString &line)
{
    QTextCursor cursor(ui->sessionOutput->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(line);

    ui->sessionOutput->verticalScrollBar()->setValue(ui->sessionOutput->verticalScrollBar()->maximum());
}

#endif
