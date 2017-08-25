/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "util.h"
#include "script.h"

#include <QFileDialog>
#include <QLabel>
#include <QtScript>

Script::Script()
   : QWidget(), ui(new Ui::Script)
{
   ui->setupUi(this);
   setWindowTitle("Script");

   // load data from resource file
   m_fileName = ":/resources/script.js";
   displayScript();

   // signals
   connect(ui->openPB,  SIGNAL(clicked()), this, SLOT(actionOpenScript()));
   connect(ui->runPB,   SIGNAL(clicked()), this, SLOT(actionRunScript()));
   connect(ui->closePB, SIGNAL(clicked()), this, SLOT(actionClose()));
}

Script::~Script()
{
   delete ui;
}

void Script::displayScript()
{
   QFile file(m_fileName);

   if (! file.open(QFile::ReadOnly | QFile::Text)) {
      const QString msg = "Unable to open file " + m_fileName + " : " + file.errorString();
      QMessageBox::warning( 0, "Script", msg );
      return;
   }

   file.close();


   // open again as a script
   QFile scriptFile(m_fileName);
   scriptFile.open(QIODevice::ReadOnly);

   QTextStream stream(&scriptFile);
   QString contents = stream.readAll();

   // display
   ui->textEdit->setPlainText(contents);

   scriptFile.close();

   //
   jsScript(contents);
}

void Script::jsScript(QString contents)
{
   QScriptEngine engine;

   QLabel *label_js = new QLabel();
   QScriptValue scriptLabel = engine.newQObject(label_js);
   engine.globalObject().setProperty("label_js", scriptLabel);

   QPushButton *button_js = new QPushButton();
   QScriptValue scriptButton = engine.newQObject(button_js);
   engine.globalObject().setProperty("button_js", scriptButton);

   //
   QScriptValue result = engine.evaluate(contents, m_fileName);

   if (result.isError()) {
      int temp = result.property("lineNumber").toInt32();

      QMessageBox::critical(0,"Script",
         QString::fromLatin1("%0:%1:\n%2").arg(m_fileName).arg(temp).arg(result.toString()));

   } else {

      QLabel *label = new QLabel();
      label->setText("QLabel Object, not from JavaScript file");

      QLayout *mainLayout = ui->displayGB->layout();
      mainLayout->addWidget(label);

      mainLayout->addWidget(label_js);
      mainLayout->addWidget(button_js);
   }
}

void Script::actionOpenScript()
{
   m_fileName = QFileDialog::getOpenFileName(this, tr("Open Script File"),
            QDir::currentPath(), tr("Script Files (*.js)"));

   if (! m_fileName.isEmpty()) {
      displayScript();
   }
}

void Script::actionRunScript()
{
   // get contents
   QString contents =  ui->textEdit->toPlainText();

   // clear name for engine.evaluate
   m_fileName = "";

   //
   jsScript(contents);
}

void Script::actionClose() {
   this->parentWidget()->close();
}

