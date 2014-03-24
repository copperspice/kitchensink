/**********************************************************************
*
* Copyright (c) 2012-2013 Barbara Geller
* Copyright (c) 2011-2012 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef TABLEWIDGET_VIEW_H
#define TABLEWIDGET_VIEW_H

#include "ui_tablewidget_view.h"

#include <QWidget>
#include <QStandardItemModel>

class TableWidget_View : public QWidget
{
   CS_OBJECT(TableWidget_View)
      
   public:
      explicit TableWidget_View(QWidget *parent = 0);
      ~TableWidget_View();
      
   private:
      Ui::TableWidget_View *ui;
      QStandardItemModel *m_model;

      void setUpWidget();
      void setUpView();

   private :
      CS_SLOT_1(Private, void tableClicked_W(int row,int col))
      CS_SLOT_2(tableClicked_W) 
      CS_SLOT_1(Private, void tableClicked_V(const QModelIndex & index))
      CS_SLOT_2(tableClicked_V) 
};

#endif
