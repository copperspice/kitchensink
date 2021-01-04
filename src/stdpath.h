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

#ifndef STDPATH_H
#define STDPATH_H

#include "ui_stdpath.h"

#include <QStandardPaths>
#include <QWidget>

class StdPath : public QWidget
{
   CS_OBJECT(StdPath)

   public:
       StdPath(QWidget *parent = nullptr);
       ~StdPath();

   private:
       CS_SLOT_1(Private, void standardLocations(int index))
       CS_SLOT_2(standardLocations)

       CS_SLOT_1(Private, void writeableLocation(int index))
       CS_SLOT_2(writeableLocation)

       CS_SLOT_1(Private, void find())
       CS_SLOT_2(find)

       CS_SLOT_1(Private, void locate())
       CS_SLOT_2(locate)

       CS_SLOT_1(Private, void locateAll())
       CS_SLOT_2(locateAll)

       Ui::StdPath *m_ui;
};

#endif
