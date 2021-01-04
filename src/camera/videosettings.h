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

#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H

#include <QAudioEncoderSettings>
#include <QDialog>
#include <QVideoEncoderSettings>

class QComboBox;
class QMediaRecorder;

namespace Ui {
class VideoSettingsUi;
}

class VideoSettings : public QDialog
{
   CS_OBJECT(VideoSettings)

 public:
   VideoSettings(QMediaRecorder *mediaRecorder, QWidget *parent = nullptr);
   ~VideoSettings();

   QAudioEncoderSettings audioSettings() const;
   void setAudioSettings(const QAudioEncoderSettings &);

   QVideoEncoderSettings videoSettings() const;
   void setVideoSettings(const QVideoEncoderSettings &);

   QString format() const;
   void setFormat(const QString &format);

 protected:
   void changeEvent(QEvent *e);

 private:
   QVariant boxValue(const QComboBox *) const;
   void selectComboBoxItem(QComboBox *box, const QVariant &value);

   Ui::VideoSettingsUi *ui;
   QMediaRecorder *mediaRecorder;
};

#endif
