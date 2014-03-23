
#include "wiggle_boxes.h"

Wiggle_Boxes::Wiggle_Boxes(QWidget *parent)
   : QmlApplicationViewer(parent)
{
   QString fileName;

#ifdef Q_OS_MAC
    fileName = QCoreApplication::applicationDirPath() + "resources_qml/wiggle_boxes/wiggle_boxes.qml";
#else
    fileName = "/resources_qml/wiggle_boxes/Wiggle_Boxes.qml";
#endif

   this->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
   this->setMainQmlFile(fileName.toLatin1());
   this->setWindowTitle("Wiggle Boxes");
   this->showExpanded();
}
