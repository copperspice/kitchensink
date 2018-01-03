/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
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

   shootScreen();
   delaySpinBox->setValue(5);
}

void Screenshot::resizeEvent(QResizeEvent * /* event */)
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
    QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
}

void Screenshot::saveScreenshot()
{
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                  tr("%1 Files (*.%2);;All Files (*)").arg(format.toUpper()).arg(format));

    if (! fileName.isEmpty()) {
        originalPixmap.save(fileName, format.toLatin1().constData());
    }
}

void Screenshot::shootScreen()
{
    if (delaySpinBox->value() != 0) {
        qApp->beep();
    }

    originalPixmap = QPixmap();

    originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
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

QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver, const char *member)
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
