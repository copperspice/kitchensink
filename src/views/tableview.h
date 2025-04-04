/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
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

#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QSqlDatabase>
#include <QWidget>

class TableView : public QWidget
{
   CS_OBJECT(TableView)

 public:
   TableView();
   ~TableView();
   QSqlDatabase m_db;

 private:
   bool createConnection();
};

#endif
