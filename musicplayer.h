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
****************************************************************************/

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "ui_musicplayer.h"

#include <QMainWindow>
#include <QList>
#include <QAction>
#include <QStandardItemModel>

#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

class MusicPlayer : public QMainWindow
{
   Q_OBJECT

   public:
      MusicPlayer();
      ~MusicPlayer();

   private:
      Ui::MusicPlayer *ui;
      QStandardItemModel *m_model;
      QString m_dir;

      Phonon::AudioOutput *m_audioOutput;
      Phonon::MediaObject *m_mediaObject;
      Phonon::MediaObject *m_metaParser;

      Phonon::SeekSlider   *m_seekSlider;
      Phonon::VolumeSlider *m_volumeSlider;

      QList<Phonon::MediaSource> m_sources;

      QAction *m_playAction;
      QAction *m_pauseAction;
      QAction *m_stopAction;

      void closeEvent(QCloseEvent *event);
      void setupActions();
      void setupUi();      

   private slots:
      void on_actionOpen_triggered();
      void actionAbout();
      void actionClose();

      void stateChanged(Phonon::State newState, Phonon::State oldState);
      void tick(qint64 time);
      void tableClicked(const QModelIndex &);
      void sourceChanged(const Phonon::MediaSource &source);
      void metaParserStateChanged(Phonon::State newState, Phonon::State oldState);
      void aboutToFinish();
};

#endif
