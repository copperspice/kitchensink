#ifndef UTIL_H
#define UTIL_H

#include <QMessageBox>

void ksMsg(const QString &msg);
void ksMsg(QString msg, int value);
void ksMsg(QWidget *parent, const QString &title, const QString &msg);

#endif
