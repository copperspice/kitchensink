/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "style_edit.h"
#include "style_dw.h"
#include "util.h"

#include <QString>
#include <QStyleFactory>

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


