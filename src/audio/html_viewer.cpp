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

#if ! defined(QT_NO_WEBKIT)

#include "html_viewer.h"

#include <QtGui>
#include <QtWebKit>

Html_Viewer::Html_Viewer()
   : QMainWindow(), ui(new Ui::Html_Form)
{
   QWidget *temp = new QWidget(this);
   setCentralWidget(temp);

   ui->setupUi(temp);
   setWindowTitle("Html Viewer");

   createActions();
   setStartupText();

   // signals
   connect(ui->webView,   SIGNAL(loadFinished(bool)), this,              SLOT(updateTextEdit()));
   connect(ui->clearPB,   SIGNAL(clicked()),          ui->plainTextEdit, SLOT(clear()) );
   connect(ui->previewPB, SIGNAL(clicked()),          this,              SLOT(actionPreview()) );
}

Html_Viewer::~Html_Viewer()
{
   delete ui;
}

void Html_Viewer::createActions()
{
   // 1
   QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

   QAction *openAct = new QAction(tr("&Open..."), this);
   openAct->setShortcuts(QKeySequence::Open);
   openAct->setStatusTip(tr("Open an existing HTML file"));
   connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
   fileMenu->addAction(openAct);

   QAction *openUrlAct = new QAction(tr("&Open URL..."), this);
   openUrlAct->setShortcut(tr("Ctrl+U"));
   openUrlAct->setStatusTip(tr("Open a URL"));
   connect(openUrlAct, SIGNAL(triggered()), this, SLOT(openUrl()));
   fileMenu->addAction(openUrlAct);

   QAction *saveAct = new QAction(tr("&Save"), this);
   saveAct->setShortcuts(QKeySequence::Save);
   saveAct->setStatusTip(tr("Save the HTML file to disk"));
   connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
   fileMenu->addAction(saveAct);

   fileMenu->addSeparator();

   QAction *exitAct = new QAction(tr("E&xit"), this);
   exitAct->setStatusTip(tr("Exit Viewer"));
   exitAct->setShortcuts(QKeySequence::Quit);
   connect(exitAct, SIGNAL(triggered()), this, SLOT(actionClose()));
   fileMenu->addAction(exitAct);

   menuBar()->addSeparator();

   // 2
   QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

   QAction *aboutAct = new QAction(tr("&About"), this);
   aboutAct->setStatusTip(tr("Show the About box"));
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
   helpMenu->addAction(aboutAct);
}

void Html_Viewer::setStartupText()
{
   QString string = "<html><body>"
                    "\n\n"
                    "<h1>HTML Previewer</h1>"
                    "\n\n"
                    "<p>This example shows how to use "
                    "\n"
                    "<b><font color='#0000FF'>QWebView</font></b>"
                    "\n"
                    " to preview HTML data written in a QPlainTextEdit.</p>"
                    "\n\n"
                    "</body></html>";

   ui->plainTextEdit->setPlainText(string);
   ui->webView->setHtml(string);
}

//
void Html_Viewer::about()
{
   QMessageBox::about(this, tr("About HTML Viewer"),
      tr("The <b>Previewer</b> example demonstrates how to view HTML documents using a QWebView."));
}

void Html_Viewer::open()
{
   QString fileName = QFileDialog::getOpenFileName(this);

   if (!fileName.isEmpty()) {
      // read from file
      QFile file(fileName);

      if (!file.open(QIODevice::ReadOnly)) {
         QMessageBox::information(this, tr("Unable to open file"), file.errorString());
         return;
      }

      QTextStream out(&file);
      QString output = out.readAll();

      // display contents
      ui->plainTextEdit->setPlainText(output);

      m_baseUrl = QUrl::fromLocalFile(fileName);
   }
}


void Html_Viewer::openUrl()
{
   bool ok;
   QString url(QInputDialog::getText(this, tr("Enter a URL"), tr("URL:"), QLineEdit::Normal, "http://", &ok));

   if (ok && ! url.isEmpty()) {
      ui->webView->setUrl( QUrl(url) );
   }
}

void Html_Viewer::save()
{
   QString content  = ui->plainTextEdit->toPlainText();
   QString fileName = QFileDialog::getSaveFileName(this);

   if (!fileName.isEmpty()) {
      // save to file
      QFile file(fileName);

      if (!file.open(QIODevice::WriteOnly)) {
         QMessageBox::information(this, tr("Unable to open file"),file.errorString());
         return;
      }

      QTextStream in(&file);
      in << content;
   }
}

void Html_Viewer::updateTextEdit()
{
   QWebFrame *mainFrame = ui->webView->page()->mainFrame();
   QString frameText = mainFrame->toHtml();
   ui->plainTextEdit->setPlainText(frameText);
}

void Html_Viewer::actionClose() {
   this->parentWidget()->close();
}

void Html_Viewer::actionPreview()
{
    // Update the contents in web viewer
    QString text = ui->plainTextEdit->toPlainText();
    ui->webView->setHtml(text, m_baseUrl);
}

#endif