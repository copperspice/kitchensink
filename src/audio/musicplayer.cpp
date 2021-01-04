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

#if ! defined(QT_NO_MULTIMEDIA)

#include "musicplayer.h"
#include "volumebutton.h"
#include "util.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QToolBar>
#include <QStandardPaths>
#include <QStyleFactory>

static QString formatTime(qint64 timeMilliSeconds);

MusicPlayer::MusicPlayer(QWidget *parent)
   : QWidget(parent), m_ui(new Ui::MusicPlayer)
{
   // user interface
   m_ui->setupUi(this);
   setWindowTitle(tr("Multimedia Music Player"));

   setupActions();
   setupUi();

   connect(m_ui->openFile_PB, &QPushButton::clicked, this, &MusicPlayer::openFile);
   connect(m_ui->close_PB,    &QPushButton::clicked, this, &MusicPlayer::close);
   connect(m_ui->aboutCs_PB,  &QPushButton::clicked, this, &MusicPlayer::aboutCs);
   connect(m_ui->musicTable,  &QTableView::clicked,  this, &MusicPlayer::tableClicked);

   connect(m_playAction,      &QAction::triggered,   this, &MusicPlayer::togglePlayer);
   connect(m_pauseAction,     &QAction::triggered,   this, &MusicPlayer::togglePlayer);
   connect(m_stopAction,      &QAction::triggered,   this, &MusicPlayer::stopPlayer);

   connect(&m_mediaPlayer,    &QMediaPlayer::positionChanged, this,  &MusicPlayer::updateTime);
   connect(&m_mediaPlayer,    &QMediaPlayer::durationChanged, this,  &MusicPlayer::updateDuration);

   connect(&m_mediaPlayer, static_cast<void (QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),
                  this, &MusicPlayer::handleError);
}

MusicPlayer::~MusicPlayer()
{
   delete m_ui;
}

void MusicPlayer::aboutCs()
{
   QApplication::aboutCs();
}

void MusicPlayer::close() {
   this->parentWidget()->close();
}

void MusicPlayer::closeEvent(QCloseEvent *event)
{
   event->accept();
}

void MusicPlayer::openFile()
{
   if (m_dir.isEmpty()) {
      QStringList list = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);

      if (! list.isEmpty()) {
         m_dir = list.first();
      }
   }

   QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), m_dir);

   if (fileList.isEmpty()) {
      return;
   }

   // save the user selected path for the next loop through
   QFileInfo tmp = QFileInfo(fileList.at(0));
   m_dir = tmp.absolutePath();

   for (QString fileName : fileList) {
      QUrl url = QUrl::fromLocalFile(fileName);
      m_sources.append(url);

      std::shared_ptr<QMediaPlayer> tmpPlayer = std::make_shared<QMediaPlayer>();

      int row = m_model->rowCount();
      m_model->insertRow(row);

      QStandardItem *itemTitle    = new QStandardItem(url.fileName());
      QStandardItem *itemArtist   = new QStandardItem("");
      QStandardItem *itemAlbum    = new QStandardItem("");
      QStandardItem *itemDuration = new QStandardItem("00:00");

      m_model->setItem(row, 0, itemTitle);
      m_model->setItem(row, 1, itemArtist);
      m_model->setItem(row, 2, itemAlbum);
      m_model->setItem(row, 3, itemDuration);

      // if you want to capture m_model in the lambda use a generalized capture: model = m_model

      connect(tmpPlayer.get(), &QMediaPlayer::metaDataAvailableChanged, this,
                  [ tmpPlayer, url, itemTitle, itemArtist, itemAlbum, itemDuration]( )
         {

            QString title    = url.fileName();
            QString artist   = "Not Available";
            QString album    = "Not Available";
            QString duration = "00:00";

            if (tmpPlayer->isMetaDataAvailable()) {
               title    = tmpPlayer->metaData("Title").toString();
               artist   = tmpPlayer->metaData("Author").toString();
               album    = tmpPlayer->metaData("AlbumTitle").toString();
               duration = formatTime(tmpPlayer->duration());
            }

            itemTitle->setText(title);
            itemArtist->setText(artist);
            itemAlbum->setText(album);
            itemDuration->setText(duration);
         });

      // wait until the connect is configured
      tmpPlayer->setMedia(url);
   }

   if (m_mediaPlayer.state() != QMediaPlayer::PlayingState) {
      m_playAction->setEnabled(true);
      m_pauseAction->setEnabled(false);
      m_stopAction->setEnabled(false);
   }
}

void MusicPlayer::setupActions()
{
   m_playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
   m_playAction->setShortcut(tr("Ctrl+P"));
   m_playAction->setDisabled(true);

   m_pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
   m_pauseAction->setShortcut(tr("Ctrl+A"));
   m_pauseAction->setDisabled(true);

   m_stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
   m_stopAction->setShortcut(tr("Ctrl+S"));
   m_stopAction->setDisabled(true);
}

void MusicPlayer::setupUi()
{
   QToolBar *bar = new QToolBar;
   bar->addAction(m_playAction);
   bar->addAction(m_pauseAction);
   bar->addAction(m_stopAction);

   m_slider = new QSlider(Qt::Horizontal, this);
   m_slider->setEnabled(false);
   m_slider->setToolTip(tr("Seek"));
   m_slider->setStyle(QStyleFactory::create("Fusion"));
   connect(m_slider, &QAbstractSlider::valueChanged, this, &MusicPlayer::setSlider);

   m_labelTime = new QLabel(tr("00:00"), this);
   m_labelTime->setMinimumWidth(m_labelTime->sizeHint().width());
   m_labelTime->setFrameStyle(QFrame::Panel);

   m_status = new QLabel("", this);
   m_status->setWordWrap(true);

   m_volumeButton = new VolumeButton(this);
   m_volumeButton->setToolTip(tr("Adjust volume"));
   m_volumeButton->setVolume(m_mediaPlayer.volume());
   connect(m_volumeButton, &VolumeButton::volumeChanged, &m_mediaPlayer, &QMediaPlayer::setVolume);

   QHBoxLayout *seekerLayout = new QHBoxLayout;
   seekerLayout->addWidget(m_slider);
   seekerLayout->addSpacing(3);
   seekerLayout->addWidget(m_labelTime);

   QHBoxLayout *playbackLayout = new QHBoxLayout;
   playbackLayout->addWidget(bar);
   playbackLayout->addSpacing(10);
   playbackLayout->addWidget(m_status);
   playbackLayout->addStretch();
   playbackLayout->addWidget(m_volumeButton);

   QVBoxLayout *layout = m_ui->verticalLayout;
   layout->addLayout(seekerLayout);
   layout->addLayout(playbackLayout);

   // table
   m_model = new QStandardItemModel;
   m_model->setColumnCount(4);
   m_model->setHeaderData(0, Qt::Horizontal, tr("Title"));
   m_model->setHeaderData(1, Qt::Horizontal, tr("Artist"));
   m_model->setHeaderData(2, Qt::Horizontal, tr("Album"));
   m_model->setHeaderData(3, Qt::Horizontal, tr("Duration"));

   m_ui->musicTable->setModel(m_model);
   m_ui->musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
   m_ui->musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
   m_ui->musicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

   m_ui->musicTable->setColumnWidth(0, 225);
   m_ui->musicTable->setColumnWidth(1, 200);
   m_ui->musicTable->setColumnWidth(2, 200);
   m_ui->musicTable->horizontalHeader()->setStretchLastSection(true);
}

void MusicPlayer::setSlider(int position)
{
   // avoid seeking when the slider value change is triggered from updatePosition()
   if (qAbs(m_mediaPlayer.position() - position) > 99) {
      m_mediaPlayer.setPosition(position);
   }
}

void MusicPlayer::playUrl(const QUrl &url)
{
   m_mediaPlayer.setMedia(url);

   m_playAction->setEnabled(false);
   m_pauseAction->setEnabled(true);
   m_stopAction->setEnabled(true);

   m_mediaPlayer.play();
}

void MusicPlayer::togglePlayer()
{
   if (m_mediaPlayer.state() == QMediaPlayer::PlayingState) {
      m_mediaPlayer.pause();

      m_playAction->setEnabled(true);
      m_pauseAction->setEnabled(true);
      m_stopAction->setEnabled(false);

   } else if (m_mediaPlayer.state() == QMediaPlayer::PausedState) {
      m_mediaPlayer.play();

      m_playAction->setEnabled(false);
      m_pauseAction->setEnabled(true);
      m_stopAction->setEnabled(true);

   } else {
      int row;
      QModelIndex index = m_ui->musicTable->currentIndex();

      if (index.isValid()) {
         row = index.row();

      } else {
         row = m_sources.size() - 1;
      }

      m_current_row = row;
      playUrl(m_sources[row]);
   }
}

void MusicPlayer::stopPlayer()
{
   m_mediaPlayer.stop();

   m_playAction->setEnabled(true);
   m_pauseAction->setEnabled(false);
   m_stopAction->setEnabled(false);
}

QString formatTime(qint64 timeMilliSeconds)
{
   qint64 seconds = timeMilliSeconds / 1000;

   const qint64 minutes = seconds / 60;
   seconds -= minutes * 60;

   return QString("%1:%2").formatArg(minutes, 2, 10, '0').formatArg(seconds, 2, 10, '0');
}

void MusicPlayer::updateTime(qint64 position)
{
   m_slider->setValue(position);
   m_labelTime->setText(formatTime(position));
}

void MusicPlayer::updateDuration(qint64 duration)
{
   m_slider->setRange(0, duration);
   m_slider->setEnabled(duration > 0);
   m_slider->setPageStep(duration / 10);
}

void MusicPlayer::updateState(QMediaPlayer::State state)
{
   if (state == QMediaPlayer::PlayingState) {
     m_playAction->setToolTip(tr("Pause"));

   } else {
     m_playAction->setToolTip(tr("Play"));

   }
}

void MusicPlayer::tableClicked(const QModelIndex &index)
{
   int row = index.row();

   if (row >= m_sources.size()) {
      return;
   }

   m_current_row = row;
   playUrl(m_sources[row]);
}

void MusicPlayer::handleError()
{
   m_playAction->setEnabled(false);

   QString errorMsg = m_mediaPlayer.errorString();

   if (errorMsg.isEmpty()) {
      errorMsg = tr("Unknown error #%1").formatArg(int(m_mediaPlayer.error()));
   }

   m_status->setText(errorMsg);
}

QSize MusicPlayer::sizeHint() const
{
   return QSize(800, 300);
}

#endif
