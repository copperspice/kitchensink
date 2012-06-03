#include "util.h"
#include "style_edit.h"

#include <QtGui>

QString Style_Edit::qssName = "Shiny";

Style_Edit::Style_Edit(QWidget *parent)
   : QDialog(parent), ui(new Ui::Style_Edit)
{
   ui->setupUi(this);

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
   ui->applyButton->setEnabled(false);

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
   QFile file(":/qss/" + name.toLower() + ".qss");
   file.open(QFile::ReadOnly);

   QString styleSheet = QLatin1String(file.readAll());

   return styleSheet;
}

void Style_Edit::on_styleCombo_activated(const QString &styleName)
{
   qApp->setStyle(styleName);
   ui->applyButton->setEnabled(false);
}

void Style_Edit::on_styleSheetCombo_activated(const QString &name)
{   
   Style_Edit::qssName = name;

   //
   QString styleSheet = this->loadStyleSheet(Style_Edit::qssName);

   ui->styleTextEdit->setPlainText(styleSheet);
   ui->applyButton->setEnabled(false);
}

void Style_Edit::on_styleTextEdit_textChanged()
{
   ui->applyButton->setEnabled(true);
}

void Style_Edit::on_applyButton_clicked()
{
   qApp->setStyleSheet(ui->styleTextEdit->toPlainText());
   ui->applyButton->setEnabled(false);
}

void Style_Edit::actionClose() {
   this->parentWidget()->close();
}



