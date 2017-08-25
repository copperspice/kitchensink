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

#include "xmlpatterns.h"
#include "xmlsyntaxhighlighter.h"
#include "util.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QSize>

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

   int len = queries.count();

   for(int i = 0; i < len; ++i)  {
      ui->defaultQueries->addItem(queries.at(i));
   }

   // signals
   connect(ui->defaultQueries, SIGNAL(currentIndexChanged(int)), this, SLOT(displayQuery(int)));
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

