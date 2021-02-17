/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "util.h"
#include "script.h"

#include <QFileDialog>
#include <QLabel>
#include <QStandardItemModel>
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
      QMessageBox::warning(nullptr, "Script", msg);
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

      QMessageBox::critical(nullptr,"Script", QString("%0:%1:\n%2").formatArgs(m_fileName, QString::number(temp), result.toString()));

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

