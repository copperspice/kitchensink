/**********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
};

#endif
