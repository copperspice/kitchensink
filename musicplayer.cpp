/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
***************************************************************************/

#include "musicplayer.h"
#include "util.h"

#include <QtGui>

MusicPlayer::MusicPlayer()
   : QMainWindow(), ui(new Ui::MusicPlayer)
{
   ui->setupUi(this);
   setWindowTitle(tr("Music Player"));

   // configure Phonon
   m_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
   m_mediaObject = new Phonon::MediaObject(this);
   m_metaInfo    = new Phonon::MediaObject(this);

   Phonon::createPath(m_mediaObject, m_audioOutput);

   //
   setupActions();
   setupUi();

   m_mediaObject->setTickInterval(1000);

   // Phonon Signals
   connect(m_mediaObject, SIGNAL(tick(qint64)),    this, SLOT(tick(qint64)));
   connect(m_mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

   connect(m_mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
           this, SLOT(stateChanged(Phonon::State,Phonon::State)));

   connect(m_mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
           this, SLOT(sourceChanged(Phonon::MediaSource)));   

   connect(m_metaInfo, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
           this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));


   // signals
   connect(m_playAction,    SIGNAL(triggered()), m_mediaObject, SLOT(play()));
   connect(m_pauseAction,   SIGNAL(triggered()), m_mediaObject, SLOT(pause()) );
   connect(m_stopAction,    SIGNAL(triggered()), m_mediaObject, SLOT(stop()));

   connect(ui->musicTable,  SIGNAL(clicked(const QModelIndex &)), this, SLOT(tableClicked(const QModelIndex &)) );

   connect(ui->actionAbout, SIGNAL(triggered()), SLOT(actionAbout()));
   connect(ui->actionExit,  SIGNAL(triggered()), SLOT(actionClose()));

   // adjust the size
   QSize size = this->size();
   this->setMinimumSize( size.width()+200, size.height() );
}

MusicPlayer::~MusicPlayer()
{
   delete ui;
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

   //
   m_seekSlider = new Phonon::SeekSlider(this);
   m_seekSlider->setMediaObject(m_mediaObject);

   //
   m_volumeSlider = new Phonon::VolumeSlider(this);
   m_volumeSlider->setAudioOutput(m_audioOutput);
   m_volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

   //  
   QPalette palette;
   palette.setBrush(QPalette::Light, Qt::darkGray);
   palette.setBrush(QPalette::Dark,  Qt::darkYellow);

   ui->timerLCD->setPalette(palette);
   ui->timerLCD->display("00:00");

   //
   m_model = new QStandardItemModel;
   m_model->setColumnCount(3);
   m_model->setHeaderData(0, Qt::Horizontal, tr("Title"));
   m_model->setHeaderData(1, Qt::Horizontal, tr("Artist"));
   m_model->setHeaderData(2, Qt::Horizontal, tr("Album"));

   ui->musicTable->setModel(m_model);   
   ui->musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->musicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

   ui->musicTable->setColumnWidth(0, 175);
   ui->musicTable->setColumnWidth(1, 175);
   ui->musicTable->horizontalHeader()->setStretchLastSection(true);

   //
   QHBoxLayout *seekerLayout = new QHBoxLayout;
   seekerLayout->addWidget(m_seekSlider);
   seekerLayout->addWidget(ui->timerLCD);

   QHBoxLayout *playbackLayout = new QHBoxLayout;
   playbackLayout->addWidget(bar);
   playbackLayout->addStretch();   
   playbackLayout->addWidget(m_volumeSlider);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(ui->musicTable);
   mainLayout->addLayout(seekerLayout);
   mainLayout->addLayout(playbackLayout);

   QWidget *widget = new QWidget;
   widget->setLayout(mainLayout);
   setCentralWidget(widget);
}

void MusicPlayer::on_actionOpen_triggered()
{
   if (m_dir.isEmpty()) {
      m_dir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);
   }

   QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), m_dir);

   if (files.isEmpty()) {
      return;
   }

   // save the path for the next loop through
   QFileInfo x = QFileInfo( files.at(0) );
   m_dir = x.absolutePath();

   //
   int index = m_sources.size();

   foreach (QString string, files) {
      Phonon::MediaSource source = Phonon::MediaSource(string);
      m_sources.append(source);
   }

   if (! m_sources.isEmpty()) {
      m_metaInfo->setCurrentSource(m_sources.at(index));
   }

}

void MusicPlayer::actionClose() {
   this->parentWidget()->close();
}

void MusicPlayer::actionAbout()
{
   QMessageBox::information(this, tr("About Music Player"),
      tr("This example shows how to use Phonon Multimedia Framework."));
}

void MusicPlayer::stateChanged(Phonon::State newState, Phonon::State oldState)
{
   switch (newState) {

      case Phonon::ErrorState:
         if (m_mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("Fatal Error"), m_mediaObject->errorString());
         } else {
            QMessageBox::warning(this, tr("Error"), m_mediaObject->errorString());
         }
         break;

      case Phonon::PlayingState:
         m_playAction->setEnabled(false);
         m_pauseAction->setEnabled(true);
         m_stopAction->setEnabled(true);
         break;

      case Phonon::StoppedState:
         m_stopAction->setEnabled(false);
         m_playAction->setEnabled(true);
         m_pauseAction->setEnabled(false);
         ui->timerLCD->display("00:00");
         break;

      case Phonon::PausedState:
         m_pauseAction->setEnabled(false);
         m_stopAction->setEnabled(true);
         m_playAction->setEnabled(true);
         break;

      case Phonon::BufferingState:
         break;

      default:
         break;
   }
}

void MusicPlayer::tick(qint64 time)
{
   QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
   ui->timerLCD->display(displayTime.toString("mm:ss"));
}

void MusicPlayer::tableClicked(const QModelIndex &index)
{
   int row = index.row();

   //
   bool wasPlaying = m_mediaObject->state() == Phonon::PlayingState;

   m_mediaObject->stop();
   m_mediaObject->clearQueue();

   if (row >= m_sources.size()) {
      return;
   }

   m_mediaObject->setCurrentSource(m_sources[row]);

   if (wasPlaying) {
      m_mediaObject->play();

   } else {
     m_mediaObject->stop();
   }
}

void MusicPlayer::sourceChanged(const Phonon::MediaSource &source)
{
   ui->musicTable->selectRow(m_sources.indexOf(source));
   ui->timerLCD->display("00:00");
}

void MusicPlayer::metaStateChanged(Phonon::State newState, Phonon::State oldState)
{ 
   QMap<QString, QString> metaData = m_metaInfo->metaData();

   if (newState == Phonon::ErrorState) {
      QMessageBox::warning(this, tr("Error Opening File(s)"), m_metaInfo->currentSource().fileName() + "   " +  m_metaInfo->errorString());

      while (! m_sources.isEmpty() && !(m_sources.takeLast() == m_metaInfo->currentSource())) {
      }

      return;
   }

   if (newState != Phonon::StoppedState && newState != Phonon::PausedState) {
      return;
   }

   if (m_metaInfo->currentSource().type() == Phonon::MediaSource::Invalid) {
      return;
   }

   QString title = metaData.value("TITLE");
   if ( title.isEmpty() ) {
      title = m_metaInfo->currentSource().fileName();
   }

   QStandardItem *titletItem = new QStandardItem(title);
   QStandardItem *artistItem = new QStandardItem(metaData.value("ARTIST"));
   QStandardItem *albumItem  = new QStandardItem(metaData.value("ALBUM"));

   //
   int row = m_model->rowCount();
   m_model->insertRow(row);

   m_model->setItem(row, 0, titletItem);
   m_model->setItem(row, 1, artistItem);
   m_model->setItem(row, 2, albumItem);

   //
   ui->musicTable->selectRow(row);
   m_mediaObject->setCurrentSource(m_metaInfo->currentSource());

   //
   int index = m_sources.indexOf(m_metaInfo->currentSource()) + 1;

   if (m_sources.size() > index) {
      // put you on the last song
      m_metaInfo->setCurrentSource(m_sources.at(index));
   }

}

void MusicPlayer::aboutToFinish()
{
   int index = m_sources.indexOf(m_mediaObject->currentSource()) + 1;

   if (m_sources.size() > index) {
      m_mediaObject->enqueue(m_sources.at(index));
   }
}




