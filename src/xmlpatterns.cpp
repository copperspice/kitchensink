/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
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
    if (! query.isValid())
        return;

    QXmlFormatter formatter(query, &buffer);
    if (! query.evaluateTo(&formatter)) {
        return;
    }

    buffer.close();
    this->findChild<QTextEdit*>("outputTextEdit")->setPlainText(QString::fromUtf8(outArray.constData()));
}

