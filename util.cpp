#include "util.h"

 void bgMsg(QString msg)
 {
    QMessageBox msgB;
    msgB.setWindowTitle("Debug Informatoin");
    msgB.setText(msg);
    msgB.exec();
}


/* void bgDebug(QtMsgType type, QString msg)
{
    switch (type) {

       case QtDebugMsg:
          fprintf(stdout, "Debug: %s\n", msg);
          break;

       case QtWarningMsg:
          fprintf(stdout, "Warning: %s\n", msg);
          break;

       case QtCriticalMsg:
          fprintf(stdout, "Critical: %s\n", msg);
          break;
    }
}           */

