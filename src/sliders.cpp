/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
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

#include "sliders.h"

#include <QtGui>

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

   connect(m_buttonsOrientationComboBox, SIGNAL(currentIndexChanged(int)),
           this, SLOT(buttonsOrientationChanged(int)));

   m_optionsLayout = new QGridLayout;
   m_optionsLayout->addWidget(m_buttonsOrientationLabel, 0, 0);
   m_optionsLayout->addWidget(m_buttonsOrientationComboBox, 0, 1);
   m_optionsLayout->setColumnStretch(2, 1);
   m_optionsGroupBox->setLayout(m_optionsLayout);
}

void Sliders::createButtons()
{
   m_buttonBox = new QDialogButtonBox;
   m_buttonBox->setCenterButtons(true);
   m_rotateWidgetsButton = m_buttonBox->addButton(tr("Rotate &Widgets"),QDialogButtonBox::ActionRole);

   connect(m_rotateWidgetsButton, SIGNAL(clicked()), this, SLOT(rotateWidgets()));
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

   foreach (QWidget *widget, m_rotableWidgets) {
      m_rotableLayout->removeWidget(widget);
   }

   m_rotableWidgets.enqueue(m_rotableWidgets.dequeue());

   const int n = m_rotableWidgets.count();
   for (int i = 0; i < n / 2; ++i) {
      m_rotableLayout->addWidget(m_rotableWidgets[n - i - 1], 0, i);
      m_rotableLayout->addWidget(m_rotableWidgets[i], 1, i);
   }
}
