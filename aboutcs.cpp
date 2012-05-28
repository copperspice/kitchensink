#include "util.h"
#include "aboutcs.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

AboutCS::AboutCS()
   : QWidget()
{
   setWindowTitle("About CopperSpice");

   QPushButton *homePB  = new QPushButton;
   homePB->setText("Home");

   QPushButton *closePB = new QPushButton;
   closePB->setText("Close");

   //
   m_viewer = new QWebView;

   QString url = "http://192.168.10.39/copperspice/kitchensink.html";
   m_viewer->setUrl(url);

   //
   QHBoxLayout *buttonLayout = new QHBoxLayout;
   buttonLayout->addStretch();
   buttonLayout->addWidget(homePB);
   buttonLayout->addSpacing(10);
   buttonLayout->addWidget(closePB);
   buttonLayout->addStretch();

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(m_viewer);
   mainLayout->addSpacing(10);
   mainLayout->addLayout(buttonLayout);
   setLayout(mainLayout);

   mainLayout->setContentsMargins(0, 0, 0, 15);

   // signals
   connect(homePB,   SIGNAL(clicked()), this, SLOT(actionHome()) );
   connect(closePB,  SIGNAL(clicked()), this, SLOT(actionClose()) );

   // adjust the size
   QSize size = this->size();
   this->setMinimumHeight( size.height() );
}

void AboutCS::actionHome() {
   QString url = "http://192.168.10.39/copperspice/kitchensink.html";
   m_viewer->setUrl(url);
}

void AboutCS::actionClose() {
   this->parentWidget()->close();
}
