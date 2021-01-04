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

#include <ui_camera_videosettings.h>

#include <videosettings.h>

#include <QComboBox>
#include <QDebug>
#include <QMediaRecorder>
#include <QMediaService>

VideoSettings::VideoSettings(QMediaRecorder *mediaRecorder, QWidget *parent)
   : QDialog(parent), ui(new Ui::VideoSettingsUi), mediaRecorder(mediaRecorder)
{
   ui->setupUi(this);

   // audio codecs
   ui->audioCodecBox->addItem(tr("Default audio codec"), QVariant(QString()));

   for (const QString &codecName : mediaRecorder->supportedAudioCodecs()) {
      QString description = mediaRecorder->audioCodecDescription(codecName);
      ui->audioCodecBox->addItem(codecName + ": " + description, QVariant(codecName));
   }

   // sample rate
   for (int sampleRate : mediaRecorder->supportedAudioSampleRates()) {
      ui->audioSampleRateBox->addItem(QString::number(sampleRate), QVariant(sampleRate));
   }

   ui->audioQualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));

   // video codecs
   ui->videoCodecBox->addItem(tr("Default video codec"), QVariant(QString()));

   for (const QString &codecName : mediaRecorder->supportedVideoCodecs()) {
      QString description = mediaRecorder->videoCodecDescription(codecName);
      ui->videoCodecBox->addItem(codecName + ": " + description, QVariant(codecName));
   }

   ui->videoQualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));

   ui->videoResolutionBox->addItem(tr("Default"));
   QList<QSize> supportedResolutions = mediaRecorder->supportedResolutions();

   for (const QSize &resolution : supportedResolutions) {
      ui->videoResolutionBox->addItem(QString("%1x%2").formatArg(resolution.width()).
                  formatArg(resolution.height()), QVariant(resolution));
   }

   ui->videoFramerateBox->addItem(tr("Default"));
   QList<qreal> supportedFrameRates = mediaRecorder->supportedFrameRates();

   for (double rate : supportedFrameRates) {
      QString rateString = QString("%1").formatArg(rate, 0, 'f', 2);
      ui->videoFramerateBox->addItem(rateString, QVariant(rate));
   }

   // containers
   ui->containerFormatBox->addItem(tr("Default container"), QVariant(QString()));

   for (const QString &format : mediaRecorder->supportedContainers()) {
      ui->containerFormatBox->addItem(format + ":" + mediaRecorder->containerDescription(format), QVariant(format));
   }
}

VideoSettings::~VideoSettings()
{
   delete ui;
}

void VideoSettings::changeEvent(QEvent *e)
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

QAudioEncoderSettings VideoSettings::audioSettings() const
{
   QAudioEncoderSettings settings = mediaRecorder->audioSettings();
   settings.setCodec(boxValue(ui->audioCodecBox).toString());
   settings.setQuality(QMultimedia::EncodingQuality(ui->audioQualitySlider->value()));
   settings.setSampleRate(boxValue(ui->audioSampleRateBox).toInt());
   return settings;
}

void VideoSettings::setAudioSettings(const QAudioEncoderSettings &audioSettings)
{
   selectComboBoxItem(ui->audioCodecBox, QVariant(audioSettings.codec()));
   selectComboBoxItem(ui->audioSampleRateBox, QVariant(audioSettings.sampleRate()));
   ui->audioQualitySlider->setValue(audioSettings.quality());
}

QVideoEncoderSettings VideoSettings::videoSettings() const
{
   QVideoEncoderSettings settings = mediaRecorder->videoSettings();
   settings.setCodec(boxValue(ui->videoCodecBox).toString());
   settings.setQuality(QMultimedia::EncodingQuality(ui->videoQualitySlider->value()));
   settings.setResolution(boxValue(ui->videoResolutionBox).toSize());
   settings.setFrameRate(boxValue(ui->videoFramerateBox).value<qreal>());

   return settings;
}

void VideoSettings::setVideoSettings(const QVideoEncoderSettings &videoSettings)
{
   selectComboBoxItem(ui->videoCodecBox, QVariant(videoSettings.codec()));
   selectComboBoxItem(ui->videoResolutionBox, QVariant(videoSettings.resolution()));
   ui->videoQualitySlider->setValue(videoSettings.quality());

   // special case for frame rate
   for (int i = 0; i < ui->videoFramerateBox->count(); ++i) {
      qreal itemRate = ui->videoFramerateBox->itemData(i).value<qreal>();

      if (qFuzzyCompare(itemRate, videoSettings.frameRate())) {
         ui->videoFramerateBox->setCurrentIndex(i);
         break;
      }
   }
}

QString VideoSettings::format() const
{
   return boxValue(ui->containerFormatBox).toString();
}

void VideoSettings::setFormat(const QString &format)
{
   selectComboBoxItem(ui->containerFormatBox, QVariant(format));
}

QVariant VideoSettings::boxValue(const QComboBox *box) const
{
   int idx = box->currentIndex();
   if (idx == -1) {
      return QVariant();
   }

   return box->itemData(idx);
}

void VideoSettings::selectComboBoxItem(QComboBox *box, const QVariant &value)
{
   for (int i = 0; i < box->count(); ++i) {
      if (box->itemData(i) == value) {
         box->setCurrentIndex(i);
         break;
      }
   }
}
