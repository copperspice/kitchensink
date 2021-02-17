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

#include "screenshot.h"

#include <QCheckBox>
#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QSize>
#include <QString>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

#include <QApplication>
#include <QDesktopWidget>

Screenshot::Screenshot()
{
   setWindowTitle(tr("Screen Shot"));

   screenshotLabel = new QLabel;
   screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   screenshotLabel->setAlignment(Qt::AlignCenter);
   screenshotLabel->setMinimumSize(240, 160);

   createOptionsGroupBox();
   createButtonsLayout();

   mainLayout = new QVBoxLayout;
   mainLayout->addWidget(screenshotLabel);
   mainLayout->addWidget(optionsGroupBox);
   mainLayout->addLayout(buttonsLayout);
   setLayout(mainLayout);

   captureScreen();
   delaySpinBox->setValue(5);
}

void Screenshot::resizeEvent(QResizeEvent *)
{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);

    if (! screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())  {
        updateScreenshotLabel();
    }
}

QSize Screenshot::sizeHint() const
{
   return QSize(500,400);
}

void Screenshot::newScreenshot()
{
    newScreenshotButton->setDisabled(true);
    QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(captureScreen()));
}

void Screenshot::saveScreenshot()
{
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                  tr("%1 Files (*.%2);;All Files (*)").formatArgs(format.toUpper(), format));

    if (! fileName.isEmpty()) {
        originalPixmap.save(fileName, csPrintable(format));
    }
}

void Screenshot::captureScreen()
{
    if (delaySpinBox->value() != 0) {
        qApp->beep();
    }

    originalPixmap = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    updateScreenshotLabel();

    newScreenshotButton->setDisabled(false);
}

void Screenshot::createOptionsGroupBox()
{
    optionsGroupBox = new QGroupBox(tr("Options"));

    delaySpinBox = new QSpinBox;
    delaySpinBox->setSuffix(tr(" s"));
    delaySpinBox->setMaximum(60);

    delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

    optionsGroupBoxLayout = new QGridLayout;
    optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
    optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);

    optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void Screenshot::createButtonsLayout()
{
    newScreenshotButton  = createButton(tr("New Screenshot"),  this, SLOT(newScreenshot()));
    saveScreenshotButton = createButton(tr("Save Screenshot"), this, SLOT(saveScreenshot()));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(newScreenshotButton);
    buttonsLayout->addWidget(saveScreenshotButton);
    buttonsLayout->addStretch();
}

QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver, const QString &member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}

void Screenshot::updateScreenshotLabel()
{
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
