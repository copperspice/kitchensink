/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
***********************************************************************/

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QSqlDatabase>
#include <QWidget>
#include <qcontainerfwd.h>
#include <qstringfwd.h>

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
