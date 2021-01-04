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

#include "sliders.h"

#include <QComboBox>
#include <QDial>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

Sliders::Sliders()
   : QWidget()
{
   setWindowTitle(tr("Slider Widget"));

   createRotableGroupBox();
   createOptionsGroupBox();
   createButtons();

   m_mainLayout = new QGridLayout;
   m_mainLayout->addWidget(m_rotableGroupBox, 0, 0);
   m_mainLayout->addWidget(m_optionsGroupBox, 1, 0);
   m_mainLayout->addWidget(m_buttonBox, 2, 0);
   setLayout(m_mainLayout);

   m_mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
}

void Sliders::createRotableGroupBox()
{
   m_rotableGroupBox = new QGroupBox(tr("Rotable Widgets"));

   QFont font = m_rotableGroupBox->font();
   font.setPointSize(10);
   m_rotableGroupBox->setFont(font);

   m_rotableWidgets.enqueue(new QSpinBox);
   m_rotableWidgets.enqueue(new QSlider);
   m_rotableWidgets.enqueue(new QDial);
   m_rotableWidgets.enqueue(new QProgressBar);

   int nK = m_rotableWidgets.count();
   for (int i = 0; i < nK; ++i) {
      connect(m_rotableWidgets[i],SIGNAL(valueChanged(int)),
            m_rotableWidgets[(i + 1) % nK], SLOT(setValue(int)));
   }

   m_rotableLayout = new QGridLayout;
   m_rotableGroupBox->setLayout(m_rotableLayout);

   rotateWidgets();
}

void Sliders::createOptionsGroupBox()
{
   m_optionsGroupBox = new QGroupBox(tr("Options"));

   QFont font = m_optionsGroupBox->font();
   font.setPointSize(10);
   m_optionsGroupBox->setFont(font);

   m_buttonsOrientationLabel = new QLabel(tr("Orientation of buttons:"));

   m_buttonsOrientationComboBox = new QComboBox;
   m_buttonsOrientationComboBox->addItem(tr("Horizontal"), Qt::Horizontal);
   m_buttonsOrientationComboBox->addItem(tr("Vertical"),   Qt::Vertical);

   m_optionsLayout = new QGridLayout;
   m_optionsLayout->addWidget(m_buttonsOrientationLabel, 0, 0);
   m_optionsLayout->addWidget(m_buttonsOrientationComboBox, 0, 1);
   m_optionsLayout->setColumnStretch(2, 1);
   m_optionsGroupBox->setLayout(m_optionsLayout);

   // static_cast is required since this signal is overloaded
   connect(m_buttonsOrientationComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                  this, &Sliders::buttonsOrientationChanged);
}

void Sliders::createButtons()
{
   m_buttonBox = new QDialogButtonBox;
   m_buttonBox->setCenterButtons(true);
   m_rotateWidgetsButton = m_buttonBox->addButton(tr("Rotate &Widgets"),QDialogButtonBox::ActionRole);

   connect(m_rotateWidgetsButton, &QPushButton::clicked, this, &Sliders::rotateWidgets);
}

void Sliders::buttonsOrientationChanged(int index)
{
   m_mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
   setMinimumSize(0, 0);

   Qt::Orientation orientation = Qt::Orientation(m_buttonsOrientationComboBox->itemData(index).toInt());

   if (orientation == m_buttonBox->orientation()) {
      return;
   }

   m_mainLayout->removeWidget(m_buttonBox);

   int spacing = m_mainLayout->spacing();

   QSize oldSizeHint = m_buttonBox->sizeHint() + QSize(spacing, spacing);
   m_buttonBox->setOrientation(orientation);
   QSize newSizeHint = m_buttonBox->sizeHint() + QSize(spacing, spacing);

   if (orientation == Qt::Horizontal) {
      m_mainLayout->addWidget(m_buttonBox, 2, 0);
      resize(size() + QSize(-oldSizeHint.width(), newSizeHint.height()));

   } else {
      m_mainLayout->addWidget(m_buttonBox, 0, 3, 2, 1);
      resize(size() + QSize(newSizeHint.width(), -oldSizeHint.height()));
   }

   m_mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
}

void Sliders::rotateWidgets()
{
   Q_ASSERT(m_rotableWidgets.count() % 2 == 0);

   for (QWidget *widget : m_rotableWidgets) {
      m_rotableLayout->removeWidget(widget);
   }

   m_rotableWidgets.enqueue(m_rotableWidgets.dequeue());

   const int n = m_rotableWidgets.count();
   for (int i = 0; i < n / 2; ++i) {
      m_rotableLayout->addWidget(m_rotableWidgets[n - i - 1], 0, i);
      m_rotableLayout->addWidget(m_rotableWidgets[i], 1, i);
   }
}
