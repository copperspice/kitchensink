#include "util.h"
#include "colorpicker.h"
#include "ui_colorpicker.h"

#include <QColorDialog>


ColorPicker::ColorPicker(QWidget *parent)
   : QWidget(parent), ui(new Ui::ColorPicker)
{
   ui->setupUi(this);
   setWindowTitle("Color Selector");

   ui->colorEdit->setText("A wacky fox and sizeable pig jumped over the blue moon.");
   ui->native_checkBox->setChecked(true);

   connect(ui->selectColor_pushButton, SIGNAL(clicked()), this, SLOT(setColor()));
}

ColorPicker::~ColorPicker()
{
   delete ui;
}

void ColorPicker::setColor()
{
    QColor color;

    if (ui->native_checkBox->isChecked())  {
        color = QColorDialog::getColor(Qt::green, this);

    } else  {
        color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    }

    if (color.isValid()) {
         QPalette temp = ui->colorEdit->palette();
         temp.setColor( QPalette::Base, color);
         ui->colorEdit->setPalette(temp);
    }
}
