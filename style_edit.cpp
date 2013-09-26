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
#include "style_edit.h"
#include "style_dw.h"

#include <QtGui>

const static QString qsPath = ":/resources/";
QString Style_Edit::qssName = "Shiny";

Style_Edit::Style_Edit(QWidget *parent, QWidget *dwFrom)
   : QDialog(parent), ui(new Ui::Style_Edit)
{
   ui->setupUi(this);
   m_dwFrom = dwFrom;

   QRegExp regExp(".(.*)\\+?Style");
   QString defaultStyle = QApplication::style()->metaObject()->className();

   if (regExp.exactMatch(defaultStyle)) {
      defaultStyle = regExp.cap(1);
   }

   // 1
   ui->styleCombo->addItems(QStyleFactory::keys());
   ui->styleCombo->setCurrentIndex(ui->styleCombo->findText(defaultStyle, Qt::MatchContains));

   // 2
   ui->styleSheetCombo->setCurrentIndex(ui->styleSheetCombo->findText(Style_Edit::qssName));

   QString styleSheet = this->readStyleSheet(Style_Edit::qssName);
   ui->styleTextEdit->setPlainText(styleSheet);
   ui->applyPB->setEnabled(false);

   // signal
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));
}

Style_Edit::~Style_Edit()
{
   delete ui;
}

QString Style_Edit::getQssName()
{
   return Style_Edit::qssName;
}

QString Style_Edit::loadStyleSheet(const QString &name)
{
   QString styleSheet = readStyleSheet(name);

   // new style sheet
   qApp->setStyleSheet(styleSheet);

   return styleSheet;
}

QString Style_Edit::readStyleSheet(const QString &name)
{
   QFile file(qsPath + name.toLower() + ".qss");
   file.open(QFile::ReadOnly);

   QString styleSheet = QLatin1String(file.readAll());

   return styleSheet;
}

void Style_Edit::on_styleCombo_activated(const QString &styleName)
{
   qApp->setStyle(styleName);
   ui->applyPB->setEnabled(false);
}

void Style_Edit::on_styleSheetCombo_activated(const QString &name)
{   
   Style_Edit::qssName = name;

   //
   QString styleSheet = this->loadStyleSheet(Style_Edit::qssName);

   ui->styleTextEdit->setPlainText(styleSheet);
   ui->applyPB->setEnabled(false);
}

void Style_Edit::on_styleTextEdit_textChanged()
{
   ui->applyPB->setEnabled(true);
}

void Style_Edit::on_applyPB_clicked()
{
   qApp->setStyleSheet(ui->styleTextEdit->toPlainText());
   ui->applyPB->setEnabled(false);
}

void Style_Edit::actionClose() {
   this->parentWidget()->close();
}

void Style_Edit::closeEvent(QCloseEvent *event)
{
   Style_DW *temp;
   temp = dynamic_cast<Style_DW *>(m_dwFrom);

   if (temp) {
      // saftey check
      temp->styleEditClose();
      event->accept();

   } else {
      // yes, this window will not close
      // however, closing DW_Style will close this window
      event->ignore();
   }
}


