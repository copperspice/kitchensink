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

#include "xmlsyntaxhighlighter.h"

XmlSyntaxHighlighter::XmlSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // tag format
    tagFormat.setForeground(Qt::darkBlue);
    tagFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("(<[a-zA-Z:]+\\b|<\\?[a-zA-Z:]+\\b|\\?>|>|/>|</[a-zA-Z:]+>)");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    // attribute format
    attributeFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("[a-zA-Z:]+=");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // attribute content format
    attributeContentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("(\"[^\"]*\"|'[^']*')");
    rule.format = attributeContentFormat;
    highlightingRules.append(rule);

    commentFormat.setForeground(Qt::lightGray);
    commentFormat.setFontItalic(true);

    commentStartExpression = QRegExp("<!--");
    commentEndExpression   = QRegExp("-->");
}

void XmlSyntaxHighlighter::highlightBlock(const QString &text)
{
     for (const HighlightingRule &rule : highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = text.indexOf(expression);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = text.indexOf(expression, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = text.indexOf(commentStartExpression);

     while (startIndex >= 0) {
         int endIndex = text.indexOf(commentEndExpression, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, commentFormat);
         startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
     }
}
