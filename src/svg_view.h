/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef SVG_VIEW_H
#define SVG_VIEW_H

#include <QTextFormat>
#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;
class QTextEdit;

class Svg_View : public QWidget
{
   CS_OBJECT(Svg_View)

 public:
   static constexpr const int SvgTextFormat = QTextFormat::UserObject + 1;
   static constexpr const int SvgImageId = 1;

   Svg_View();

 private:
   void setupTextObject();
   void setupGui();

   // slot declarations
   void insertTextObject();
   void actionClose();

   QTextEdit   *m_textEdit;
   QLabel      *m_fileNameLabel;
   QComboBox   *m_fileNameCombo;
   QPushButton *m_insertSVG_PB;
};

#endif
