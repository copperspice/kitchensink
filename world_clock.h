
#ifndef WORLD_CLOCK_H
#define WORLD_CLOCK_H

#include "qmlapplicationviewer.h"
#include <QWidget>

class World_Clock : public QmlApplicationViewer
{
   Q_OBJECT

   public:
     World_Clock(QWidget *parent = 0);

};

#endif
