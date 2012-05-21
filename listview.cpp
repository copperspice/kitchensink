#include "listview.h"
#include "ui_listview.h"

ListView::ListView(QWidget *parent)
   : QWidget(parent), ui(new Ui::ListView)
{
   ui->setupUi(this);
   setWindowTitle("List View Model");

}

ListView::~ListView()
{
   delete ui;
}
