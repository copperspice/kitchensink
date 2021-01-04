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

#include "xmlpatterns.h"
#include "xmlsyntaxhighlighter.h"
#include "util.h"

#include <QByteArray>
#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QSize>
#include <QTextStream>
#include <QXmlFormatter>
#include <QXmlQuery>

static const QString qmPath = ":/resources/xml_patterns";

XmlPatterns::XmlPatterns()
   : QWidget(), ui(new Ui::XmlPatterns)
{
   ui->setupUi(this);
   setWindowTitle("XML Patterns");

   new XmlSyntaxHighlighter(this->findChild<QTextEdit*>("inputTextEdit")->document());
   new XmlSyntaxHighlighter(this->findChild<QTextEdit*>("outputTextEdit")->document());

   loadInputFile();
   const QStringList queries(QDir(qmPath + "/", "*.xq").entryList());

   for(const QString &item : queries)  {
      ui->defaultQueries->addItem(item);
   }

   // static_cast is required since this signal is overloaded
   connect(ui->defaultQueries, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                  this, &XmlPatterns::displayQuery);

   displayQuery(0);
}

XmlPatterns::~XmlPatterns()
{
   delete ui;
}

void XmlPatterns::displayQuery(int index)
{
   QFile queryFile(QString(qmPath + "/") + ui->defaultQueries->itemText(index));
   queryFile.open(QIODevice::ReadOnly);

   const QString query(QString::fromLatin1(queryFile.readAll()));
   this->findChild<QTextEdit*>("queryTextEdit")->setPlainText(query);

   evaluate(query);
}

void XmlPatterns::loadInputFile()
{
   QFile forView;
   forView.setFileName(qmPath + "/cookbook.xml");

   if (! forView.open(QIODevice::ReadOnly)) {
     ksMsg(tr("Unable to Open File") + forView.errorString());
     return;
   }

   QTextStream in(&forView);
   QString inputDocument = in.readAll();
   this->findChild<QTextEdit*>("inputTextEdit")->setPlainText(inputDocument);
}

void XmlPatterns::evaluate(const QString &str)
{
   QFile sourceDocument;
   sourceDocument.setFileName(qmPath + "/cookbook.xml");
   sourceDocument.open(QIODevice::ReadOnly);

   QByteArray outArray;
   QBuffer buffer(&outArray);
   buffer.open(QIODevice::ReadWrite);

   QXmlQuery query;
   query.bindVariable("inputDocument", &sourceDocument);
   query.setQuery(str);

   if (! query.isValid()) {
     return;
   }

   QXmlFormatter formatter(query, &buffer);
   if (! query.evaluateTo(&formatter)) {
      return;
   }

   buffer.close();
   this->findChild<QTextEdit*>("outputTextEdit")->setPlainText(QString::fromUtf8(outArray.constData()));
}
