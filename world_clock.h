
#ifndef WORLD_CLOCK_H
#define WORLD_CLOCK_H

#include "qmlapplicationviewer.h"
#include <QWidget>

class World_Clock : public QmlApplicationViewer
{
   CS_OBJECT(World_Clock)

   public:
     World_Clock(QWidget *parent = 0);

};

#endif
