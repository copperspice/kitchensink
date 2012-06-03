#include "util.h"

void bgMsg(QString msg)
{
   QMessageBox msgB;
   msgB.setWindowTitle("Information");
   msgB.setText(msg);
   msgB.exec();
}


void bgMsg(QString msg, int value)
{
   msg = msg + "   " + QString::number(value);

   //
   QMessageBox msgB;
   msgB.setWindowTitle("Information");
   msgB.setText(msg);
   msgB.exec();
}

