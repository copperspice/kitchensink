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

#include "util.h"
#include "international.h"

#include <QtGui>

static const QString qmPath = ":/resources";
QTranslator *International::m_translator = new QTranslator;

International::International()
   : QWidget(), ui(new Ui::International )
{
   ui->setupUi(this);
   setWindowTitle(tr("International"));

   // add the model
   m_model = new QStringListModel();
   ui->listView->setModel(m_model);

   // add data
   ui->nameCB->addItem("Amy Pond");
   ui->nameCB->addItem("Jack Harkness");
   ui->nameCB->addItem("River Song");
   ui->nameCB->addItem("Rose Tyler");
   ui->nameCB->addItem("Martha Jones");

   this->getListData();     

   // signals
   connect(ui->englishRB,  SIGNAL(clicked()), this, SLOT(actionEnglish()));
   connect(ui->frenchRB,   SIGNAL(clicked()), this, SLOT(actionFrench()));
   connect(ui->germanRB,   SIGNAL(clicked()), this, SLOT(actionGerman()));
   connect(ui->okPB,       SIGNAL(clicked()), this, SLOT(actionClose()));
   connect(ui->closePB,    SIGNAL(clicked()), this, SLOT(actionClose()));

   // force
   ui->nameCB->setFocus();
}

International::~International()
{
   delete ui;
}

void International::actionEnglish()
{
   if (! m_translator->load("qt_en.qm",qmPath)) {
      ksMsg(this, tr("International"), tr("Error while loading English international file."));
   }

   qApp->installTranslator(m_translator);
}

void International::actionFrench()
{
   if (! m_translator->load("qt_fr.qm",qmPath)) {
      ksMsg(this, tr("International"), tr("Error while loading French international file."));
   }

   qApp->installTranslator(m_translator);
}

void International::actionGerman()
{
   if (! m_translator->load("qt_de.qm",qmPath)) {
      ksMsg(this, tr("International"), tr("Error while loading German international file."));
   }

   qApp->installTranslator(m_translator);   
}

void International::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      ui->retranslateUi(this);
      this->getListData();
   }

   // calls parent, will change the title bar
   QWidget::changeEvent(event);
}

void International::getListData()
{
   QStringList list;
   list.append(tr("Chocolate Cake"));
   list.append(tr("Lemon Bars"));
   list.append(tr("Oatmeal Raisin Cookies"));
   list.append(tr("Peach Cobbler"));
   list.append(tr("Pumpkin Cheesecake"));
   list.append(tr("Sticky Buns"));

   m_model->setStringList(list);
}

void International::actionClose()
{
   this->parentWidget()->close();
}


