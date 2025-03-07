/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H

#include "ui_international.h"

#include <QWidget>

class QStringListModel;
class QTranslator;

class International : public QWidget
{
   CS_OBJECT(International)

 public:
   International();
   ~International();

 protected:
   void changeEvent(QEvent *event) override;

 private:
   void retranslateUi();
   void getListData();

   Ui::International *ui;
   QStringListModel *m_model;
   static QTranslator *m_translator;

   // slot declarations
   void actionEnglish();
   void actionFrench();
   void actionGerman();
   void actionClose();
};

#endif
