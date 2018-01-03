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

#include <QWidget>

class QSortFilterProxyModel;

class ListView : public QWidget
{
   CS_OBJECT(ListView)

   public:
      explicit ListView(QWidget *parent = nullptr);
      ~ListView();

   private:
      QStringList getData();

      CS_SLOT_1(Private, void delRow())
      CS_SLOT_2(delRow)

      CS_SLOT_1(Private, void addRow())
      CS_SLOT_2(addRow)

      Ui::ListView *ui;
      QSortFilterProxyModel *m_proxyModel;
};

#endif
