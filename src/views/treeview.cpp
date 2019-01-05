/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#include "treeview.h"
#include "util.h"

#include <QGridLayout>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlQuery>
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
   setMinimumSize(200, 350);

   QTreeView *treeView = new QTreeView();
   QStandardItemModel *model = new QStandardItemModel();

   // get sql data
   QList<struCat> itemList;
   itemList = getData();

   // sort the qlist data
   std::sort(itemList.begin(), itemList.end(), sortMe);

   // put qlist data in the tree
   QList<struCat>::iterator nK;

   QStandardItem *parentItem = model->invisibleRootItem();
   QStandardItem *lastParent = nullptr;

   for (nK = itemList.begin(); nK != itemList.end(); ++nK) {

      QStandardItem *item = new QStandardItem;
      item->setText(nK->catName);
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );

      if ( nK->catParent == 0 ) {
         parentItem->appendRow(item);

         // save this
         lastParent = item;

       }  else {
         lastParent->appendRow(item);
      }

   }

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Food Categories"));
   model->sort(0);

   treeView->setModel(model);
   treeView->expandAll();

   //
   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(treeView);
   setLayout(mainLayout);
}

bool TreeView::createConnection()
{
   static int counter = 100;
   QString treeName = "tree" + QString::number(counter++);

   m_db = QSqlDatabase::addDatabase("QSQLITE", treeName);
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(0, tr("Unable to Open Database"),
           tr("Unable to establish a connection to the database.\n"
              "This example requires SQLite.\n\n"), QMessageBox::Cancel);
      return false;
   }

   QSqlQuery query(m_db);
   query.exec("CREATE TABLE food (catKey int PRIMARY KEY, catName varchar(30), catParent int)");

   query.exec("insert into food values(101, 'Salad',        0   )");
   query.exec("insert into food values(102, 'Bread',        0   )");
   query.exec("insert into food values(103, 'Cookies',      104 )");
   query.exec("insert into food values(104, 'Dessert' ,     0   )");
   query.exec("insert into food values(105, 'Vegetables',   0   )");
   query.exec("insert into food values(106, 'Seafood',      0   )");
   query.exec("insert into food values(107, 'Chicken',      0   )");
   query.exec("insert into food values(108, 'Pastries',     104 )");
   query.exec("insert into food values(109, 'Muffins',      102 )");
   query.exec("insert into food values(110, 'Thanksgiving', 0   )");
   query.exec("insert into food values(111, 'Pasta',        101 )");
   query.exec("insert into food values(112, 'Greens',       101 )");

   return true;
}

QList<TreeView::struCat> TreeView::getData()
{
   QSqlQuery query(m_db);
   query.prepare("SELECT catKey, catName, catParent FROM food");
   query.exec();

   QList<struCat> itemList;
   struct struCat temp;

   while (query.next())  {

      temp.catKey    = query.value(0).toInt();
      temp.catName   = query.value(1).toString();
      temp.catParent = query.value(2).toInt();

      itemList.append(temp);
   }

   return itemList;
}

bool TreeView::sortMe(const TreeView::struCat &s1, const TreeView::struCat &s2)
{
   bool retVal;

   if ( s1.catParent == 0 && s2.catParent == 0)  {
      retVal = s1.catKey < s2.catKey;

   } else if ( s1.catParent == 0 && s2.catParent != 0 ) {

      if ( s1.catKey == s2.catParent ) {
         retVal = true;
      } else {
         retVal = s1.catKey < s2.catParent;
      }

   } else if ( s1.catParent != 0 && s2.catParent == 0 ) {

      if ( s1.catParent == s2.catKey ) {
         retVal = false;
      } else {
          retVal = s1.catParent < s2.catKey;
      }

   } else if ( s1.catParent != 0 && s2.catParent != 0 ) {
      retVal = s1.catParent < s2.catParent;
   }

   return retVal;

}


