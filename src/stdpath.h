/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
       CS_SLOT_1(Private, void standardLocations(int un_named_arg1))
       CS_SLOT_2(standardLocations)

       CS_SLOT_1(Private, void writeableLocation(int un_named_arg1))
       CS_SLOT_2(writeableLocation)

       CS_SLOT_1(Private, void find())
       CS_SLOT_2(find)

       CS_SLOT_1(Private, void locate())
       CS_SLOT_2(locate)

       CS_SLOT_1(Private, void locateAll())
       CS_SLOT_2(locateAll)

       Ui::StdPath *m_ui;
};

// add type to QVarient
Q_DECLARE_METATYPE(QStandardPaths::StandardLocation)

#endif
