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

#include <ui_camera.h>

#include <camera.h>
#include <imagesettings.h>
#include <videosettings.h>

#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaService>
#include <QMediaRecorder>
#include <QMediaMetaData>

#include <QKeyEvent>
#include <QMessageBox>
#include <QPalette>
#include <QTimer>

CS_DECLARE_METATYPE(QCameraInfo)

Camera::Camera(QWidget *parent)
   : QMainWindow(parent), ui(new Ui::Camera), camera(nullptr), imageCapture(nullptr),
     mediaRecorder(nullptr), isCapturingImage(false), applicationExiting(false)
{
   ui->setupUi(this);

   // camera devices
   QActionGroup *videoDevicesGroup = new QActionGroup(this);
   videoDevicesGroup->setExclusive(true);

   if (QCameraInfo::defaultCamera().isNull()) {
      throw std::runtime_error("No camera found");
   }

   for (const QCameraInfo &cameraInfo : QCameraInfo::availableCameras()) {
      QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
      videoDeviceAction->setCheckable(true);
      videoDeviceAction->setData(QVariant::fromValue(cameraInfo));

      if (cameraInfo == QCameraInfo::defaultCamera()) {
         videoDeviceAction->setChecked(true);
      }

      ui->menuDevices->addAction(videoDeviceAction);
   }

   connect(videoDevicesGroup, &QActionGroup::triggered,    this, &Camera::updateCameraDevice);
   connect(ui->captureWidget, &QTabWidget::currentChanged, this, &Camera::updateCaptureMode);

   setCamera(QCameraInfo::defaultCamera());
}

Camera::~Camera()
{
   delete mediaRecorder;
   delete imageCapture;
   delete camera;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
   delete camera;
   delete mediaRecorder;
   delete imageCapture;

   camera        = new QCamera(cameraInfo);
   mediaRecorder = new QMediaRecorder(camera);
   imageCapture  = new QCameraImageCapture(camera);

   connect(camera, &QCamera::stateChanged, this, &Camera::updateCameraState);
   connect(camera, &QCamera::error,        this, &Camera::displayCameraError);

   connect(mediaRecorder, &QMediaRecorder::stateChanged,    this, &Camera::updateRecorderState);
   connect(mediaRecorder, &QMediaRecorder::durationChanged, this, &Camera::updateRecordTime);
   connect(mediaRecorder, &QMediaRecorder::error,           this, &Camera::displayRecorderError);

   mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QString("Test Title")));

   connect(ui->exposureCompensation, &QSlider::valueChanged, this, &Camera::setExposureCompensation);

   camera->setViewfinder(ui->viewfinder);

   updateCameraState(camera->state());
   updateLockStatus(camera->lockStatus(), QCamera::UserRequest);
   updateRecorderState(mediaRecorder->state());

   connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &Camera::readyForCapture);
   connect(imageCapture, &QCameraImageCapture::imageCaptured,          this, &Camera::processCapturedImage);
   connect(imageCapture, &QCameraImageCapture::imageSaved,             this, &Camera::imageSaved);
   connect(imageCapture, &QCameraImageCapture::error,                  this, &Camera::displayCaptureError);

   connect(camera, static_cast<void (QCamera::*)(QCamera::LockStatus, QCamera::LockChangeReason)>(&QCamera::lockStatusChanged),
           this, &Camera::updateLockStatus);

   ui->captureWidget->setTabEnabled(0, (camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
   ui->captureWidget->setTabEnabled(1, (camera->isCaptureModeSupported(QCamera::CaptureVideo)));

   updateCaptureMode();
   camera->start();
}

void Camera::keyPressEvent(QKeyEvent *event)
{
   if (event->isAutoRepeat()) {
      return;
   }

   switch (event->key()) {
      case Qt::Key_CameraFocus:
         displayViewfinder();
         camera->searchAndLock();
         event->accept();
         break;

      case Qt::Key_Camera:
         if (camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();

         } else {
            if (mediaRecorder->state() == QMediaRecorder::RecordingState) {
               stop();
            } else {
               record();
            }
         }

         event->accept();
         break;

      default:
         QMainWindow::keyPressEvent(event);
   }
}

void Camera::keyReleaseEvent(QKeyEvent *event)
{
   if (event->isAutoRepeat()) {
      return;
   }

   switch (event->key()) {
      case Qt::Key_CameraFocus:
         camera->unlock();
         break;

      default:
         QMainWindow::keyReleaseEvent(event);
   }
}

void Camera::updateRecordTime()
{
   QString str = QString("Recorded %1 sec").formatArg(mediaRecorder->duration() / 1000);
   ui->statusbar->showMessage(str);
}

void Camera::processCapturedImage(int requestId, const QImage &img)
{
   (void) requestId;

   QImage scaledImage = img.scaled(ui->viewfinder->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

   ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

   // Display captured image for 4 seconds.
   displayCapturedImage();
   QTimer::singleShot(4000, this, SLOT(displayViewfinder()));
}

void Camera::configureCaptureSettings()
{
   switch (camera->captureMode()) {

      case QCamera::CaptureStillImage:
         configureImageSettings();
         break;

      case QCamera::CaptureVideo:
         configureVideoSettings();
         break;

      default:
         break;
   }
}

void Camera::configureVideoSettings()
{
   VideoSettings settingsDialog(mediaRecorder);

   settingsDialog.setAudioSettings(audioSettings);
   settingsDialog.setVideoSettings(videoSettings);
   settingsDialog.setFormat(videoContainerFormat);

   if (settingsDialog.exec()) {
      audioSettings = settingsDialog.audioSettings();
      videoSettings = settingsDialog.videoSettings();
      videoContainerFormat = settingsDialog.format();

      mediaRecorder->setEncodingSettings(
         audioSettings,
         videoSettings,
         videoContainerFormat);
   }
}

void Camera::configureImageSettings()
{
   ImageSettings settingsDialog(imageCapture);

   settingsDialog.setImageSettings(imageSettings);

   if (settingsDialog.exec()) {
      imageSettings = settingsDialog.imageSettings();
      imageCapture->setEncodingSettings(imageSettings);
   }
}

void Camera::record()
{
   mediaRecorder->record();
   updateRecordTime();
}

void Camera::pause()
{
   mediaRecorder->pause();
}

void Camera::stop()
{
   mediaRecorder->stop();
}

void Camera::setMuted(bool muted)
{
   mediaRecorder->setMuted(muted);
}

void Camera::toggleLock()
{
   switch (camera->lockStatus()) {
      case QCamera::Searching:
      case QCamera::Locked:
         camera->unlock();
         break;
      case QCamera::Unlocked:
         camera->searchAndLock();
   }
}

void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
   QColor indicationColor = Qt::black;

   switch (status) {
      case QCamera::Searching:
         indicationColor = Qt::yellow;
         ui->statusbar->showMessage(tr("Focusing..."));
         ui->lockButton->setText(tr("Focusing..."));
         break;
      case QCamera::Locked:
         indicationColor = Qt::darkGreen;
         ui->lockButton->setText(tr("Unlock"));
         ui->statusbar->showMessage(tr("Focused"), 2000);
         break;
      case QCamera::Unlocked:
         indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
         ui->lockButton->setText(tr("Focus"));
         if (reason == QCamera::LockFailed) {
            ui->statusbar->showMessage(tr("Focus Failed"), 2000);
         }
   }

   QPalette palette = ui->lockButton->palette();
   palette.setColor(QPalette::ButtonText, indicationColor);
   ui->lockButton->setPalette(palette);
}

void Camera::takeImage()
{
   isCapturingImage = true;
   imageCapture->capture();
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
   (void) id;
   (void) error;

   QMessageBox::warning(this, tr("Image Capture Error"), errorString);
   isCapturingImage = false;
}

void Camera::startCamera()
{
   camera->start();
}

void Camera::stopCamera()
{
   camera->stop();
}

void Camera::updateCaptureMode()
{
   int tabIndex = ui->captureWidget->currentIndex();
   QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;

   if (camera->isCaptureModeSupported(captureMode)) {
      camera->setCaptureMode(captureMode);
   }
}

void Camera::updateCameraState(QCamera::State state)
{
   switch (state) {
      case QCamera::ActiveState:
         ui->actionStartCamera->setEnabled(false);
         ui->actionStopCamera->setEnabled(true);
         ui->captureWidget->setEnabled(true);
         ui->actionSettings->setEnabled(true);
         break;

      case QCamera::UnloadedState:
      case QCamera::LoadedState:
         ui->actionStartCamera->setEnabled(true);
         ui->actionStopCamera->setEnabled(false);
         ui->captureWidget->setEnabled(false);
         ui->actionSettings->setEnabled(false);
         break;
   }
}

void Camera::updateRecorderState(QMediaRecorder::State state)
{
   switch (state) {
      case QMediaRecorder::StoppedState:
         ui->recordButton->setEnabled(true);
         ui->pauseButton->setEnabled(true);
         ui->stopButton->setEnabled(false);
         break;

      case QMediaRecorder::PausedState:
         ui->recordButton->setEnabled(true);
         ui->pauseButton->setEnabled(false);
         ui->stopButton->setEnabled(true);
         break;

      case QMediaRecorder::RecordingState:
         ui->recordButton->setEnabled(false);
         ui->pauseButton->setEnabled(true);
         ui->stopButton->setEnabled(true);
         break;
   }
}

void Camera::setExposureCompensation(int index)
{
   camera->exposure()->setExposureCompensation(index * 0.5);
}

void Camera::displayRecorderError()
{
   QMessageBox::warning(this, tr("Capture error"), mediaRecorder->errorString());
}

void Camera::displayCameraError()
{
   QMessageBox::warning(this, tr("Camera error"), camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
   setCamera(action->data().value<QCameraInfo>());
}

void Camera::displayViewfinder()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void Camera::displayCapturedImage()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void Camera::readyForCapture(bool ready)
{
   ui->takeImageButton->setEnabled(ready);
}

void Camera::imageSaved(int id, const QString &fileName)
{
   Q_UNUSED(id);
   Q_UNUSED(fileName);

   isCapturingImage = false;
   if (applicationExiting) {
      close();
   }
}

void Camera::closeEvent(QCloseEvent *event)
{
   if (isCapturingImage) {
      setEnabled(false);
      applicationExiting = true;
      event->ignore();
   } else {
      event->accept();
   }
}
