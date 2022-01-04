/***********************************************************************
*
* Copyright (c) 2012-2022 Barbara Geller
* Copyright (c) 2012-2022 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
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
