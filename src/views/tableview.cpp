/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
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

#include "tableview.h"
#include "util.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QTableView>

TableView::TableView()
   : QWidget()
{
   if (! this->createConnection()) {
      QString msg = "** Create Database Error";
      throw msg;
   }

   setWindowTitle(tr("Table View Model"));
   setMinimumSize(850, 335);

   //
   QSqlTableModel *model = new QSqlTableModel(this, m_db);

   QStringList tableList = m_db.tables();
   model->setTable(tableList.at(0));

   QSqlError error = model->lastError();

   if ( error.isValid() )  {
      ksMsg( this, "Table View - SQL Error", error.text() );
   }

   model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   model->setSort(2, Qt::AscendingOrder);
   model->select();

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Biography"));

   //
   QTableView *view = new QTableView;
   view->setModel(model);

   view->setColumnWidth(0, 30);
   view->setColumnWidth(1, 100);
   view->setColumnWidth(2, 100);
   view->setColumnWidth(3, 500);
   view->horizontalHeader()->setStretchLastSection(true);

   QHBoxLayout *mainLayout = new QHBoxLayout;
   setLayout(mainLayout);

   mainLayout->addWidget(view);

   // adjust the height of each row
   view->resizeRowsToContents();
}

TableView::~TableView()
{
}

bool TableView::createConnection()
{
   static int counter = 100;
   QString tableName = "table" + QString::number(counter++);

   m_db = QSqlDatabase::addDatabase("QSQLITE", tableName);
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(nullptr, tr("Unable to Open Database"),
           tr("Unable to establish a connection to the database.\n"
              "This example requires SQLite.\n\n"), QMessageBox::Cancel);
      return false;
   }

   QSqlQuery query(m_db);
   query.exec("create table person (id int primary key, "
              "firstname varchar(20), lastname varchar(20), bio varchar(200))");

   query.exec("insert into person values(1, 'Gordon',  'Lightfoot', "
        "'Canadian folk singer, wrote ballads which told elaborate stories.')");

   query.exec("insert into person values(2, 'Whoopi',  'Goldberg', "
        "'Comedian, actress, talk show host, activist. She was on Star Trek NG, which is one of "
        "here most cherished experiences.')");

   query.exec("insert into person values(3, 'Paul', 'McCartney', "
         "'English singer and songwriter, key member of the Beatles')");

   query.exec("insert into person values(4, 'Dennis',  'Ritchie', "
         "'A key developer of the C programming language.')");

   query.exec("insert into person values(5, 'Robert',  'Heinlein', "
         "'Science fiction author.')");

   query.exec("insert into person values(6, 'Shirley', 'Corriher', "
         "'Biochemist, cookbook author, James Beard foundation award winner. If you want to understand "
         "the chemistry of baking her books are fantastic.')");

   query.exec("insert into person values(7, 'Vincent', 'Van Gogh', "
         "'Dutch painter with a very unique and special style, influenced modern art.')");


   return true;
}


/*
   QTableWidget            This class provides an "item based" table view with a default model.
                           The items in a QTableWidget are QTableWidgetItem(s)

   QTableView              This class provides a "model/view" implementation of a table.
                           With a QTableView a model must be supplied.

   Models for QTableView
      QSqlTableModel
      QSqlRelationalTableModel

*/
