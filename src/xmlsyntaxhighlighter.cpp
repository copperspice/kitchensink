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
   int startIndex = 0;

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
         setCurrentBlockState(1);
         commentLength = text.length() - startIndex;

      } else {
         int endIndex  = match.capturedStart() - text.begin();
         commentLength = endIndex - startIndex + match.capturedLength();
      }

      setFormat(startIndex, commentLength, commentFormat);
      match = commentStartExpression.match(text, match.capturedEnd(0));

      if (match.hasMatch()) {
         startIndex = match.capturedStart(0) - text.begin();
      } else {
         startIndex = -1;
      }
   }
}
