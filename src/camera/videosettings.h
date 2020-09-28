/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
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
