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

#include "util.h"
#include "international.h"

#include <QStringListModel>
#include <QTranslator>

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

   //
   connect(ui->englishRB,  &QPushButton::clicked, this, &International::actionEnglish);
   connect(ui->frenchRB,   &QPushButton::clicked, this, &International::actionFrench);
   connect(ui->germanRB,   &QPushButton::clicked, this, &International::actionGerman);
   connect(ui->okPB,       &QPushButton::clicked, this, &International::actionClose);
   connect(ui->closePB,    &QPushButton::clicked, this, &International::actionClose);

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


