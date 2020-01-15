/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
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

#ifndef DRAW_H
#define DRAW_H

#include "draw_area.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

class Draw : public QWidget
{
   CS_OBJECT(Draw)

   public:
      Draw();

   private :
      CS_SLOT_1(Private, void shapeChanged())
      CS_SLOT_2(shapeChanged)

      CS_SLOT_1(Private, void penChanged())
      CS_SLOT_2(penChanged)

      CS_SLOT_1(Private, void brushChanged())
      CS_SLOT_2(brushChanged)

      DrawArea *m_renderArea;
      QLabel *shapeLabel;
      QLabel *penWidthLabel;
      QLabel *penStyleLabel;
      QLabel *penCapLabel;
      QLabel *penJoinLabel;
      QLabel *brushStyleLabel;
      QLabel *otherOptionsLabel;
      QComboBox *shapeComboBox;
      QSpinBox *penWidthSpinBox;
      QComboBox *penStyleComboBox;
      QComboBox *penCapComboBox;
      QComboBox *penJoinComboBox;
      QComboBox *brushStyleComboBox;
      QCheckBox *antialiasingCheckBox;
      QCheckBox *transformationsCheckBox;
};


#endif
