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

#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "ui_line_edit.h"

#include <QWidget>
#include <QLineEdit>

class LineEdit : public QWidget
{
    CS_OBJECT(LineEdit)

   public:
       LineEdit();
       ~LineEdit();
   
   private:
       Ui::LineEdit *ui;
   
       //QLineEdit *align_LineEdit;
       //QLineEdit *mask_LineEdit;
       //QLineEdit *password_LineEdit;
       //QLineEdit *valid_LineEdit;
       //QLineEdit *readonly_LineEdit;
   
       CS_SLOT_1(Private, void alignChanged(int data))
       CS_SLOT_2(alignChanged) 
   
       CS_SLOT_1(Private, void maskChanged(int data))
       CS_SLOT_2(maskChanged) 
   
       CS_SLOT_1(Private, void passwordChanged(int data))
       CS_SLOT_2(passwordChanged) 
   
       CS_SLOT_1(Private, void validChanged(int data))
       CS_SLOT_2(validChanged) 
   
       CS_SLOT_1(Private, void readonlyChanged(int data))
       CS_SLOT_2(readonlyChanged)    
};


#endif
