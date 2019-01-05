/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#ifndef XML_H
#define XML_H

#include "ui_xml.h"
#include "mainwindow.h"

#include <QDomDocument>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QWidget>

class Xml : public QWidget
{
   CS_OBJECT(Xml)

   public:
      explicit Xml();
      ~Xml();

   private:
      Ui::Xml *ui;
      QString m_fileName;
      QStandardItemModel *m_model;

      void processXml();
      void parseElement(QStandardItem *parentItem, QDomElement element);
      void parseMealElement(QStandardItem *parentItem, QDomElement element);
      QStandardItem *addElement(QStandardItem *parentItem, QString text);

      // slot declarations
      void actionOpenXml();
      void actionClose();
};

#endif
