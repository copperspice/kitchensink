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
      CS_SLOT_1(Private, void actionOpenXml())
      CS_SLOT_2(actionOpenXml)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      Ui::Xml *ui;
      QString m_fileName;
      QStandardItemModel *m_model;

      void processXml();
      void parseElement(QStandardItem *parentItem, QDomElement element);
      void parseMealElement(QStandardItem *parentItem, QDomElement element);
      QStandardItem *addElement(QStandardItem *parentItem, QString text);

};

#endif
