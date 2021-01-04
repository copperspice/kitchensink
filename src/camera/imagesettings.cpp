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

#include <ui_camera_imagesettings.h>

#include <imagesettings.h>

#include <QCameraImageCapture>
#include <QComboBox>
#include <QDebug>
#include <QMediaService>

ImageSettings::ImageSettings(QCameraImageCapture *imageCapture, QWidget *parent)
   : QDialog(parent), ui(new Ui::ImageSettingsUi), imagecapture(imageCapture)
{
   ui->setupUi(this);

   // image codecs
   ui->imageCodecBox->addItem(tr("Default image format"), QVariant(QString()));

   for (const QString &codecName : imagecapture->supportedImageCodecs()) {
      QString description = imagecapture->imageCodecDescription(codecName);
      ui->imageCodecBox->addItem(codecName + ": " + description, QVariant(codecName));
   }

   ui->imageQualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));

   ui->imageResolutionBox->addItem(tr("Default Resolution"));
   QList<QSize> supportedResolutions = imagecapture->supportedResolutions();

   for (const QSize &resolution : supportedResolutions) {
      ui->imageResolutionBox->addItem(QString("%1x%2").formatArg(resolution.width())
                                      .formatArg(resolution.height()), QVariant(resolution));
   }
}

ImageSettings::~ImageSettings()
{
   delete ui;
}

void ImageSettings::changeEvent(QEvent *e)
{
   QDialog::changeEvent(e);

   switch (e->type()) {
      case QEvent::LanguageChange:
         ui->retranslateUi(this);
         break;

      default:
         break;
   }
}

QImageEncoderSettings ImageSettings::imageSettings() const
{
   QImageEncoderSettings settings = imagecapture->encodingSettings();
   settings.setCodec(boxValue(ui->imageCodecBox).toString());
   settings.setQuality(QMultimedia::EncodingQuality(ui->imageQualitySlider->value()));
   settings.setResolution(boxValue(ui->imageResolutionBox).toSize());

   return settings;
}

void ImageSettings::setImageSettings(const QImageEncoderSettings &imageSettings)
{
   selectComboBoxItem(ui->imageCodecBox, QVariant(imageSettings.codec()));
   selectComboBoxItem(ui->imageResolutionBox, QVariant(imageSettings.resolution()));
   ui->imageQualitySlider->setValue(imageSettings.quality());
}

QVariant ImageSettings::boxValue(const QComboBox *box) const
{
   int idx = box->currentIndex();
   if (idx == -1) {
      return QVariant();
   }

   return box->itemData(idx);
}

void ImageSettings::selectComboBoxItem(QComboBox *box, const QVariant &value)
{
   for (int i = 0; i < box->count(); ++i) {
      if (box->itemData(i) == value) {
         box->setCurrentIndex(i);
         break;
      }
   }
}
