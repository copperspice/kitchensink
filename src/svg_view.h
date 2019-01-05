/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
      enum { SvgTextFormat = QTextFormat::UserObject + 1 };
      enum SvgProperties { SvgData = 1 };

      Svg_View();

   private:
      void setupTextObject();
      void setupGui();

      CS_SLOT_1(Private, void insertTextObject())
      CS_SLOT_2(insertTextObject)
      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      QTextEdit   *m_textEdit;
      QLabel      *m_fileNameLabel;
      QComboBox   *m_fileNameCombo;
      QPushButton *m_insertSVG_PB;
};

#endif
