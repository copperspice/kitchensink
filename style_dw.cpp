#include "util.h"

#include "style_dw.h"
#include "style_edit.h"

#include <QMessageBox>

Style_DW::Style_DW(Mdi *parent)
   : QMainWindow(parent), ui(new Ui::Style_DW)
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

   connect(ui->okPB,    SIGNAL(clicked()), this, SLOT(actionOk()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));

   // force
   ui->nameCB->setFocus();
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
   m_style = new Style_Edit(m_parent, this);
   m_parent->addMdiChild(m_style);
}

void Style_DW::actionOk()
{
   ksMsg(this, "Style Sheets", "Ok button pressed. Closing Style Sheets.");
   this->actionClose();
}

void Style_DW::styleEditClose()
{
   // marks the style_edit window closed
   m_style  = NULL;
}

void Style_DW::actionClose() {

   // close child window if open
   if (m_style != NULL) {      
      m_style->actionClose();
   }

   this->parentWidget()->close();
}
