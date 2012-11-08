/**********************************************************************
*
* Copyright (c) 2012 Barbara Geller
* Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#include "util.h"
#include "treeview.h"

#include <QSqlTableModel>
#include <QSqlQuery>

#include <QTreeView>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QListIterator>

TreeView::TreeView() :
   QWidget()
{
   if (! this->createConnection() ) {
      QString msg = "** Create Database Error";
      throw msg;
   }

   setWindowTitle(tr("Tree View Model"));

   //
   QTreeView *treeView = new QTreeView();

   //
   QStandardItemModel *model = new QStandardItemModel();

   // get sql data
   QList<struCat> itemList;
   itemList = getData();

   // sort the qlist data
   qSort(itemList.begin(), itemList.end(), sortMe);

   // put qlist data in the tree
   QList<struCat>::iterator nK;

   QStandardItem *parentItem = model->invisibleRootItem();
   QStandardItem *lastParent = NULL;

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

   // adjust
   QSize size = this->size();
   this->setMinimumHeight( size.height() );
}

bool TreeView::createConnection()
{
   m_db = QSqlDatabase::addDatabase("QSQLITE", "tree");
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(0, tr("Cannot open database"),
           tr("Unable to establish a database connection.\n"
              "This example needs SQLite support. Please read "
              "the Qt SQL driver documentation for information on "
              "how to build it.\n\n"
              "Click Cancel to exit."), QMessageBox::Cancel);
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


