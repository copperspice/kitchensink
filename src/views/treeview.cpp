/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "treeview.h"
#include "util.h"

#include <QGridLayout>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QTreeView>

#include <algorithm>

TreeView::TreeView()
   : QWidget()
{
   if (! this->createConnection() ) {
      QString msg = "** Create Database Error";
      throw msg;
   }

   setWindowTitle(tr("Tree View Model"));
   setMinimumSize(250, 425);

   // get sql data
   QList<TreeData> treeList = getData();

   // sort the data
   std::sort(treeList.begin(), treeList.end(), sortMe);

   QStandardItemModel *model = new QStandardItemModel();
   QStandardItem *rootItem = model->invisibleRootItem();
   QStandardItem *prevItem = nullptr;

   for (auto iter = treeList.begin(); iter != treeList.end(); ++iter) {

      QStandardItem *item = new QStandardItem;
      item->setText(iter->m_name);
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

      if (iter->m_parentId == 0) {
         rootItem->appendRow(item);
         prevItem = item;

      } else {
         prevItem->appendRow(item);
      }
   }

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Recipe Categories"));
   model->sort(0);

   QTreeView *treeView = new QTreeView();
   treeView->setModel(model);
   treeView->expandAll();

   //
   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(treeView);
   setLayout(mainLayout);
}

bool TreeView::createConnection()
{
   m_db = QSqlDatabase::addDatabase("QSQLITE", "treeViewDb");
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(nullptr, tr("Error Opening Database"),
            tr("Unable to establish a connection to the SQLite database."), QMessageBox::Cancel);

      return false;
   }

   QSqlQuery query(m_db);
   query.exec("CREATE TABLE food (catKey int PRIMARY KEY, catName varchar(30), catParentId int)");

   query.exec("insert into food values(101, 'Salad', 0)");
   query.exec("insert into food values(102, 'Bread', 0)");
   query.exec("insert into food values(103, 'KitchenSink Cookies', 104)");
   query.exec("insert into food values(104, 'Dessert', 0)");
   query.exec("insert into food values(105, 'Roasted Carrots', 114)");
   query.exec("insert into food values(106, 'Chicken', 0)");
   query.exec("insert into food values(107, 'Brownies', 104)");
   query.exec("insert into food values(108, 'Blueberry Muffins', 102)");
   query.exec("insert into food values(109, 'Chocolate Ice Cream', 104)");
   query.exec("insert into food values(110, 'Soup', 0)");
   query.exec("insert into food values(111, 'Corn Bread', 102)");
   query.exec("insert into food values(112, 'Thai Curry', 106)");
   query.exec("insert into food values(113, 'Mixed Greens', 101)");
   query.exec("insert into food values(114, 'Vegetables', 0)");
   query.exec("insert into food values(115, 'Pasta', 0)");
   query.exec("insert into food values(116, 'Greek', 0)");

   return true;
}

QList<TreeView::TreeData> TreeView::getData()
{
   QSqlQuery query(m_db);
   query.prepare("SELECT catKey, catName, catParentId FROM food");
   query.exec();

   QList<TreeData> retval;
   struct TreeData tmp;

   while (query.next()) {
      tmp.m_id       = query.value(0).toInt();
      tmp.m_name     = query.value(1).toString();
      tmp.m_parentId = query.value(2).toInt();

      retval.append(tmp);
   }

   return retval;
}

bool TreeView::sortMe(const TreeView::TreeData &s1, const TreeView::TreeData &s2)
{
   bool retval = false;

   if (s1.m_parentId == 0 && s2.m_parentId == 0)  {
      retval = s1.m_id < s2.m_id;

   } else if (s1.m_parentId == 0 && s2.m_parentId != 0) {

      if ( s1.m_id == s2.m_parentId ) {
         retval = true;
      } else {
         retval = s1.m_id < s2.m_parentId;
      }

   } else if (s1.m_parentId != 0 && s2.m_parentId == 0) {

      if (s1.m_parentId == s2.m_id) {
         retval = false;
      } else {
         retval = s1.m_parentId < s2.m_id;
      }

   } else if (s1.m_parentId != 0 && s2.m_parentId != 0)  {
      retval = s1.m_parentId < s2.m_parentId;
   }

   return retval;
}
