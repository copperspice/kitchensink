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

#include "dialogs.h"

#include <QDir>
#include <QErrorMessage>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QStringList>

#define MESSAGE  Dialogs::tr("<p>Message boxes have a caption, text, " \
   "and any number of buttons, each with standard or custom text." \
   "<p>Click a Button or the Esc button.")

Dialogs::Dialogs(QWidget *parent)
   : QWidget(parent), ui(new Ui::Dialogs)
{
   ui->setupUi(this);
   setWindowTitle(tr("Standard Dialogs"));

   ui->native_checkBox->setChecked(true);

   // signals
   connect(ui->integer_pushButton,    SIGNAL(clicked()), this, SLOT(setInteger()));
   connect(ui->double_pushButton,     SIGNAL(clicked()), this, SLOT(setDouble()));
   connect(ui->getItem_pushButton,    SIGNAL(clicked()), this, SLOT(setItem()));
   connect(ui->getText_pushButton,    SIGNAL(clicked()), this, SLOT(setText()));

   connect(ui->dir_pushButton,        SIGNAL(clicked()), this, SLOT(setExistingDirectory()));
   connect(ui->openFile_pushButton,   SIGNAL(clicked()), this, SLOT(setOpenFileName()));
   connect(ui->openFiles_pushButton,  SIGNAL(clicked()), this, SLOT(setOpenFileNames()));

   connect(ui->critical_pushButton,   SIGNAL(clicked()), this, SLOT(criticalMessage()));
   connect(ui->info_pushButton,       SIGNAL(clicked()), this, SLOT(informationMessage()));
   connect(ui->quest_pushButton,      SIGNAL(clicked()), this, SLOT(questionMessage()));
   connect(ui->warn_pushButton,       SIGNAL(clicked()), this, SLOT(warningMessage()));
   connect(ui->error_pushButton,      SIGNAL(clicked()), this, SLOT(errorMessage()));
}

Dialogs::~Dialogs()
{
   delete ui;
}

// 1
void Dialogs::setInteger()
{
   bool ok;
   int i = QInputDialog::getInt(this, tr("getInteger()"),
              tr("Percentage:"), 25, 0, 100, 1, &ok);

   if (ok) {
      ui->integer_lineEdit->setText(tr("%1%").formatArg(i));
   }
}

void Dialogs::setDouble()
{
   bool ok;
   double d = QInputDialog::getDouble(this, tr("getDouble()"),
              tr("Amount:"), 37.56, -10000, 10000, 2, &ok);

   if (ok) {
      ui->double_lineEdit->setText(QString("$%1").formatArg(d));
   }
}

void Dialogs::setItem()
{
   QStringList items;
   items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

   bool ok;
   QString item = QInputDialog::getItem(this, tr("getItem()"),
              tr("Season:"), items, 0, false, &ok);

   if (ok && !item.isEmpty()) {
      ui->getItem_lineEdit->setText(item);
   }
}

void Dialogs::setText()
{
   bool ok;
   QString text = QInputDialog::getText(this, tr("getText()"),
         tr("User name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

   if (ok && !text.isEmpty()) {
      ui->getText_lineEdit->setText(text);
   }
}

// 2
void Dialogs::setExistingDirectory()
{
   QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

   if (! ui->native_checkBox->isChecked()) {
      options |= QFileDialog::DontUseNativeDialog;
   }

   QString directory = QFileDialog::getExistingDirectory(this,
         tr("getExistingDirectory()"),ui->dir_lineEdit->text(),options);

   if (! directory.isEmpty()) {
      ui->dir_lineEdit->setText(directory);
   }
}

void Dialogs::setOpenFileName()
{
   QFileDialog::Options options;

   if (! ui->native_checkBox->isChecked()) {
      options |= QFileDialog::DontUseNativeDialog;
   }

   QString selectedFilter;
   QString fileName = QFileDialog::getOpenFileName(this,
         tr("getOpenFileName()"), ui->openFile_lineEdit->text(),
         tr("All Files (*);;Text Files (*.txt)"), &selectedFilter, options);

   if (! fileName.isEmpty()) {
      ui->openFile_lineEdit->setText(fileName);
   }
}

void Dialogs::setOpenFileNames()
{
   QFileDialog::Options options;

   if (! ui->native_checkBox->isChecked()) {
      options |= QFileDialog::DontUseNativeDialog;
   }

   QString selectedFilter;
   QStringList files = QFileDialog::getOpenFileNames(
         this, tr("getOpenFileNames()"), openFilesPath,
         tr("All Files (*);;Text Files (*.txt)"), &selectedFilter, options);

   if (files.count()) {
      openFilesPath = files[0];
      ui->openFiles_lineEdit->setText(QString("[%1]").formatArg(files.join(", ")));
   }
}

void Dialogs::criticalMessage()
{
   QMessageBox::StandardButton reply;
   reply = QMessageBox::critical(this, tr("Dialog Test: critical()"),
         MESSAGE,QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

   if (reply == QMessageBox::Abort) {
      ui->critical_lineEdit->setText(tr("Abort"));

   } else if (reply == QMessageBox::Retry) {
      ui->critical_lineEdit->setText(tr("Retry"));

   } else  {
      ui->critical_lineEdit->setText(tr("Ignore"));
   }
}

void Dialogs::informationMessage()
{
   QMessageBox::StandardButton reply;
   reply = QMessageBox::information(this, tr("Dialog Test: information()"), MESSAGE);

   if (reply == QMessageBox::Ok) {
      ui->info_lineEdit->setText(tr("OK"));
   } else {
      ui->info_lineEdit->setText(tr("Escape"));
   }
}

void Dialogs::questionMessage()
{
   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, tr("Dialog Test:  question()"),
           MESSAGE, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

   if (reply == QMessageBox::Yes) {
      ui->quest_lineEdit->setText(tr("Yes"));

   } else if (reply == QMessageBox::No)  {
      ui->quest_lineEdit->setText(tr("No"));

   } else {
      ui->quest_lineEdit->setText(tr("Cancel"));
   }
}

void Dialogs::warningMessage()
{
   QMessageBox msgBox(QMessageBox::Warning, tr("Dialog Test:  warning()"), MESSAGE, Qt::EmptyFlag, this);
   msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
   msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);

   if (msgBox.exec() == QMessageBox::AcceptRole) {
      ui->warn_lineEdit->setText(tr("Save Again"));

   } else {
      ui->warn_lineEdit->setText(tr("Continue"));
   }
}

void Dialogs::errorMessage()
{
   errorMessageDialog = new QErrorMessage(this);

   errorMessageDialog->showMessage(
            tr("This dialog shows and remembers error messages. "
               "If the checkbox is checked (as it is by default), "
               "the message will be shown again. If the user unchecks the box, the message "
               "will not appear again if QErrorMessage::showMessage() is called with the same message."));

   ui->error_lineEdit->setText(tr("If the box is unchecked, the message will not appear again."));
}
