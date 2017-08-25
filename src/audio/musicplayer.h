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


#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "ui_musicplayer.h"

#include <QWidget>
#include <QAction>
#include <QList>
#include <QLCDNumber>
#include <QPushButton>
#include <QStandardItemModel>

#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

class MusicPlayer : public QWidget
{
   CS_OBJECT(MusicPlayer)

   public:
      MusicPlayer();
      ~MusicPlayer();

      bool loaded();

   private:
      void closeEvent(QCloseEvent *event);
      void setupActions();
      void setupUi();

      CS_SLOT_1(Private, void openFile())
      CS_SLOT_2(openFile)

      CS_SLOT_1(Private, void aboutCs())
      CS_SLOT_2(aboutCs)

      CS_SLOT_1(Private, void close())
      CS_SLOT_2(close)

      CS_SLOT_1(Private, void stateChanged(Phonon::State newState,Phonon::State oldState))
      CS_SLOT_2(stateChanged)

      CS_SLOT_1(Private, void tick(qint64 time))
      CS_SLOT_2(tick)

      CS_SLOT_1(Private, void tableClicked(const QModelIndex & un_named_arg1))
      CS_SLOT_2(tableClicked)

      CS_SLOT_1(Private, void sourceChanged(const Phonon::MediaSource & source))
      CS_SLOT_2(sourceChanged)

      CS_SLOT_1(Private, void metaParserStateChanged(Phonon::State newState,Phonon::State oldState))
      CS_SLOT_2(metaParserStateChanged)

      CS_SLOT_1(Private, void aboutToFinish())
      CS_SLOT_2(aboutToFinish)

      Ui::MusicPlayer *ui;
      QStandardItemModel *m_model;
      QString m_dir;
      bool m_loaded;

      Phonon::AudioOutput *m_audioOutput;
      Phonon::MediaObject *m_mediaObject;
      Phonon::MediaObject *m_metaParser;

      Phonon::SeekSlider   *m_seekSlider;
      Phonon::VolumeSlider *m_volumeSlider;
      QLCDNumber *m_timerLCD;

      QList<Phonon::MediaSource> m_sources;

      QAction *m_playAction;
      QAction *m_pauseAction;
      QAction *m_stopAction;
};

#endif
