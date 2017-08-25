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

#ifndef STYLE_EDIT_H
#define STYLE_EDIT_H

#include "ui_style_edit.h"

#include <QDialog>

class Style_Edit : public QDialog
{
   CS_OBJECT(Style_Edit)

   public:
      Style_Edit(QWidget *parent, QWidget *dwFrom);
      ~Style_Edit();

      static QString getQssName();
      static QString loadStyleSheet(const QString &sheetName);

      CS_SLOT_1(Public, void actionClose())
      CS_SLOT_2(actionClose)

   private:
      CS_SLOT_1(Private, void on_styleCombo_activated(const QString & styleName))
      CS_SLOT_2(on_styleCombo_activated)

      CS_SLOT_1(Private, void on_styleSheetCombo_activated(const QString & styleSheetName))
      CS_SLOT_2(on_styleSheetCombo_activated)

      CS_SLOT_1(Private, void on_styleTextEdit_textChanged())
      CS_SLOT_2(on_styleTextEdit_textChanged)

      CS_SLOT_1(Private, void on_applyPB_clicked())
      CS_SLOT_2(on_applyPB_clicked)

      Ui::Style_Edit *ui;
      QWidget *m_dwFrom;
      static QString qssName;
      static QString readStyleSheet(const QString &name);
      void closeEvent(QCloseEvent *event);
};

#endif
