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

#include "chat_dialog.h"

#include <QMessageBox>
#include <QTimer>
#include <QTextTable>
#include <QScrollBar>
#include <QString>
#include <QWidget>

Chat_Dialog::Chat_Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Chat_Dialog)
{
    ui->setupUi(this);

    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->textEdit->setReadOnly(true);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);

    connect(ui->lineEdit, &QLineEdit::returnPressed,  this, &Chat_Dialog::returnPressed);
    connect(ui->lineEdit, &QLineEdit::returnPressed,  this, &Chat_Dialog::returnPressed);

    connect(&client, &Client::newMessage,      this, &Chat_Dialog::appendMessage);
    connect(&client, &Client::newParticipant,  this, &Chat_Dialog::newParticipant);
    connect(&client, &Client::participantLeft, this, &Chat_Dialog::participantLeft);

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);

    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}

void Chat_Dialog::appendMessage(const QString &from, const QString &message)
{
   if (from.isEmpty() || message.isEmpty()) {
      return;
   }

   QTextCursor cursor(ui->textEdit->textCursor());
   cursor.movePosition(QTextCursor::End);

   QTextTable *table = cursor.insertTable(1, 2, tableFormat);
   table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
   table->cellAt(0, 1).firstCursorPosition().insertText(message);

   QScrollBar *bar = ui->textEdit->verticalScrollBar();
   bar->setValue(bar->maximum());
}

void Chat_Dialog::returnPressed()
{
    QString text = ui->lineEdit->text();

    if (text.isEmpty()) {
        return;
    }

    if (text.startsWith(QChar('/'))) {
        QColor color = ui->textEdit->textColor();

        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("Unknown command: %1").formatArg(text.left(text.indexOf(' '))));
        ui->textEdit->setTextColor(color);

    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    ui->lineEdit->clear();
}

void Chat_Dialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty()) {
        return;
    }

    QColor color = ui->textEdit->textColor();
    ui->textEdit->setTextColor(Qt::gray);
    ui->textEdit->append(tr("* %1 has joined").formatArg(nick));
    ui->textEdit->setTextColor(color);
    ui->listWidget->addItem(nick);
}

void Chat_Dialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty()) {
        return;
    }

    QList<QListWidgetItem *> items = ui->listWidget->findItems(nick, Qt::MatchExactly);

    if (items.isEmpty()) {
        return;
    }

    delete items.at(0);

    QColor color = ui->textEdit->textColor();
    ui->textEdit->setTextColor(Qt::gray);
    ui->textEdit->append(tr("* %1 has left").formatArg(nick));
    ui->textEdit->setTextColor(color);
}

void Chat_Dialog::showInformation()
{
   if (ui->listWidget->count() == 1) {
       QMessageBox::information(this, tr("Chat Message"), tr("In order to use this feature you can start another copy of "
            " KitchenSink on your local network or simply open another chat window."));
   }
}


