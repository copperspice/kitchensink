/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef XMLSYNTAXHIGHLIGHTER_H
#define XMLSYNTAXHIGHLIGHTER_H

#include <QString>
#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QVector>

class QTextCharFormat;

class XmlSyntaxHighlighter : public QSyntaxHighlighter
{
 public:
   XmlSyntaxHighlighter(QTextDocument *parent = nullptr);

   protected:
      virtual void highlightBlock(const QString &text);

 private:
   struct HighlightingRule
   {
      QRegularExpression pattern;
      QTextCharFormat format;
   };

   QVector<HighlightingRule> highlightingRules;

   QRegularExpression commentStartExpression;
   QRegularExpression commentEndExpression;

   QTextCharFormat tagFormat;
   QTextCharFormat attributeFormat;
   QTextCharFormat attributeContentFormat;
   QTextCharFormat commentFormat;
};

#endif
