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

#ifndef SCRIPT_H
#define SCRIPT_H

#include "ui_script.h"

#include <QWidget>

class QStandardItemModel;
class QString;

class Script : public QWidget
{
   CS_OBJECT(Script)

   public:
      explicit Script();
      ~Script();

   private:
      CS_SLOT_1(Private, void actionOpenScript())
      CS_SLOT_2(actionOpenScript)

      CS_SLOT_1(Private, void actionRunScript())
      CS_SLOT_2(actionRunScript)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      Ui::Script *ui;
      QString m_fileName;
      void displayScript();
      void jsScript(QString contents);
};

#endif
