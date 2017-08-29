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

#ifndef SLIDERS_H
#define SLIDERS_H

#include <QQueue>
#include <QWidget>

class QComboBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QPushButton;


class Sliders : public QWidget
{
   CS_OBJECT(Sliders)

   public:
      Sliders();

   private:
      void createRotableGroupBox();
      void createOptionsGroupBox();
      void createButtons();

      CS_SLOT_1(Private, void buttonsOrientationChanged(int index))
      CS_SLOT_2(buttonsOrientationChanged)

      CS_SLOT_1(Private, void rotateWidgets())
      CS_SLOT_2(rotateWidgets)

      QGroupBox *m_rotableGroupBox;
      QQueue<QWidget *> m_rotableWidgets;

      QGroupBox *m_optionsGroupBox;
      QLabel *m_buttonsOrientationLabel;
      QComboBox *m_buttonsOrientationComboBox;

      QDialogButtonBox *m_buttonBox;
      QPushButton *m_rotateWidgetsButton;

      QGridLayout *m_mainLayout;
      QGridLayout *m_rotableLayout;
      QGridLayout *m_optionsLayout;
};

#endif
