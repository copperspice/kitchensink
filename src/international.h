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

#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H

#include "ui_international.h"

#include <QStringListModel>
#include <QWidget>

class International : public QWidget
{
   CS_OBJECT(International)

   public:
      International();
      ~International();

   private:
      void retranslateUi();
      void changeEvent(QEvent *event);
      void getListData();

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      CS_SLOT_1(Private, void actionEnglish())
      CS_SLOT_2(actionEnglish)

      CS_SLOT_1(Private, void actionFrench())
      CS_SLOT_2(actionFrench)

      CS_SLOT_1(Private, void actionGerman())
      CS_SLOT_2(actionGerman)

      Ui::International *ui;
      QStringListModel *m_model;
      static QTranslator *m_translator;
};

#endif
