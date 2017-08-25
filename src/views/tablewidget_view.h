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


#ifndef TABLEWIDGET_VIEW_H
#define TABLEWIDGET_VIEW_H

#include "ui_tablewidget_view.h"

#include <QWidget>
#include <QStandardItemModel>

class TableWidget_View : public QWidget
{
   CS_OBJECT(TableWidget_View)

   public:
      explicit TableWidget_View(QWidget *parent = nullptr);
      ~TableWidget_View();

   private:
      void setUpWidget();
      void setUpView();

      CS_SLOT_1(Private, void tableClicked_W(int row,int col))
      CS_SLOT_2(tableClicked_W)

      CS_SLOT_1(Private, void tableClicked_V(const QModelIndex & index))
      CS_SLOT_2(tableClicked_V)

      Ui::TableWidget_View *ui;
      QStandardItemModel *m_model;

};

#endif
