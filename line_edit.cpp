/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
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
         ui->valid_lineEdit->setValidator(0);
         break;

      case 1:

         ui->valid_lineEdit->setText("2012-01-01");
         ui->valid_lineEdit->setCursorPosition(0);

         {  // validation yyyy-mm-dd
            QRegExp regExp("([0-9]{4})-(1[0-2]|0[1-9])-(3[0-1]|0[1-9]|[1-2][0-9])");
            QValidator *validator = new QRegExpValidator(regExp, this);
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

