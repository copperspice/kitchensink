/***********************************************************************
*
* Copyright (c) 2012-2026 Barbara Geller
* Copyright (c) 2012-2026 Ansel Sermersheim
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

#ifndef IMAGESETTINGS_H
#define IMAGESETTINGS_H

#ifndef QT_NO_MULTIMEDIA

#include <QAudioEncoderSettings>
#include <QDialog>
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
   void changeEvent(QEvent *e) override;

 private:
   QVariant boxValue(const QComboBox *box) const;
   void selectComboBoxItem(QComboBox *box, const QVariant &value);

   Ui::ImageSettingsUi *ui;
   QCameraImageCapture *imagecapture;
};

#endif   // ! QT_NO_MULTIMEDIA

#endif
