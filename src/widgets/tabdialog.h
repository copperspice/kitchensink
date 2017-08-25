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
