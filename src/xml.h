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
