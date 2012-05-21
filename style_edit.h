#ifndef STYLESHEETEDITOR_H
#define STYLESHEETEDITOR_H

#include "ui_style_edit.h"

#include <QDialog>

class Style_Edit : public QDialog
{
      Q_OBJECT

   public:
      Style_Edit(QWidget *parent = 0);
      ~Style_Edit();
      static QString getQssName();
      static QString loadStyleSheet(const QString &sheetName);

   private slots:
      void on_styleCombo_activated(const QString &styleName);
      void on_styleSheetCombo_activated(const QString &styleSheetName);
      void on_styleTextEdit_textChanged();
      void on_applyButton_clicked();

   private:
      Ui::Style_Edit *ui;      
      static QString qssName;
      static QString readStyleSheet(const QString &name);
};

#endif
