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
