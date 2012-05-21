#include "util.h"
#include "fontpicker.h"
#include "ui_fontpicker.h"

#include <QFont>
#include <QFontDialog>

FontPicker::FontPicker(QWidget *parent) :
   QWidget(parent), ui(new Ui::FontPicker)
{
   ui->setupUi(this);
   ui->fontEdit->setText("The fox and the pig jumped over the moon.");

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
        ui->fontEdit->setText(font.key());
        ui->fontEdit->setFont(font);
    }
}
