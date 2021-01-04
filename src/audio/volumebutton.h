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

#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QLabel>
#include <QMenu>
#include <QSlider>
#include <QToolButton>
#include <QWidget>

class VolumeButton : public QToolButton
{
   CS_OBJECT(VolumeButton)

   CS_PROPERTY_READ(volume,   volume)
   CS_PROPERTY_WRITE(volume,  setVolume)
   CS_PROPERTY_NOTIFY(volume, volumeChanged)

   public:
      explicit VolumeButton(QWidget *parent = nullptr);

      int volume() const;

      CS_SIGNAL_1(Public, void volumeChanged(int volume))
      CS_SIGNAL_2(volumeChanged,volume)

      // slots
      void increaseVolume();
      void descreaseVolume();
      void setVolume(int volume);

   private:
      QMenu   *menu   = nullptr;
      QLabel  *label  = nullptr;
      QSlider *slider = nullptr;
};

#endif
