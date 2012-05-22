#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "ui_listview.h"

#include <QWidget>
#include <QSortFilterProxyModel>

class ListView : public QWidget
{
   Q_OBJECT
      
   public:
      explicit ListView(QWidget *parent = 0);
      ~ListView();
      
   private:
      Ui::ListView *ui;
      QStringList getData();
      QSortFilterProxyModel *m_proxyModel;

   private slots:
      void delRow();
      void addRow();

};

#endif // LISTVIEW_H
