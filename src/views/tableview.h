/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
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
