/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/


#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "ui_listview.h"

#include <QStringList>
#include <QSortFilterProxyModel>
#include <QWidget>

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
