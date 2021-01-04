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

#include "tabdialog.h"

#include <QButtonGroup>
#include <QGridLayout>

TabDialog::TabDialog(QWidget *parent)
   : QWidget(parent), ui(new Ui::TabDialog)
{
   ui->setupUi(this);
   setWindowTitle(tr("Tab Dialog"));

   QGridLayout *mainLayout = ui->gridLayout;
   mainLayout->setContentsMargins(14, 14, 14, 9);
   mainLayout->setVerticalSpacing(14);

   //
   ui->tabWidget->setTabText(0, tr("Customer"));
   ui->tabWidget->setTabText(1, tr("Sandwich Selection"));
   ui->tabWidget->setTabText(2, tr("Sides && Desserts"));

   // forces the six rb on tab2 to be exclusive  
   QButtonGroup *temp = new QButtonGroup;
   temp->addButton(ui->coriander_RB);
   temp->addButton(ui->juniper_RB);
   temp->addButton(ui->poultryS_RB);
   temp->addButton(ui->rosemary_RB);
   temp->addButton(ui->salt_RB);
   temp->addButton(ui->kitchenSink_RB);

   //
   ui->dateEdit->setDate(QDate::currentDate());
   ui->dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
   ui->dateEdit->setReadOnly(true);
   ui->dateEdit->setFrame(false);

   ui->timeEdit->setTime(QTime::currentTime());
   ui->timeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
   ui->timeEdit->setReadOnly(true);
   ui->timeEdit->setFrame(false);

   // select the first tab
   ui->tabWidget->setCurrentIndex(0);

   // signals
   connect(ui->coriander_RB,   SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));
   connect(ui->juniper_RB,     SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));
   connect(ui->poultryS_RB,    SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));
   connect(ui->rosemary_RB,    SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));
   connect(ui->salt_RB,        SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));
   connect(ui->kitchenSink_RB, SIGNAL(clicked()), this, SLOT(actionRollYourOwn()));

   connect(ui->closePB,        SIGNAL(clicked()), this, SLOT(actionClose()));

   // force
   ui->ticketLineEdit->setFocus();
}

TabDialog::~TabDialog()
{
   delete ui;
}

void TabDialog::actionRollYourOwn()
{
   ui->cornBeef_CB->setChecked(false);
   ui->pastrami_CB->setChecked(false);
   ui->turkey_CB->setChecked(false);
   ui->chicken_CB->setChecked(false);
   ui->veggies_CB->setChecked(false);

   ui->avocado_CB->setChecked(false);
   ui->onions_CB->setChecked(false);
   ui->tomatoes_CB->setChecked(false);
   ui->bellPeppers_CB->setChecked(false);

   ui->lettuce_CB->setChecked(false);
   ui->mayo_CB->setChecked(false);
   ui->mustard_CB->setChecked(false);
   ui->pickles_CB->setChecked(false);
   ui->siracha_CB->setChecked(false);

   ui->cheddar_CB->setChecked(false);
   ui->jack_CB->setChecked(false);
   ui->provolone_CB->setChecked(false);
   ui->swiss_CB->setChecked(false);

   //
   QObject *temp = this->sender();

   if (temp == ui->coriander_RB )  {
      ui->veggies_CB->setChecked(true);
      ui->sourDough_RB->setChecked(true);

      ui->onions_CB->setChecked(true);
      ui->tomatoes_CB->setChecked(true);
      ui->bellPeppers_CB->setChecked(true);
      ui->provolone_CB->setChecked(true);
      ui->swiss_CB->setChecked(true);

   } else if ( temp == ui->juniper_RB)  {
      ui->pastrami_CB->setChecked(true);
      ui->ryeBread_RB->setChecked(true);

      ui->pickles_CB->setChecked(true);
      ui->siracha_CB->setChecked(true);

   } else if ( temp == ui->poultryS_RB)  {
      ui->turkey_CB->setChecked(true);
      ui->wheat_RB->setChecked(true);

      ui->avocado_CB->setChecked(true);
      ui->tomatoes_CB->setChecked(true);
      ui->lettuce_CB->setChecked(true);
      ui->swiss_CB->setChecked(true);

   } else if ( temp == ui->rosemary_RB)  {
      ui->chicken_CB->setChecked(true);
      ui->dutchCrunch_RB->setChecked(true);

      ui->onions_CB->setChecked(true);
      ui->tomatoes_CB->setChecked(true);
      ui->lettuce_CB->setChecked(true);
      ui->provolone_CB->setChecked(true);

   } else if ( temp == ui->salt_RB)  {
      ui->cornBeef_CB->setChecked(true);
      ui->ryeBread_RB->setChecked(true);

      ui->mustard_CB->setChecked(true);
      ui->swiss_CB->setChecked(true);

   } else if ( temp == ui->kitchenSink_RB)  {
      ui->cornBeef_CB->setChecked(true);
      ui->pastrami_CB->setChecked(true);
      ui->ryeBread_RB->setChecked(true);

      ui->avocado_CB->setChecked(true);
      ui->onions_CB->setChecked(true);
      ui->mustard_CB->setChecked(true);
      ui->pickles_CB->setChecked(true);
      ui->provolone_CB->setChecked(true);
      ui->swiss_CB->setChecked(true);
   }

}

void TabDialog::actionClose() {
   this->parentWidget()->close();
}
