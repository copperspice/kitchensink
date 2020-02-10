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

#ifndef CHAT_DIALOG_H
#define CHAT_DIALOG_H

#include "ui_chat_dialog.h"
#include "client.h"

#include <QDialog>
#include <qstringfwd.h>

class QTextTableFormat;

class Chat_Dialog : public QDialog
{
   CS_OBJECT(Chat_Dialog)

   public:
      Chat_Dialog(QWidget *parent = nullptr);
      void appendMessage(const QString &from, const QString &message);

   private:
      void returnPressed();
      void newParticipant(const QString &nick);
      void participantLeft(const QString &nick);

      CS_SLOT_1(Private, void showInformation())
      CS_SLOT_2(showInformation)

      Ui::Chat_Dialog *ui;

      Client client;
      QString myNickName;
      QTextTableFormat tableFormat;
};

#endif
