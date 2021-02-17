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

#include "util.h"
#include "xml.h"

#include <QFileDialog>

Xml::Xml()
   : QWidget(), ui(new Ui::Xml)
{
   ui->setupUi(this);
   setWindowTitle("XML");

   m_model = new QStandardItemModel;
   ui->treeView->setModel(m_model);

   // load data from resource file
   m_fileName = ":/resources/sampleMenu.xml";
   processXml();

   connect(ui->openPB,  &QPushButton::clicked, this, &Xml::actionOpenXml);
   connect(ui->closePB, &QPushButton::clicked, this, &Xml::actionClose);
}

Xml::~Xml()
{
   delete ui;
}

void Xml::actionOpenXml()
{
   m_fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"),
            QDir::currentPath(), tr("XML Files (*.xml)"));

   if (! m_fileName.isEmpty()) {
      processXml();
   }
}

void Xml::processXml()
{
   QFile file(m_fileName);
   if (! file.open(QFile::ReadOnly | QFile::Text)) {

      const QString msg = "Unable to open file " + m_fileName + " : " + file.errorString();
      QMessageBox::warning(nullptr, "XML", msg);
      return;
   }

   //
   const QString xmlRoot = "restaurant";
   QDomDocument doc;

   // parse contents of file into a doc
   QString errorMsg;
   int errorLine;
   int errorColumn;

   if (! doc.setContent(&file, false, &errorMsg, &errorLine, &errorColumn)) {
     file.close();

     const QString msg = "Set content failed.   \n\nError:" + errorMsg + "\n" +
         "Line: " + QString::number(errorLine) + "  Column: " + QString::number(errorColumn);

     QMessageBox::warning( this, "XML", msg );
     return;
   }

   // display only, xml file saved in a textEdit
   file.seek(0);
   QByteArray temp = file.readAll();

   QString fileData = QString::fromUtf8(temp);
   ui->textEdit->setPlainText(fileData);

   file.close();

   // test root element
   QDomElement root = doc.documentElement();

   if (root.tagName() != xmlRoot)  {
      const QString msg = "XML root element must be " + xmlRoot;
      QMessageBox::warning( this, "XML", msg );
      return;
   }

   //
   QStandardItem *rootItem = m_model->invisibleRootItem();
   parseElement(rootItem, root);

   //
   m_model->setHeaderData(0, Qt::Horizontal, QObject::tr("CopperSpice Diner"));
   ui->treeView->expandAll();
}

void Xml::parseElement(QStandardItem *rootItem, QDomElement element)
{
   QString rootName = element.tagName();
   rootName = element.tagName().mid(0,1).toUpper() + element.tagName().mid(1);

   QStandardItem *parentItem;
   parentItem = addElement(rootItem, rootName);

   //
   QStandardItem *childItem;
   QDomNode node = element.firstChild();

   while(! node.isNull()) {

      // convert the node to an element
      QDomElement nextElem = node.toElement();

      if (! nextElem.isNull() ) {

         if (nextElem.tagName() == "meal") {
            QString attrib = nextElem.attribute("name");

            if ( attrib.isEmpty() ) {
               attrib = "Unknown Category";
            }

            childItem = addElement(parentItem, attrib);
            parseMealElement(childItem, nextElem );
         }
      }

      node = node.nextSibling();
   }
}

void Xml::parseMealElement(QStandardItem *parentItem, QDomElement element)
{
   QStandardItem *childItem;
   QDomNode node = element.firstChild();

   while (! node.isNull()) {

      // convert the node to an element
      QDomElement nextElem = node.toElement();

      if (! nextElem.isNull() ) {

         if (nextElem.tagName() == "course") {
            childItem = addElement(parentItem, nextElem.attribute("name"));
            parseMealElement(childItem, nextElem );

         } else if (nextElem.tagName() == "item") {
            addElement(parentItem, nextElem.text());
         }
      }

      node = node.nextSibling();
   }
}

QStandardItem *Xml::addElement(QStandardItem *parentItem, QString text)
{
   if (text.isEmpty()) {
      return parentItem;
   }

   QStandardItem *item = new QStandardItem;
   item->setText(text);
   // item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

   parentItem->appendRow(item);
   return item;
}

void Xml::actionClose() {
   this->parentWidget()->close();
}

