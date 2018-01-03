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

#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QString>
#include <QWidget>

class DragLabel : public QLabel
{
   public:
      DragLabel(const QString &text, QWidget *parent);
      QString labelText() const;

   private:
      QString m_labelText;
};

#endif
