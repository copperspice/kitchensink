/**********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
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
#include "listview.h"
#include "ui_listview.h"

#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <QListView>
#include <QAbstractItemModel>
#include <QModelIndex>

ListView::ListView(QWidget *parent)
   : QWidget(parent), ui(new Ui::ListView)
{
   ui->setupUi(this);
   setWindowTitle("List View Model");

   //
   QStringListModel *model = new QStringListModel(this);
   model->setStringList( getData() );

   //
   m_proxyModel = new QSortFilterProxyModel(this);
   m_proxyModel->setSourceModel(model);
   m_proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
   m_proxyModel->sort(0, Qt::AscendingOrder);
   m_proxyModel->setDynamicSortFilter(true);

   //
   ui->listView->setModel(m_proxyModel);
   ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

   // adjust the size
   QSize size = this->size();
   this->setMinimumHeight( size.height() );

   connect( ui->insert_PB,  SIGNAL(clicked()), this, SLOT(addRow()) );
   connect( ui->delete_PB,  SIGNAL(clicked()), this, SLOT(delRow()) );
}

ListView::~ListView()
{
   delete ui;
}

QStringList ListView::getData()
{
   QStringList data;

   data << "gallon" << "ounce" << "pinch" << "pound" << "cup"
        << "pint" << "quart" << "tsp" << "Tbsp" << "bunch" << "jigger" ;

   return data;
}

void ListView::addRow()
{
   // sort off
   m_proxyModel->setDynamicSortFilter(false);
   m_proxyModel->sort(-1);

   int row = ui->listView->currentIndex().row();
   m_proxyModel->insertRows(row,1);

   // get index
   QModelIndex index = m_proxyModel->index(row, 0);
   //    m_proxyModel->setData(index, QVariant("NEW"), Qt::EditRole);

   // select and edit
   ui->listView->setCurrentIndex(index);
   ui->listView->edit(index);

   // sort on
   m_proxyModel->setDynamicSortFilter(true);
   m_proxyModel->sort(0, Qt::AscendingOrder);
}

void ListView::delRow()
{
   m_proxyModel->removeRows(ui->listView->currentIndex().row(), 1);
}



