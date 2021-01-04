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

#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QMainWindow>
#include <QMediaRecorder>

namespace Ui {
   class Camera;
}

class Camera : public QMainWindow
{
   CS_OBJECT(Camera)

 public:
   Camera(QWidget *parent = nullptr);
   ~Camera();

 protected:
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
   void closeEvent(QCloseEvent *event);

 private:
   Ui::Camera *ui;

   QCamera *camera;
   QCameraImageCapture *imageCapture;
   QMediaRecorder *mediaRecorder;

   QImageEncoderSettings imageSettings;
   QAudioEncoderSettings audioSettings;
   QVideoEncoderSettings videoSettings;
   QString videoContainerFormat;

   bool isCapturingImage;
   bool applicationExiting;

   CS_SLOT_1(Private, void startCamera())
   CS_SLOT_2(startCamera)

   CS_SLOT_1(Private, void stopCamera())
   CS_SLOT_2(stopCamera)

   CS_SLOT_1(Private, void record())
   CS_SLOT_2(record)

   CS_SLOT_1(Private, void pause())
   CS_SLOT_2(pause)

   CS_SLOT_1(Private, void stop())
   CS_SLOT_2(stop)

   CS_SLOT_1(Private, void setMuted(bool muted))
   CS_SLOT_2(setMuted)

   CS_SLOT_1(Private, void toggleLock())
   CS_SLOT_2(toggleLock)

   CS_SLOT_1(Private, void takeImage())
   CS_SLOT_2(takeImage)

   CS_SLOT_1(Private, void configureCaptureSettings())
   CS_SLOT_2(configureCaptureSettings)

   CS_SLOT_1(Private, void displayViewfinder())
   CS_SLOT_2(displayViewfinder)

   CS_SLOT_1(Private, void setExposureCompensation(int index))
   CS_SLOT_2(setExposureCompensation)

   // slots
   void configureImageSettings();
   void configureVideoSettings();
   void displayCameraError();
   void displayCaptureError(int id, QCameraImageCapture::Error error, const QString &errorString);
   void displayCapturedImage();
   void displayRecorderError();
   void imageSaved(int id, const QString &fileName);
   void readyForCapture(bool ready);
   void processCapturedImage(int requestId, const QImage &img);
   void setCamera(const QCameraInfo &cameraInfo);
   void updateCaptureMode();
   void updateCameraDevice(QAction *action);
   void updateCameraState(QCamera::State state);
   void updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason);
   void updateRecorderState(QMediaRecorder::State state);
   void updateRecordTime();
};

#endif
