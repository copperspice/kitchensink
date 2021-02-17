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

#include "tablewidget_view.h"
#include "util.h"

#include <QSize>
#include <QStringList>
#include <QTableWidget>

TableWidget_View::TableWidget_View(QWidget *parent)
   : QWidget(parent), ui(new Ui::TableWidget_View)
{
   ui->setupUi(this);
   setWindowTitle("Table Widget / Table View");

   setUpWidget();
   setUpView();

   // this code appears in the UI generated file, shown here as an example
   // ui->splitter->setHandleWidth(10);

   // adjust size of the widget
   QSize size = this->size();
   setMinimumWidth( size.width() );
   setMinimumHeight( size.height() );
}

TableWidget_View::~TableWidget_View()
{
   delete ui;
}

void TableWidget_View::setUpWidget()
{
   QStringList headers;
   headers << tr("Name") << tr("Type") << tr("First Aired");

   // this code appears in the UI generated file, shown here as an example
   // tableWidget = new QTableWidget(0, 3);

   ui->tableWidget->setRowCount(0);
   ui->tableWidget->setColumnCount(3);

   // name the columns
   ui->tableWidget->setHorizontalHeaderLabels(headers);

   // resizes the last column automatically, shown here as an example
   // ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

   ui->tableWidget->setColumnWidth(0, 140);
   ui->tableWidget->setColumnWidth(0, 140);
   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

   ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

   // sorting should be set to false before adding data
   // following line is not required since default is false
   // ui->tableWidget->setSortingEnabled(false);

   // data
   int row = ui->tableWidget->rowCount();

   QTableWidgetItem *nameItem  = new QTableWidgetItem("The Good Wife");
   QTableWidgetItem *typeItem  = new QTableWidgetItem(tr("Drama/Legal"));
   QTableWidgetItem *airedItem = new QTableWidgetItem("2009");

   ui->tableWidget->insertRow(row);
   ui->tableWidget->setItem(row, 0, nameItem);
   ui->tableWidget->setItem(row, 1, typeItem);
   ui->tableWidget->setItem(row, 2, airedItem);

   //
   nameItem  = new QTableWidgetItem("Doctor Who");
   typeItem  = new QTableWidgetItem(tr("Science Fiction"));
   airedItem = new QTableWidgetItem("1963");

   ui->tableWidget->insertRow(row);
   ui->tableWidget->setItem(row, 0, nameItem);
   ui->tableWidget->setItem(row, 1, typeItem);
   ui->tableWidget->setItem(row, 2, airedItem);

   //
   nameItem  = new QTableWidgetItem("ER");
   typeItem  = new QTableWidgetItem(tr("Drama/Medical"));
   airedItem = new QTableWidgetItem("1994");

   ui->tableWidget->insertRow(row);
   ui->tableWidget->setItem(row, 0, nameItem);
   ui->tableWidget->setItem(row, 1, typeItem);
   ui->tableWidget->setItem(row, 2, airedItem);

   //
   nameItem  = new QTableWidgetItem("Friends");
   typeItem  = new QTableWidgetItem(tr("Comedy"));
   airedItem = new QTableWidgetItem("1994");

   ui->tableWidget->insertRow(row);
   ui->tableWidget->setItem(row, 0, nameItem);
   ui->tableWidget->setItem(row, 1, typeItem);
   ui->tableWidget->setItem(row, 2, airedItem);

   //
   nameItem  = new QTableWidgetItem("Stargate");
   typeItem  = new QTableWidgetItem(tr("Science Fiction"));
   airedItem = new QTableWidgetItem("1997");

   ui->tableWidget->insertRow(row);
   ui->tableWidget->setItem(row, 0, nameItem);
   ui->tableWidget->setItem(row, 1, typeItem);
   ui->tableWidget->setItem(row, 2, airedItem);

   // initial sort
   ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);
   ui->tableWidget->setSortingEnabled(true);

   // signal and slot are method pointers
   connect(ui->tableWidget, &QTableWidget::cellPressed, this, &TableWidget_View::tableClicked_W);

   // following code will compile however it will fail at run time since this SLOT does not exist
   // connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem * )),
   //        this, SLOT(actionItemChanged(QTableWidgetItem *)));

   // error reported at run time
   // QObject::connect() QTableWidget::itemChanged(QTableWidgetItem * )
   // Unable to connect to receiver in TableWidget_View (../tablewidget_view.cpp:xxx)
   // Signal Index: 9 Slot Index: -1

}

void TableWidget_View::setUpView()
{
   // setup
   m_model = new QStandardItemModel;
   m_model->setColumnCount(3);
   m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
   m_model->setHeaderData(1, Qt::Horizontal, tr("Type"));
   m_model->setHeaderData(2, Qt::Horizontal, tr("First Aired"));

   //
   ui->tableView->setModel(m_model);
   ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

   ui->tableView->setColumnWidth(0, 175);
   ui->tableView->setColumnWidth(1, 175);

   // resizes the last column automatically, shown here as an example
   // ui->tableView->horizontalHeader()->setStretchLastSection(true);

   ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
   ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

   // sorting should be set to false before adding data
   // following line is not required since default is false
   // ui->tableView->setSortingEnabled(false);

   // data
   int row = m_model->rowCount();

   QStandardItem *nameItem  = new QStandardItem("The Good Wife");
   QStandardItem *typeItem  = new QStandardItem(tr("Drama/Legal"));
   QStandardItem *airedItem = new QStandardItem("2009");

   m_model->insertRow(row);
   m_model->setItem(row, 0, nameItem);
   m_model->setItem(row, 1, typeItem);
   m_model->setItem(row, 2, airedItem);

   //
   nameItem  = new QStandardItem("Doctor Who");
   typeItem  = new QStandardItem(tr("Science Fiction"));
   airedItem = new QStandardItem("1963");

   m_model->insertRow(row);
   m_model->setItem(row, 0, nameItem);
   m_model->setItem(row, 1, typeItem);
   m_model->setItem(row, 2, airedItem);

   //
   nameItem  = new QStandardItem("ER");
   typeItem  = new QStandardItem(tr("Drama/Medical"));
   airedItem = new QStandardItem("1994");

   m_model->insertRow(row);
   m_model->setItem(row, 0, nameItem);
   m_model->setItem(row, 1, typeItem);
   m_model->setItem(row, 2, airedItem);

   //
   nameItem  = new QStandardItem("Friends");
   typeItem  = new QStandardItem(tr("Comedy"));
   airedItem = new QStandardItem("1994");

   m_model->insertRow(row);
   m_model->setItem(row, 0, nameItem);
   m_model->setItem(row, 1, typeItem);
   m_model->setItem(row, 2, airedItem);

   //
   nameItem  = new QStandardItem("Stargate");
   typeItem  = new QStandardItem(tr("Science Fiction"));
   airedItem = new QStandardItem("1997");

   m_model->insertRow(row);
   m_model->setItem(row, 0, nameItem);
   m_model->setItem(row, 1, typeItem);
   m_model->setItem(row, 2, airedItem);

   // initial sort
   ui->tableView->sortByColumn(0, Qt::AscendingOrder);
   ui->tableView->setSortingEnabled(true);

   // signal and slot are method pointers
   connect(ui->tableView, &QTableView::clicked, this, &TableWidget_View::tableClicked_V);
}

void TableWidget_View::tableClicked_W(int row, int column)
{
   ksMsg(this, "Table Widget", "SIGNAL cellPressed() SLOT tableClicked_W\nint row & int column values passed\n\n"
         "Row: " + QString::number(row) + "  Column:" + QString::number(column));
}

void TableWidget_View::tableClicked_V(const QModelIndex & index)
{
   int row    = index.row();
   int column = index.column();

   ksMsg(this, "Table View", "SIGNAL clicked() SLOT tableClicked_V()\nModel index value passed\n\n"
         "Row: " + QString::number(row) + "  Column:" + QString::number(column));
}
