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

#ifndef UTIL_H
#define UTIL_H

#include <QMessageBox>

void ksMsg(const QString &msg);
void ksMsg(QString msg, int value);
void ksMsg(QWidget *parent, const QString &title, const QString &msg);

#endif
