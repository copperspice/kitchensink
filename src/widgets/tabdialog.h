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

#ifndef TABDIALOG_H
#define TABDIALOG_H

#include "ui_tabdialog.h"

#include <QWidget>

class TabDialog : public QWidget
{
   CS_OBJECT(TabDialog)

   public:
      TabDialog(QWidget *parent = nullptr);
      ~TabDialog();

   private:
      CS_SLOT_1(Private, void actionRollYourOwn())
      CS_SLOT_2(actionRollYourOwn)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      Ui::TabDialog *ui;
};

#endif
