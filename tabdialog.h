#ifndef TABDIALOG_H
#define TABDIALOG_H

#include "ui_tabdialog.h"
#include <QWidget>

class TabDialog : public QWidget
{
   Q_OBJECT

   public:
      TabDialog(QWidget *parent = 0);
      ~TabDialog();

   private:
      Ui::TabDialog *ui;

   private slots:
      void actionRollYourOwn();
      void actionClose();
};

#endif
