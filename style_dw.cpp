#include "util.h"

#include "style_dw.h"
#include "style_edit.h"

#include <QMessageBox>

Style_DW::Style_DW(Mdi *parent)
   : QMainWindow(), ui(new Ui::Style_DW)
{
   m_parent = parent;
   m_style  = NULL;

   ui->setupUi(this);
   setWindowTitle("Style Sheets");

   ui->nameLabel->setProperty("class", "mandatory QLabel");

   // add data
   ui->nameCB->addItem(tr("Amy Pond"));
   ui->nameCB->addItem(tr("Jack Harkness"));
   ui->nameCB->addItem(tr("River Song"));
   ui->nameCB->addItem(tr("Rose Tyler"));
   ui->nameCB->addItem(tr("Martha Jones"));

   //
   QString qssName = Style_Edit::getQssName();
   Style_Edit::loadStyleSheet(qssName);

   connect(ui->buttonBox,   SIGNAL(clicked(QAbstractButton *)), this, SLOT(actionButton(QAbstractButton *)));
   connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(actionClose()));
}

Style_DW::~Style_DW()
{
   delete ui;
}

void Style_DW::on_actionAbout_triggered()
{
   QMessageBox::about(this, tr("About Style Sheets"),
          tr("The <b>Style Sheet</b> example shows how widgets can be styled "
             "using Qt Style Sheets. Click <b>File|Edit Style Sheet</b> to pop up the "
             "style editor and choose an existing style sheet or design your own."));
}

void Style_DW::on_actionEditStyle_triggered()
{   
   m_style = new Style_Edit(m_parent);
   m_parent->addMdiChild(m_style);
}

void Style_DW::actionButton(QAbstractButton *button)
{
   QMessageBox msgB;

   if (button->text().toLower() == "ok") {
      msgB.setText("Ok button pressed. Closing Style Sheets.");
      msgB.exec();

   } else {
      msgB.setText("Cancel button pressed. Closing Style Sheets.");
      msgB.exec();
   }

   //
   this->actionClose();
}

void Style_DW::actionClose() {

   // close child window if open
   if (m_style) {
      m_style->actionClose();
   }

   this->parentWidget()->close();
}
