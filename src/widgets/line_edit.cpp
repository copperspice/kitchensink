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

#include "line_edit.h"
#include "ui_line_edit.h"

#include <QDoubleValidator>

LineEdit::LineEdit()
   : QWidget(), ui(new Ui::LineEdit)
{
   ui->setupUi(this);

   setWindowTitle(tr("QLineEdit Samples"));
   setMinimumSize(100,100);

   ui->align_lineEdit->setText("Sample menu availabe on line.");
   ui->align_lineEdit->setClearButtonEnabled(true);

   ui->readonly_lineEdit->setText("Sample menu availabe on line.");
   ui->readonly_lineEdit->setReadOnly(true);

   // signals
   connect(ui->align_comboBox,    SIGNAL(activated(int)), this, SLOT(alignChanged(int)));
   connect(ui->mask_comboBox,     SIGNAL(activated(int)), this, SLOT(maskChanged(int)));
   connect(ui->password_comboBox, SIGNAL(activated(int)), this, SLOT(passwordChanged(int)));
   connect(ui->valid_comboBox,    SIGNAL(activated(int)), this, SLOT(validChanged(int)));
   connect(ui->readonly_comboBox, SIGNAL(activated(int)), this, SLOT(readonlyChanged(int)));
}

LineEdit::~LineEdit()
{
   delete ui;
}

void LineEdit::alignChanged(int index)
{
   switch (index) {
      case 0:
         ui->align_lineEdit->setAlignment(Qt::AlignLeft);
         break;
      case 1:
         ui->align_lineEdit->setAlignment(Qt::AlignCenter);
         break;
      case 2:
         ui->align_lineEdit->setAlignment(Qt::AlignRight);
         break;
   }
}

void LineEdit::maskChanged(int index)
{
   ui->mask_lineEdit->setInputMask("");
   ui->mask_lineEdit->clear();

   switch (index) {
      case 0:
         ui->mask_lineEdit->setInputMask("");
         break;
      case 1:
         ui->mask_lineEdit->setInputMask("000.000.000.000;_");
         break;
      case 2:
         ui->mask_lineEdit->setInputMask(">NNNNN-NNNNN-NNNNN-NNNNN-NNNNN;#");
         break;
      case 3:
         ui->mask_lineEdit->setInputMask("(999) 999-9999");
         break;
      case 4:
         ui->mask_lineEdit->setInputMask("+99 9999 9999");
         break;
   }

}

void LineEdit::passwordChanged(int index)
{
   ui->password_lineEdit->clear();

   switch (index) {

      case 0:
         ui->password_lineEdit->setEchoMode(QLineEdit::Normal);
         break;
      case 1:
         ui->password_lineEdit->setEchoMode(QLineEdit::Password);
         break;
      case 2:
         ui->password_lineEdit->setEchoMode(QLineEdit::NoEcho);
         break;
      case 3:
         ui->password_lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
         break;
   }

}

void LineEdit::validChanged(int index)
{
   ui->valid_lineEdit->clear();

   switch (index) {
      case 0:
         ui->valid_lineEdit->setValidator(nullptr);
         break;

      case 1:

         ui->valid_lineEdit->setText("2012-01-01");
         ui->valid_lineEdit->setCursorPosition(0);

         {  // validation yyyy-mm-dd
            QRegularExpression regExp("([0-9]{4})-(1[0-2]|0[1-9])-(3[0-1]|0[1-9]|[1-2][0-9])");

            QValidator *validator = new QRegularExpressionValidator(regExp, this);
            ui->valid_lineEdit->setValidator(validator);
         }

         ui->valid_lineEdit->setInputMask("0000-00-00");

         break;

      case 2:
         ui->valid_lineEdit->setValidator(new QIntValidator(ui->valid_lineEdit));
         break;

      case 3:
         QDoubleValidator *validator = new QDoubleValidator(-9999.00, 9999.00, 2, ui->valid_lineEdit);
         validator->setNotation(QDoubleValidator::StandardNotation);

         ui->valid_lineEdit->setValidator(validator);
         break;
   }
}

void LineEdit::readonlyChanged(int index)
{
   switch (index) {
      case 0:
         ui->readonly_lineEdit->setReadOnly(true);
         break;

      case 1:
         ui->readonly_lineEdit->setReadOnly(false);
         break;
   }
}

