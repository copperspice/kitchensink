/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
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

#ifndef DIALOGS_H
#define DIALOGS_H

#include "ui_dialogs.h"

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QErrorMessage>

class Dialogs : public QWidget
{
   CS_OBJECT(Dialogs)

   public:
      Dialogs(QWidget *parent = 0);
      ~Dialogs();

   private:
      Ui::Dialogs *ui;
      QErrorMessage *errorMessageDialog;
      QString openFilesPath;

      CS_SLOT_1(Private, void setInteger())
      CS_SLOT_2(setInteger) 

      CS_SLOT_1(Private, void setDouble())
      CS_SLOT_2(setDouble) 

      CS_SLOT_1(Private, void setItem())
      CS_SLOT_2(setItem) 

      CS_SLOT_1(Private, void setText())
      CS_SLOT_2(setText) 

      CS_SLOT_1(Private, void setExistingDirectory())
      CS_SLOT_2(setExistingDirectory) 

      CS_SLOT_1(Private, void setOpenFileName())
      CS_SLOT_2(setOpenFileName) 

      CS_SLOT_1(Private, void setOpenFileNames())
      CS_SLOT_2(setOpenFileNames)       

      CS_SLOT_1(Private, void criticalMessage())
      CS_SLOT_2(criticalMessage) 

      CS_SLOT_1(Private, void informationMessage())
      CS_SLOT_2(informationMessage) 

      CS_SLOT_1(Private, void questionMessage())
      CS_SLOT_2(questionMessage) 

      CS_SLOT_1(Private, void warningMessage())
      CS_SLOT_2(warningMessage) 

      CS_SLOT_1(Private, void errorMessage())
      CS_SLOT_2(errorMessage) 
};

#endif
