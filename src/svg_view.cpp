/**********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
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

#include <QtGui>
#include <QtSvg>

#include "util.h"
#include "svg_view.h"
#include "svgtextobject.h"

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

      QMessageBox::warning(this, tr("Error Opening File"),
                           tr("Could not open '%1'").arg(fileName));
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

   // signals
   connect(m_insertSVG_PB, SIGNAL(clicked()), this, SLOT(insertTextObject()));
   connect(close_PB,       SIGNAL(clicked()), this, SLOT(actionClose()));
}

void Svg_View::actionClose() {
   this->parentWidget()->close();
}

