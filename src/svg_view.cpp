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

#include "svg_view.h"
#include "svgtextobject.h"
#include "util.h"

#include <QByteArray>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QSvgRenderer>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextEdit>
#include <QVBoxLayout>

Svg_View::Svg_View()
{
   setupGui();
   setupTextObject();

   setWindowTitle("SVG View");
}

void Svg_View::insertTextObject()
{
   QString fileName = m_fileNameCombo->currentText();
   QFile file(fileName);

   if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::warning(this, tr("Error Opening File"), tr("Could not open '%1'").formatArg(fileName));
   }

   QByteArray svgData = file.readAll();

   QTextCharFormat svgCharFormat;
   svgCharFormat.setObjectType(SvgTextFormat);
   QSvgRenderer renderer(svgData);

   QImage svgBufferImage(renderer.defaultSize(), QImage::Format_ARGB32);
   QPainter painter(&svgBufferImage);
   renderer.render(&painter, svgBufferImage.rect());

   svgCharFormat.setProperty(SvgData, svgBufferImage);

   QTextCursor cursor = m_textEdit->textCursor();
   cursor.insertText(QString(QChar::ObjectReplacementCharacter), svgCharFormat);
   m_textEdit->setTextCursor(cursor);
}

void Svg_View::setupTextObject()
{
   QObject *svgInterface = new SvgTextObject;
   m_textEdit->document()->documentLayout()->registerHandler(SvgTextFormat, svgInterface);
}

void Svg_View::setupGui()
{
   m_textEdit = new QTextEdit;
   m_textEdit->setFontPointSize(12.0);
   m_textEdit->setText("Select image in Combo Box. . . ");

   // *
   m_fileNameLabel = new QLabel(tr("SVG File Name:"));
   QFont font = m_fileNameLabel->font();
   font.setPointSize(10);
   m_fileNameLabel->setFont(font);

   m_fileNameCombo = new QComboBox;
   font = m_fileNameCombo->font();
   font.setPointSize(10);
   m_fileNameCombo->setFont(font);
   m_fileNameCombo->insertItem(0, ":/resources/pineapple.svg");
   m_fileNameCombo->insertItem(1, ":/resources/watermelon.svg");
   m_fileNameCombo->insertItem(2, ":/resources/cake1.svg");
   m_fileNameCombo->insertItem(3, ":/resources/cake2.svg");
   m_fileNameCombo->insertItem(4, ":/resources/cup_cake.svg");
   m_fileNameCombo->insertItem(5, ":/resources/ice_cream.svg");

   // *
   m_insertSVG_PB  = new QPushButton(tr("Insert Image"));
   m_insertSVG_PB->setFont(font);

   QPushButton *close_PB  = new QPushButton(tr("Close"));
   close_PB->setFont(font);

   QHBoxLayout *bottomLayout1 = new QHBoxLayout;
   bottomLayout1->addWidget(m_fileNameLabel);
   bottomLayout1->addWidget(m_fileNameCombo);
   bottomLayout1->addStretch();

   QHBoxLayout *bottomLayout2 = new QHBoxLayout;
   bottomLayout2->addStretch();
   bottomLayout2->addWidget(m_insertSVG_PB);
   bottomLayout2->addSpacing(8);
   bottomLayout2->addWidget(close_PB);
   bottomLayout2->addStretch();

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(m_textEdit);
   mainLayout->addSpacing(5);
   mainLayout->addLayout(bottomLayout1);
   mainLayout->addSpacing(5);
   mainLayout->addLayout(bottomLayout2);

   mainLayout->setContentsMargins(14,14,14,9);
   setLayout(mainLayout);

   connect(m_insertSVG_PB, &QPushButton::clicked, this, &Svg_View::insertTextObject);
   connect(close_PB,       &QPushButton::clicked, this, &Svg_View::actionClose);
}

void Svg_View::actionClose() {
   this->parentWidget()->close();
}

