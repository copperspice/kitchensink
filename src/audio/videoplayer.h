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


#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QtGui/QMovie>
#include <QtGui/QWidget>
#include <QAbstractVideoSurface>

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

#endif
