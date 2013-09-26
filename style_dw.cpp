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

#include "util.h"

#include "style_dw.h"
#include "style_edit.h"

#include <QMessageBox>

Style_DW::Style_DW(Mdi *parent)
   : QMainWindow(parent), ui(new Ui::Style_DW)
{
   m_parent = parent;
   m_style  = NULL;

   ui->setupUi(this);
   setWindowTitle("Style Sheets");

   ui->nameLabel->setProperty("class", "mandatory QLabel");

   // add data
   ui->nameCB->addItem(tr("Amy Pond"));
   ui->nameCB->addItem(tr("Jack Harkness"));
   ui->nameCB->addItem(tr("River Song"));
   ui->nameCB->addItem(tr("Rose Tyler"));
   ui->nameCB->addItem(tr("Martha Jones"));

   //
   QString qssName = Style_Edit::getQssName();
   Style_Edit::loadStyleSheet(qssName);

   connect(ui->okPB,    SIGNAL(clicked()), this, SLOT(actionOk()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));

   // force
   ui->nameCB->setFocus();
}

Style_DW::~Style_DW()
{
   delete ui;
}

void Style_DW::on_actionAbout_triggered()
{
   QMessageBox::about(this, tr("About Style Sheets"),
          tr("The <b>Style Sheet</b> example shows how widgets can be styled "
             "using Qt Style Sheets. Click <b>File|Edit Style Sheet</b> to pop up the "
             "style editor and choose an existing style sheet or design your own."));
}

void Style_DW::on_actionEditStyle_triggered()
{   
   m_style = new Style_Edit(m_parent, this);
   m_parent->addMdiChild(m_style);
}

void Style_DW::actionOk()
{
   ksMsg(this, "Style Sheets", "Ok button pressed. Closing Style Sheets.");
   this->actionClose();
}

void Style_DW::styleEditClose()
{
   // marks the style_edit window closed
   m_style  = NULL;
}

void Style_DW::actionClose() {

   // close child window if open
   if (m_style != NULL) {      
      m_style->actionClose();
   }

   this->parentWidget()->close();
}
