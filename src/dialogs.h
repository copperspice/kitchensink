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

#ifndef DIALOGS_H
#define DIALOGS_H

#include "ui_dialogs.h"

#include <QWidget>
#include <qstringfwd.h>

class QErrorMessage;

class Dialogs : public QWidget
{
   CS_OBJECT(Dialogs)

   public:
      Dialogs(QWidget *parent = nullptr);
      ~Dialogs();

   private:
      CS_SLOT_1(Private, void setInteger())
      CS_SLOT_2(setInteger)

      CS_SLOT_1(Private, void setDouble())
      CS_SLOT_2(setDouble)

      CS_SLOT_1(Private, void setItem())
      CS_SLOT_2(setItem)

      CS_SLOT_1(Private, void setText())
      CS_SLOT_2(setText)

      CS_SLOT_1(Private, void setExistingDirectory())
      CS_SLOT_2(setExistingDirectory)

      CS_SLOT_1(Private, void setOpenFileName())
      CS_SLOT_2(setOpenFileName)

      CS_SLOT_1(Private, void setOpenFileNames())
      CS_SLOT_2(setOpenFileNames)

      CS_SLOT_1(Private, void criticalMessage())
      CS_SLOT_2(criticalMessage)

      CS_SLOT_1(Private, void informationMessage())
      CS_SLOT_2(informationMessage)

      CS_SLOT_1(Private, void questionMessage())
      CS_SLOT_2(questionMessage)

      CS_SLOT_1(Private, void warningMessage())
      CS_SLOT_2(warningMessage)

      CS_SLOT_1(Private, void errorMessage())
      CS_SLOT_2(errorMessage)

      Ui::Dialogs *ui;
      QErrorMessage *errorMessageDialog;
      QString openFilesPath;
};

#endif
