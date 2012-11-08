/**********************************************************************
*
* Copyright (c) 2012 Barbara Geller
* Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#include "util.h"
#include "colorpicker.h"
#include "ui_colorpicker.h"

#include <QColorDialog>

ColorPicker::ColorPicker(QWidget *parent)
   : QWidget(parent), ui(new Ui::ColorPicker)
{
   ui->setupUi(this);
   setWindowTitle("Color Selector");

   ui->colorEdit->setText("A wacky fox and sizeable pig jumped halfway over a blue moon.");
   ui->native_checkBox->setChecked(true);

   //
   QPalette temp = ui->colorEdit->palette();
   QString colorname = temp.color(QPalette::Base).name();
   ui->label->setText("Sample Text Background in " + colorname.toUpper() );

   connect(ui->selectColor_PB, SIGNAL(clicked()), this, SLOT(setColor()));
   connect(ui->closePB,        SIGNAL(clicked()), this, SLOT(actionClose()));
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
         ui->label->setText("Sample Text Background in " + color.name().toUpper() );

         QPalette temp = ui->colorEdit->palette();
         temp.setColor( QPalette::Base, color);
         ui->colorEdit->setPalette(temp);
    }
}

void ColorPicker::actionClose() {
   this->parentWidget()->close();
}
