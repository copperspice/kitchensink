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

#ifndef IMAGESETTINGS_H
#define IMAGESETTINGS_H

#include <QDialog>
#include <QAudioEncoderSettings>
#include <QVideoEncoderSettings>

class QComboBox;
class QCameraImageCapture;

namespace Ui {
class ImageSettingsUi;
}

class ImageSettings : public QDialog
{
   CS_OBJECT(ImageSettings)

 public:
   ImageSettings(QCameraImageCapture *imageCapture, QWidget *parent = nullptr);
   ~ImageSettings();

   QAudioEncoderSettings audioSettings() const;
   void setAudioSettings(const QAudioEncoderSettings &settings);

   QImageEncoderSettings imageSettings() const;
   void setImageSettings(const QImageEncoderSettings &settings);

   QString format() const;
   void setFormat(const QString &format);

 protected:
   void changeEvent(QEvent *e);

 private:
   QVariant boxValue(const QComboBox *box) const;
   void selectComboBoxItem(QComboBox *box, const QVariant &value);

   Ui::ImageSettingsUi *ui;
   QCameraImageCapture *imagecapture;
};

#endif