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

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPixmap>
#include <QSize>
#include <QWidget>

class QCheckBox;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QSpinBox;
class QVBoxLayout;

class Screenshot : public QWidget
{
   CS_OBJECT(Screenshot)

 public:
   Screenshot();

 protected:
   void resizeEvent(QResizeEvent *event) override;
   QSize sizeHint() const override;

 private:
   void createOptionsGroupBox();
   void createButtonsLayout();
   QPushButton *createButton(const QString &text, QWidget *receiver, const QString &member);
   void updateScreenshotLabel();

   CS_SLOT_1(Private, void newScreenshot())
   CS_SLOT_2(newScreenshot)

   CS_SLOT_1(Private, void saveScreenshot())
   CS_SLOT_2(saveScreenshot)

   CS_SLOT_1(Private, void captureScreen())
   CS_SLOT_2(captureScreen)

   QPixmap originalPixmap;

   QLabel *screenshotLabel;
   QGroupBox *optionsGroupBox;
   QSpinBox *delaySpinBox;
   QLabel *delaySpinBoxLabel;
   QPushButton *newScreenshotButton;
   QPushButton *saveScreenshotButton;

   QVBoxLayout *mainLayout;
   QGridLayout *optionsGroupBoxLayout;
   QHBoxLayout *buttonsLayout;
};

#endif
