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

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "ui_listview.h"

#include <QStringList>
#include <QWidget>

class QSortFilterProxyModel;

class ListView : public QWidget
{
   CS_OBJECT(ListView)

 public:
   explicit ListView(QWidget *parent = nullptr);
   ~ListView();

 private:
   Ui::ListView *ui;
   QSortFilterProxyModel *m_proxyModel;
   QStringList getData();

   // slot declarations
   void delRow();
   void addRow();
};

#endif
