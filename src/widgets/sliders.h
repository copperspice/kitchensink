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

      // slot declarations
      void buttonsOrientationChanged(int index);
      void rotateWidgets();
};

#endif
