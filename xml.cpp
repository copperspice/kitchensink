/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

   // signals
   connect(ui->openPB,  SIGNAL(clicked()), this, SLOT(actionOpenXml()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));
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
      QMessageBox::warning( 0, "XML", msg );
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

