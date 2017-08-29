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
   setMinimumSize(300, 350);

   //
   QSqlTableModel *model = new QSqlTableModel(this, m_db);

   QStringList tempX = m_db.tables();
   model->setTable(tempX.at(0));

   QSqlError error = model->lastError();

   if ( error.isValid() )  {
      ksMsg( this, "Table View - SQL Error", error.text() );
   }

   model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   model->setSort(2, Qt::AscendingOrder);
   model->select();

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));

   //
   QTableView *view = new QTableView;
   view->setModel(model);
   view->resizeColumnsToContents();

   QHeaderView *temp = view->horizontalHeader();
   temp->setStretchLastSection(true);

   QHBoxLayout *mainLayout = new QHBoxLayout;
   mainLayout->addWidget(view);
   setLayout(mainLayout);
}

TableView::~TableView()
{
   // need to close the model before the db can be closed
   // m_db.close();
}

bool TableView::createConnection()
{
   static int counter = 100;
   QString tableName = "table" + QString::number(counter++);

   m_db = QSqlDatabase::addDatabase("QSQLITE", tableName);
   m_db.setDatabaseName(":memory:");

   if (! m_db.open()) {
      QMessageBox::critical(0, tr("Unable to Open Database"),
           tr("Unable to establish a connection to the database.\n"
              "This example requires SQLite.\n\n"), QMessageBox::Cancel);
      return false;
   }

   QSqlQuery query(m_db);
   query.exec("create table person (id int primary key, "
              "firstname varchar(20), lastname varchar(20))");

   query.exec("insert into person values(101, 'Gordon',  'Lightfoot')");
   query.exec("insert into person values(102, 'Whoopi',  'Goldberg')");
   query.exec("insert into person values(103, 'George',  'Burns')");
   query.exec("insert into person values(104, 'Dennis',  'Ritchie')");
   query.exec("insert into person values(105, 'Robert',  'Heinlein')");
   query.exec("insert into person values(106, 'Shirley', 'Corriher')");

   /*
   query.exec("create table offices (id int primary key,"
              "country varchar(20),"
              "description varchar(100))");

   query.exec("insert into offices values(0,'USA','Cook')");
   */

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
