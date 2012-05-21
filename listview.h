#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "ui_listview.h"
#include <QWidget>

namespace Ui {
class ListView;
}

class ListView : public QWidget
{
   Q_OBJECT
      
   public:
      explicit ListView(QWidget *parent = 0);
      ~ListView();
      
   private:
      Ui::ListView *ui;
};

#endif // LISTVIEW_H
