
#include "world_clock.h"

World_Clock::World_Clock(QWidget *parent)
   : QmlApplicationViewer(parent)
{
   QString fileName;

#ifdef Q_OS_MAC
    fileName = QCoreApplication::applicationDirPath() + "/resources_qml/world_clock/World_Clock.qml";
#else
    fileName = "/resources_qml/world_clock/World_Clock.qml";
#endif

   this->setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
   this->setMainQmlFile(fileName.toLatin1());
   this->setWindowTitle("World Clocks");
   this->showExpanded();
}
