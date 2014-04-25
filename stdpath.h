/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
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

#ifndef STDPATH_H
#define STDPATH_H

#include "ui_stdpath.h"

#include <QString>
#include <QStandardPaths>
#include <QWidget>

class StdPath : public QWidget
{
   CS_OBJECT(StdPath)

   public:
       StdPath(QWidget *parent = 0);
       ~StdPath();

   private:
       Ui::StdPath *m_ui;
       
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

};

// add type to QVarient
Q_DECLARE_METATYPE(QStandardPaths::StandardLocation)

#endif
