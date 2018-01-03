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

#ifndef XMLPATTERNS_H
#define XMLPATTERNS_H

#include "ui_xmlpatterns.h"

#include <QWidget>

class QString;

class XmlPatterns : public QWidget
{
   CS_OBJECT(XmlPatterns)

   public:
      XmlPatterns();
      ~XmlPatterns();

   private:
      void evaluate(const QString &str);
      void loadInputFile();

      CS_SLOT_1(Private, void displayQuery(int index))
      CS_SLOT_2(displayQuery)

      Ui::XmlPatterns *ui;
};

#endif
