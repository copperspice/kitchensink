#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QSqlQuery>

class TreeView : public QWidget
{
   public:
      TreeView();

   private:
      bool createConnection();
      QSqlDatabase m_db;

      struct struCat {
            int catKey;
            QString catName;
            int catParent;
      };


      QList<struCat> getData();      
      static bool sortMe(const TreeView::struCat &s1, const TreeView::struCat &s2);

};


#endif // TREEVIEW_H
