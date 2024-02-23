/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#ifndef QT_NO_MULTIMEDIA

#include "ui_musicplayer.h"

#include <QList>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QUrl>
#include <QWidget>

class QAction;
class QLabel;
class QSlider;

class VolumeButton;

class MusicPlayer : public QWidget
{
   CS_OBJECT(MusicPlayer)

 public:
   MusicPlayer(QWidget *parent = nullptr);
   ~MusicPlayer();

 protected:
   void closeEvent(QCloseEvent *event) override;
   QSize sizeHint() const override;

 private:
   void setupActions();
   void setupUi();

   // slots
   void openFile();
   void aboutCs();
   void close();
   void tableClicked(const QModelIndex &index);

   void togglePlayer();
   void stopPlayer();
   void playUrl(const QUrl &url);
   void setSlider(int position);
   void updateTime(qint64 position);
   void updateDuration(qint64 duration);
   void updateState(QMediaPlayer::State state);
   void handleError();

   Ui::MusicPlayer *m_ui;
   QStandardItemModel *m_model;
   QString m_dir;
   int m_current_row;

   QMediaPlayer m_mediaPlayer;

   VolumeButton *m_volumeButton = nullptr;
   QSlider *m_slider            = nullptr;
   QLabel  *m_labelTime         = nullptr;
   QLabel  *m_status            = nullptr;

   QList<QUrl> m_sources;

   QAction *m_playAction;
   QAction *m_pauseAction;
   QAction *m_stopAction;
};

#endif // ! QT_NO_MULTIMEDIA

#endif
