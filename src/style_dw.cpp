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

#include "mainwindow.h"
#include "style_dw.h"
#include "style_edit.h"
#include "util.h"

#include <QMessageBox>

Style_DW::Style_DW(MainWindow *parent)
   : QMainWindow(parent), ui(new Ui::Style_DW)
{
   m_parent = parent;
   m_style  = nullptr;

   ui->setupUi(this);
   setWindowTitle("Style Sheets");

   ui->nameLabel->setProperty("class", QString("mandatory QLabel"));

   // add data
   ui->nameCB->addItem(tr("Amy Pond"));
   ui->nameCB->addItem(tr("Jack Harkness"));
   ui->nameCB->addItem(tr("River Song"));
   ui->nameCB->addItem(tr("Rose Tyler"));
   ui->nameCB->addItem(tr("Martha Jones"));

   //
   QString qssName = Style_Edit::getQssName();
   Style_Edit::loadStyleSheet(qssName);

   connect(ui->aboutPB, SIGNAL(clicked()), this, SLOT(actionAbout()));
   connect(ui->editPB,  SIGNAL(clicked()), this, SLOT(actionEdit()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));

   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));

   // force
   ui->nameCB->setFocus();
}

Style_DW::~Style_DW()
{
   delete ui;
}

void Style_DW::actionAbout()
{
   QMessageBox::about(this, tr("About Style Sheets"),
          tr("The <b>Style Sheet</b> example shows how widgets can be styled "
             "using Qt Style Sheets. Click <b>Edit/Select Style</b> to pop up the "
             "style editor and choose an existing style sheet or design your own."));
}

void Style_DW::actionEdit()
{
   m_style = new Style_Edit(m_parent, this);
   m_parent->addMdiChild(m_style);
}

void Style_DW::actionClose() {

   // close child window if open
   if (m_style != nullptr) {
      m_style->actionClose();
   }

   this->parentWidget()->close();
}

void Style_DW::styleEditClose()
{
   // marks the style_edit window closed
   m_style = nullptr;
}

void Style_DW::closeEvent(QCloseEvent *event)
{
   actionClose();
   QWidget::closeEvent(event);
}

