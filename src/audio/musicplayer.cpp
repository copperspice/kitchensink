/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "musicplayer.h"
#include "util.h"

#include <QtGui>

MusicPlayer::MusicPlayer()
   : QWidget(), ui(new Ui::MusicPlayer)
{
   // configure Phonon
   m_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);

   if (! m_audioOutput->pluginLoaded())  {
      // new method in CopperSpice, plugin did not load

      ksMsg("Unable to load Audio plugin. Program may terminate.");
      m_loaded = false;
      return;
   }

   m_mediaObject = new Phonon::MediaObject(this);
   m_mediaObject->setTickInterval(1000);

   // used when adding files to the music list
   m_metaParser = new Phonon::MediaObject(this);

   Phonon::createPath(m_mediaObject, m_audioOutput);
   m_loaded = true;

   // ui
   ui->setupUi(this);
   setWindowTitle(tr("Music Player"));

   setupActions();
   setupUi();

   m_seekSlider->setMediaObject(m_mediaObject);
   m_volumeSlider->setAudioOutput(m_audioOutput);

   // phonon Signals
   connect(m_mediaObject, SIGNAL(tick(qint64)),    this, SLOT(tick(qint64)));
   connect(m_mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

   connect(m_mediaObject, SIGNAL(currentSourceChanged(const Phonon::MediaSource &)),
           this, SLOT(sourceChanged(const Phonon::MediaSource &)));

   connect(m_mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
           this, SLOT(stateChanged(Phonon::State,Phonon::State)));

   // call back when meta data is parsed
   connect(m_metaParser, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
           this, SLOT(metaParserStateChanged(Phonon::State,Phonon::State)));

   // signals
   connect(ui->openFile_PB, SIGNAL(clicked()), this, SLOT(openFile()) );
   connect(ui->close_PB,    SIGNAL(clicked()), this, SLOT(close())    );
   connect(ui->aboutCs_PB,  SIGNAL(clicked()), this, SLOT(aboutCs())  );

   connect(ui->musicTable,  SIGNAL(clicked(const QModelIndex &)), this, SLOT(tableClicked(const QModelIndex &)) );

   connect(m_playAction,    SIGNAL(triggered()), m_mediaObject, SLOT(play()));
   connect(m_pauseAction,   SIGNAL(triggered()), m_mediaObject, SLOT(pause()) );
   connect(m_stopAction,    SIGNAL(triggered()), m_mediaObject, SLOT(stop()));
}

MusicPlayer::~MusicPlayer()
{
   delete ui;
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
   m_mediaObject->stop();
   m_mediaObject->clearQueue();
   event->accept();
}

bool MusicPlayer::loaded()
{
   return m_loaded;
}

void MusicPlayer::openFile()
{
   if (m_dir.isEmpty()) {
      m_dir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);
   }

   QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), m_dir);

   if (fileList.isEmpty()) {
      return;
   }

   // save the path for the next loop through
   QFileInfo temp = QFileInfo( fileList.at(0) );
   m_dir = temp.absolutePath();

   //
   int index = m_sources.size();

   foreach (QString fileName, fileList) {
      Phonon::MediaSource source = Phonon::MediaSource(fileName);
      m_sources.append(source);
   }

   if (! m_sources.isEmpty()) {
      m_metaParser->setCurrentSource(m_sources.at(index));
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

   m_seekSlider = new Phonon::SeekSlider(this);

   m_volumeSlider = new Phonon::VolumeSlider(this);
   m_volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

   m_timerLCD = new QLCDNumber;
   m_timerLCD->setSegmentStyle(QLCDNumber::Filled);
   m_timerLCD->setFrameStyle(QFrame::Panel);
   m_timerLCD->setLineWidth(1);
   m_timerLCD->display("00:00");

   QPalette palette;
   palette.setBrush(QPalette::Light, Qt::darkYellow);
   palette.setBrush(QPalette::Dark,  Qt::black);
   m_timerLCD->setPalette(palette);

   QHBoxLayout *seekerLayout = new QHBoxLayout;
   seekerLayout->addWidget(m_seekSlider);
   seekerLayout->addWidget(m_timerLCD);

   QHBoxLayout *playbackLayout = new QHBoxLayout;
   playbackLayout->addWidget(bar);
   playbackLayout->addStretch();
   playbackLayout->addWidget(m_volumeSlider);

   QVBoxLayout *layout = ui->verticalLayout;
   layout->addLayout(seekerLayout);
   layout->addLayout(playbackLayout);

   // table
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
}

void MusicPlayer::tick(qint64 time)
{
   QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
   m_timerLCD->display(displayTime.toString("mm:ss"));
}

void MusicPlayer::aboutToFinish()
{
   int index = m_sources.indexOf(m_mediaObject->currentSource()) + 1;

   if (m_sources.size() > index) {
      m_mediaObject->enqueue(m_sources.at(index));
   }
}

void MusicPlayer::sourceChanged(const Phonon::MediaSource &source)
{
   ui->musicTable->selectRow(m_sources.indexOf(source));
   m_timerLCD->display("00:00");
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
         m_timerLCD->display("00:00");
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

void MusicPlayer::metaParserStateChanged(Phonon::State newState, Phonon::State oldState)
{
    switch(newState) {

      case Phonon::ErrorState:
      {
         QString temp = m_metaParser->currentSource().fileName()
                + "\n\nFile may be damaged, corrupted, or contain an image file"
                + "\n\n" + m_metaParser->errorString();

         QMessageBox::warning(this, tr("Error Opening File(s)"), temp);

         while ( ! m_sources.isEmpty() ) {

            Phonon::MediaSource item = m_sources.takeLast();

            if (item == m_metaParser->currentSource()) {
               break;
            }
         }

         return;
      }

      case Phonon::StoppedState:
         break;

      case Phonon::PausedState:
         break;

      default:
         return;
   }

   if (m_metaParser->currentSource().type() == Phonon::MediaSource::Invalid) {
      return;
   }

   // take map data and display on the table
   QMultiMap<QString, QString> metaData = m_metaParser->metaData();

   QString title = metaData.value("TITLE");
   if ( title.isEmpty() ) {
      title = m_metaParser->currentSource().fileName();
   }

   QString album = metaData.value("ALBUM");
   if ( album.isEmpty() ) {
      album = "Information unavailable";
   }

   QStandardItem *titletItem = new QStandardItem(title);
   QStandardItem *artistItem = new QStandardItem(metaData.value("ARTIST"));
   QStandardItem *albumItem  = new QStandardItem(album);

   //
   int row = m_model->rowCount();
   m_model->insertRow(row);

   m_model->setItem(row, 0, titletItem);
   m_model->setItem(row, 1, artistItem);
   m_model->setItem(row, 2, albumItem);

   //
   ui->musicTable->selectRow(row);
   m_mediaObject->setCurrentSource(m_metaParser->currentSource());

   //
   int index = m_sources.indexOf(m_metaParser->currentSource()) + 1;

   if (m_sources.size() > index) {
      // on the last song
      m_metaParser->setCurrentSource(m_sources.at(index));
   }
}

void MusicPlayer::tableClicked(const QModelIndex &index)
{
   int row = index.row();

   if (row >= m_sources.size()) {
      return;
   }

   bool wasPlaying = (m_mediaObject->state() == Phonon::PlayingState);

   m_mediaObject->stop();
   m_mediaObject->clearQueue();
   m_mediaObject->setCurrentSource(m_sources[row]);

   if (wasPlaying) {
      m_mediaObject->play();
   } else {
      m_mediaObject->stop();
   }
}

