/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "style_dw.h"
#include "style_edit.h"
#include "util.h"

#include <QCloseEvent>
#include <QFile>
#include <QString>
#include <QStyleFactory>

const static QString qsPath = ":/resources/";
QString Style_Edit::qssName = "Shiny";

Style_Edit::Style_Edit(QWidget *parent, QWidget *dwFrom)
   : QDialog(parent), ui(new Ui::Style_Edit)
{
   ui->setupUi(this);
   m_dwFrom = dwFrom;

   QString defaultStyle = QApplication::style()->metaObject()->className();

   QRegularExpression regExp(".(.*)\\+?Style", QPatternOption::ExactMatchOption);
   QRegularExpressionMatch match = regExp.match(defaultStyle);

   if (match.hasMatch()) {
      defaultStyle = match.captured(1);
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
   QApplication::instance()->setStyleSheet(styleSheet);

   return styleSheet;
}

QString Style_Edit::readStyleSheet(const QString &name)
{
   QFile file(qsPath + name.toLower() + ".qss");
   file.open(QFile::ReadOnly);

   QString styleSheet = file.readAll();

   return styleSheet;
}

void Style_Edit::on_styleCombo_activated(const QString &styleName)
{
   QApplication::instance()->setStyle(styleName);
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
   QApplication::instance()->setStyleSheet(ui->styleTextEdit->toPlainText());
   ui->applyPB->setEnabled(false);
}

void Style_Edit::actionClose()
{
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
