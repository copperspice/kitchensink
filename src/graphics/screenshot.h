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

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPixmap>
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
       QSize sizeHint() const;

   protected:
       void resizeEvent(QResizeEvent *event);

   private:
       void createOptionsGroupBox();
       void createButtonsLayout();
       QPushButton *createButton(const QString &text, QWidget *receiver, const QString &member);
       void updateScreenshotLabel();

       CS_SLOT_1(Private, void newScreenshot())
       CS_SLOT_2(newScreenshot)

       CS_SLOT_1(Private, void saveScreenshot())
       CS_SLOT_2(saveScreenshot)

       CS_SLOT_1(Private, void shootScreen())
       CS_SLOT_2(shootScreen)

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
