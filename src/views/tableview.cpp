/***********************************************************************
*
* Copyright (c) 2012-2026 Barbara Geller
* Copyright (c) 2012-2026 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "tableview.h"
#include "util.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
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
   model->setTable("famousPeople");

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
   m_db = QSqlDatabase::addDatabase("QSQLITE", "peopleDB");
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(nullptr, tr("Error Opening Database"),
            tr("Unable to establish a connection to the SQLite database."), QMessageBox::Cancel);

      return false;
   }

   QSqlQuery query(m_db);
   query.exec("create table famousPeople (id int primary key, "
         "firstname varchar(20), lastname varchar(20), bio varchar(200))");

   query.exec("insert into famousPeople values(1, 'Gordon',  'Lightfoot', "
         "'Canadian folk singer, wrote ballads which told elaborate stories.')");

   query.exec("insert into famousPeople values(2, 'George', 'Carlin', "
         "'Comedian, author, social critic. Known for his opinions about politics, "
         "language, religion, and taboo subjects.')");

   query.exec("insert into famousPeople values(3, 'Stephen', 'Sondheim', "
         "'Composer and lyricist of musical theater. Credits include Sweeney Todd, "
         "Sunday in the Park with George, and Into the Woods.')");

   query.exec("insert into famousPeople values(4, 'Dennis',  'Ritchie', "
         "'A key developer of the C programming language.')");

   query.exec("insert into famousPeople values(5, 'Robert',  'Heinlein', "
         "'Science fiction author.')");

   query.exec("insert into famousPeople values(6, 'Shirley', 'Corriher', "
         "'Biochemist, cookbook author, James Beard foundation award winner. If you want to understand "
         "the chemistry of baking her books are fantastic.')");

   query.exec("insert into famousPeople values(7, 'Vincent', 'Van Gogh', "
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
