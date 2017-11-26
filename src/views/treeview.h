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

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QSqlDatabase>
#include <QWidget>

template <typename T>
class QList;

class QString;

class TreeView : public QWidget
{
   CS_OBJECT(TreeView)

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

#endif
