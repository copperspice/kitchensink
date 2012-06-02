#include "util.h"
#include "translate.h"

#include <QtGui>

static const QString qmPath = ":/translations";

Translate::Translate()
   : QWidget(), ui(new Ui::Translate )
{
   ui->setupUi(this);
   setWindowTitle(tr("Translate"));

   // add the model
   QStringListModel *model = new QStringListModel();
   ui->listView->setModel(model);

   // add data
   ui->nameCB->addItem("Amy Pond");
   ui->nameCB->addItem("Jack Harkness");
   ui->nameCB->addItem("River Song");
   ui->nameCB->addItem("Rose Tyler");
   ui->nameCB->addItem("Martha Jones");

   QStringList list;
   list.append(tr("Chocolate Cake"));
   list.append(tr("Lemon Bars"));
   list.append(tr("Oatmeal Raisin Cookies"));
   list.append(tr("Peach Cobbler"));
   list.append(tr("Pumpkin Cheesecake"));
   list.append(tr("Sticky Buns"));

   model->setStringList(list);

   //
   m_translator = new QTranslator;

   // signals
   connect(ui->englishRB,  SIGNAL(clicked()), this, SLOT(actionEnglish()));
   connect(ui->frenchRB,   SIGNAL(clicked()), this, SLOT(actionFrench()));
   connect(ui->germanRB,   SIGNAL(clicked()), this, SLOT(actionGerman()));
   connect(ui->closePB,    SIGNAL(clicked()), this, SLOT(actionClose()));
}

Translate::~Translate()
{
   delete ui;
}

void Translate::actionEnglish()
{
   qApp->removeTranslator(m_translator);
   ui->retranslateUi(this);
}

void Translate::actionFrench()
{
   if (! m_translator->load("qt_fr.qm",qmPath)) {
      bgMsg("Error while loading international file.");
   }

   qApp->installTranslator(m_translator);
   ui->retranslateUi(this);
}

void Translate::actionGerman()
{
   if (! m_translator->load("qt_de.qm",qmPath)) {
      bgMsg("Error while loading international file.");
   }

   qApp->installTranslator(m_translator);
   ui->retranslateUi(this);
}

void Translate::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      ui->retranslateUi(this);
   }

   QWidget::changeEvent(event);
}

void Translate::actionClose()
{
   this->parentWidget()->close();
}


