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
#include <qstringfwd.h>

class XmlPatterns : public QWidget
{
   CS_OBJECT(XmlPatterns)

   public:
      XmlPatterns();
      ~XmlPatterns();

   private:
      Ui::XmlPatterns *ui;

      void evaluate(const QString &str);
      void loadInputFile();

      // slot declarations
      void displayQuery(int index);
};

#endif
