#ifndef STYLE_EDIT_H
#define STYLE_EDIT_H

#include "ui_style_edit.h"

#include <QDialog>

class Style_Edit : public QDialog
{
   Q_OBJECT

   public:
      Style_Edit(QWidget *parent, QWidget *dwFrom);
      ~Style_Edit();
      static QString getQssName();
      static QString loadStyleSheet(const QString &sheetName);

   private:
      Ui::Style_Edit *ui;
      QWidget *m_dwFrom;
      static QString qssName;
      static QString readStyleSheet(const QString &name);
      void closeEvent(QCloseEvent *event);

   public slots:
      void actionClose();

   private slots:
      void on_styleCombo_activated(const QString &styleName);
      void on_styleSheetCombo_activated(const QString &styleSheetName);
      void on_styleTextEdit_textChanged();
      void on_applyPB_clicked();
};

#endif
