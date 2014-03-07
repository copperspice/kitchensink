/**********************************************************************
*
* Copyright (c) 2012-2013 Barbara Geller
* Copyright (c) 2011-2012 Nokia Corporation and/or its subsidiary(-ies).
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

