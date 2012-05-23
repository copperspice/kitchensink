#include "util.h"
#include "fontpicker.h"
#include "ui_fontpicker.h"

#include <QFont>
#include <QFontDialog>

FontPicker::FontPicker(QWidget *parent) :
   QWidget(parent), ui(new Ui::FontPicker)
{
   ui->setupUi(this);
   setWindowTitle("Font Selector");

   ui->fontEdit->setText("A wacky fox and sizeable pig jumped over the blue moon.");

   connect( ui->selectFont_pushButton, SIGNAL(clicked()), this, SLOT(setFont()));
}

FontPicker::~FontPicker()
{
   delete ui;
}

void FontPicker::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont(ui->fontEdit->text()), this);

    if (ok) {        
        ui->fontEdit->setFont(font);
        ui->fontEdit->home(true);
        ui->fontEdit->setFocus();
    }
}
