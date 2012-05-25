#ifndef TABLEWIDGET_VIEW_H
#define TABLEWIDGET_VIEW_H

#include "ui_tablewidget_view.h"

#include <QWidget>
#include <QStandardItemModel>

class TableWidget_View : public QWidget
{
   Q_OBJECT
      
   public:
      explicit TableWidget_View(QWidget *parent = 0);
      ~TableWidget_View();
      
   private:
      Ui::TableWidget_View *ui;
      QStandardItemModel *m_model;

      void setUpWidget();
      void setUpView();
};

#endif
