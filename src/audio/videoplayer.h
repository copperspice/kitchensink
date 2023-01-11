/***********************************************************************
*
* Copyright (c) 2012-2023 Barbara Geller
* Copyright (c) 2012-2023 Ansel Sermersheim
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

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#ifndef QT_NO_MULTIMEDIA

#include <QAbstractVideoSurface>
#include <QMovie>
#include <QWidget>

class VideoPlayer : public QWidget
{
   CS_OBJECT(VideoPlayer)

 public:
   VideoPlayer(QWidget *parent = nullptr);
   ~VideoPlayer();

 private:
   bool presentImage(const QImage &image);

   CS_SLOT_1(Private, void stateChanged(QMovie::MovieState state))
   CS_SLOT_2(stateChanged)

   CS_SLOT_1(Private, void frameChanged(int frame))
   CS_SLOT_2(frameChanged)

   CS_SLOT_1(Private, void actionClose())
   CS_SLOT_2(actionClose)

   QMovie m_movie;
   QAbstractVideoSurface *m_surface;
};

#endif   // ! QT_NO_MULTIMEDIA

#endif
