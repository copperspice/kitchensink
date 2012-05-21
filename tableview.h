#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QSqlQuery>

class TableView : public QWidget
{
   Q_OBJECT

   public:
      TableView();
      QSqlDatabase m_db;

   private:
      bool createConnection();

};

#endif
