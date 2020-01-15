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

#ifndef SCRIPT_H
#define SCRIPT_H

#include "ui_script.h"

#include <QWidget>
#include <qstringfwd.h>

class QStandardItemModel;

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
