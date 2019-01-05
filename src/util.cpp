/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#include "util.h"

void ksMsg(const QString &msg)
{
   QMessageBox msgB;

   msgB.setWindowTitle("General Information");
   msgB.setWindowIcon(QIcon("://resources/ks.ico"));

   msgB.setText(msg);
   msgB.exec();
}

void ksMsg(QString msg, int value)
{
   msg = msg + "   " + QString::number(value);

   QMessageBox msgB;

   msgB.setWindowTitle("General Information");
   msgB.setWindowIcon(QIcon("://resources/ks.ico"));

   msgB.setText(msg);
   msgB.exec();
}

void ksMsg(QWidget *parent, const QString &title, const QString &msg)
{
   QMessageBox msgB;

   if (parent) {
      msgB.setWindowModality(Qt::WindowModal);
   }

   msgB.setWindowTitle(title);
   msgB.setWindowIcon(QIcon("://resources/ks.ico"));

   msgB.setText(msg);
   msgB.exec();
}

