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

#include "xmlsyntaxhighlighter.h"

XmlSyntaxHighlighter::XmlSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // tag format
    tagFormat.setForeground(Qt::darkBlue);
    tagFormat.setFontWeight(QFont::Bold);

    rule.pattern = QRegularExpression("(<[a-zA-Z:]+\\b|<\\?[a-zA-Z:]+\\b|\\?>|>|/>|</[a-zA-Z:]+>)");
    rule.format  = tagFormat;
    highlightingRules.append(rule);

    // attribute format
    attributeFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("[a-zA-Z:]+=");
    rule.format  = attributeFormat;
    highlightingRules.append(rule);

    // attribute content format
    attributeContentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("(\"[^\"]*\"|'[^']*')");
    rule.format  = attributeContentFormat;
    highlightingRules.append(rule);

    commentFormat.setForeground(Qt::lightGray);
    commentFormat.setFontItalic(true);

    commentStartExpression = QRegularExpression("<!--");
    commentEndExpression   = QRegularExpression("-->");
}

void XmlSyntaxHighlighter::highlightBlock(const QString &text)
{
   // syntax rules
   for (const HighlightingRule &rule : highlightingRules) {
      QRegularExpressionMatch match = rule.pattern.match(text);

      while (match.hasMatch()) {
         int index  = match.capturedStart(0) - text.begin();
         int length = match.capturedLength();

         setFormat(index, length, rule.format);
         match = rule.pattern.match(text, match.capturedEnd(0));
      }
   }

   // comment block
   setCurrentBlockState(0);
   int startIndex = -1;

   if (previousBlockState() != 1) {
      auto iter = text.indexOfFast(commentStartExpression);

      if (iter != text.end()) {
        startIndex = iter - text.begin();
      }
   }

   while (startIndex >= 0) {
      int commentLength;
      QRegularExpressionMatch match = commentEndExpression.match(text, text.begin() + startIndex);

      if (match.hasMatch()) {
         int endIndex  = match.capturedStart() - text.begin();
         commentLength = endIndex - startIndex + match.capturedLength();

      } else {
         setCurrentBlockState(1);
         commentLength = text.length() - startIndex;
      }

      setFormat(startIndex, commentLength, commentFormat);

      if (! match.hasMatch()) {
         break;
      }

      // find the next match
      match = commentStartExpression.match(text, match.capturedEnd(0));

      if (match.hasMatch()) {
         startIndex = match.capturedStart(0) - text.begin();
      } else {
         startIndex = -1;
      }
   }
}
