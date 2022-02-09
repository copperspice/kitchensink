/***********************************************************************
*
* Copyright (c) 2012-2022 Barbara Geller
* Copyright (c) 2012-2022 Ansel Sermersheim
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

Dialogs::Dialogs(QWidget *parent)
   : QWidget(parent), ui(new Ui::Dialogs)
{
   ui->setupUi(this);
   setWindowTitle(tr("Standard Dialogs"));

   ui->native_checkBox->setChecked(true);

   connect(ui->integer_pushButton,   &QPushButton::clicked, this, &Dialogs::setInteger);
   connect(ui->double_pushButton,    &QPushButton::clicked, this, &Dialogs::setDouble);
   connect(ui->getItem_pushButton,   &QPushButton::clicked, this, &Dialogs::setItem);
   connect(ui->getText_pushButton,   &QPushButton::clicked, this, &Dialogs::setText);

   connect(ui->dir_pushButton,       &QPushButton::clicked, this, &Dialogs::setExistingDirectory);
   connect(ui->openFile_pushButton,  &QPushButton::clicked, this, &Dialogs::setOpenFileName);
   connect(ui->openFiles_pushButton, &QPushButton::clicked, this, &Dialogs::setOpenFileNames);

   connect(ui->critical_pushButton,  &QPushButton::clicked, this, &Dialogs::criticalMessage);
   connect(ui->info_pushButton,      &QPushButton::clicked, this, &Dialogs::informationMessage);
   connect(ui->quest_pushButton,     &QPushButton::clicked, this, &Dialogs::questionMessage);
   connect(ui->warn_pushButton,      &QPushButton::clicked, this, &Dialogs::warningMessage);
   connect(ui->error_pushButton,     &QPushButton::clicked, this, &Dialogs::errorMessage);
}

Dialogs::~Dialogs()
{
   delete ui;
}

// 1
void Dialogs::setInteger()
{
   bool ok;

   int value = QInputDialog::getInt(this, tr("getInteger()"),
         tr("Percentage:"), 25, 0, 100, 1, &ok);

   if (ok) {
      ui->integer_lineEdit->setText(QString("%1%").formatArg(value));
   }
}

void Dialogs::setDouble()
{
   bool ok;

   double value = QInputDialog::getDouble(this, tr("getDouble()"),
         tr("Unit Price:"), 37.56, -10000, 10000, 2, &ok);

   if (ok) {
      ui->double_lineEdit->setText(QString("$%1").formatArg(value));
   }
}

void Dialogs::setItem()
{
   QStringList itemList;
   itemList << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

   bool ok;

   QString data = QInputDialog::getItem(this, tr("getItem()"),
         tr("Select a Season:"), itemList, 0, false, &ok);

   if (ok && ! data.isEmpty()) {
      ui->getItem_lineEdit->setText(data);
   }
}

void Dialogs::setText()
{
   bool ok;

   QString data = QInputDialog::getText(this, tr("getText()"),
         tr("User name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

   if (ok && ! data.isEmpty()) {
      ui->getText_lineEdit->setText(data);
   }
}

// 2
void Dialogs::setExistingDirectory()
{
   QFileDialog::FileDialogOptions options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

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
   QFileDialog::FileDialogOptions options;

   if (! ui->native_checkBox->isChecked()) {
      options |= QFileDialog::DontUseNativeDialog;
   }

   QString selectedFilter;

   QString fileName = QFileDialog::getOpenFileName(this, tr("getOpenFileName()"), ui->openFile_lineEdit->text(),
         tr("All Files (*);;Text Files (*.txt)"), &selectedFilter, options);

   if (! fileName.isEmpty()) {
      ui->openFile_lineEdit->setText(fileName);
   }
}

void Dialogs::setOpenFileNames()
{
   QFileDialog::FileDialogOptions options;

   if (! ui->native_checkBox->isChecked()) {
      options |= QFileDialog::DontUseNativeDialog;
   }

   QString selectedFilter;
   QStringList files = QFileDialog::getOpenFileNames(this, tr("getOpenFileNames()"), openFilesPath,
         tr("All Files (*);;Text Files (*.txt)"), &selectedFilter, options);

   if (files.count()) {
      openFilesPath = files[0];
      ui->openFiles_lineEdit->setText(QString("[%1]").formatArg(files.join(", ")));
   }
}

void Dialogs::criticalMessage()
{
   QMessageBox::StandardButton reply;

   reply = QMessageBox::critical(this, tr("Critical"),
         tr("Body of a critical message. Click one of the buttons, X icon, or press Esc"),
         QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

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
   QMessageBox::information(this, tr("Information"),
         tr("Body of informative message. Click OK, X icon, or press Esc"));

   // since no buttons were passed, reply can only be OK
   ui->info_lineEdit->setText(tr("OK"));
}

void Dialogs::questionMessage()
{
   QMessageBox::StandardButton reply;

   reply = QMessageBox::question(this, tr("Question"),
         tr("Body of a question. Click one of the buttons, X icon, or press Esc"),
         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

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
   QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
         tr("Body of a warning message. Click one of the buttons, X icon, or press Esc"),
         Qt::EmptyFlag, this);

   msgBox.addButton(tr("Save"),   QMessageBox::AcceptRole);
   msgBox.addButton(tr("Ignore"), QMessageBox::RejectRole);

   if (msgBox.exec() == QMessageBox::AcceptRole) {
      ui->warn_lineEdit->setText(tr("Save"));

   } else {
      ui->warn_lineEdit->setText(tr("Ignore"));
   }
}

void Dialogs::errorMessage()
{
   if (errorDialog == nullptr) {
      errorDialog = new QErrorMessage(this);
   }

   errorDialog->showMessage(
         tr("If the checkbox remains checked, this message box will be displayed again. \n"
            "If unchecked, this message box will not appear again for the same error message."));

   ui->error_lineEdit->setText(tr("Message displayed"));
}
