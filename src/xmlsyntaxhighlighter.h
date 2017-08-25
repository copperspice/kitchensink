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

#ifndef XMLSYNTAXHIGHLIGHTER_H
#define XMLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class XmlSyntaxHighlighter : public QSyntaxHighlighter
{
    public:
        XmlSyntaxHighlighter(QTextDocument *parent = nullptr);

    protected:
        virtual void highlightBlock(const QString &text);

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };

        QVector<HighlightingRule> highlightingRules;

        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat tagFormat;
        QTextCharFormat attributeFormat;
        QTextCharFormat attributeContentFormat;
        QTextCharFormat commentFormat;
};

#endif
