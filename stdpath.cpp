/**********************************************************************
*
* Copyright (c) 2012-2013 Barbara Geller
* Copyright (c) 2013 Jeff Tranter
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

#include "stdpath.h"
#include "util.h"

StdPath::StdPath(QWidget *parent)
   : QWidget(parent), m_ui(new Ui::StdPath)
{
    m_ui->setupUi(this);

    QList<QStandardPaths::StandardLocation> tempList;
    tempList.append(QStandardPaths::DesktopLocation);
    tempList.append(QStandardPaths::DocumentsLocation);
    tempList.append(QStandardPaths::FontsLocation);
    tempList.append(QStandardPaths::ApplicationsLocation);
    tempList.append(QStandardPaths::MusicLocation);
    tempList.append(QStandardPaths::MoviesLocation);
    tempList.append(QStandardPaths::PicturesLocation);
    tempList.append(QStandardPaths::TempLocation);
    tempList.append(QStandardPaths::HomeLocation);
    tempList.append(QStandardPaths::DataLocation);
    tempList.append(QStandardPaths::CacheLocation);
    tempList.append(QStandardPaths::GenericDataLocation);
    tempList.append(QStandardPaths::RuntimeLocation);
    tempList.append(QStandardPaths::ConfigLocation);
    tempList.append(QStandardPaths::DownloadLocation);
    tempList.append(QStandardPaths::GenericCacheLocation);

    for (int k = 0; k < tempList.size(); ++k) {
       QStandardPaths::StandardLocation type = tempList.at(k);
       m_ui->locationComboBox->addItem(QStandardPaths::displayName(type), QVariant::fromValue(type));
    }

    //
    connect(m_ui->locationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(standardLocations(int)));
    connect(m_ui->locationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(writeableLocation(int)));

    connect(m_ui->findTB,           SIGNAL(clicked(bool)), this, SLOT(find()));
    connect(m_ui->locateTB,         SIGNAL(clicked(bool)), this, SLOT(locate()));
    connect(m_ui->locateTB,         SIGNAL(clicked(bool)), this, SLOT(locateAll()));
}

StdPath::~StdPath()
{
   delete m_ui;
}

// tab 1
void StdPath::standardLocations(int index)
{
   m_ui->belongLocations->clear();

   QVariant data = m_ui->locationComboBox->itemData(index);

   QStandardPaths::StandardLocation type = data.value<QStandardPaths::StandardLocation>();
   QStringList paths = QStandardPaths::standardLocations(type);

   for(int k = 0; k < paths.size(); ++k)    {
      m_ui->belongLocations->append(paths.at(k));
   }
}

void StdPath::writeableLocation(int index)
{
   m_ui->writeLocation->clear();

   QVariant data = m_ui->locationComboBox->itemData(index);

   QStandardPaths::StandardLocation type = data.value<QStandardPaths::StandardLocation>();
   QString path = QStandardPaths::writableLocation(type);

   m_ui->writeLocation->setText(path);
}

// tab 2
void StdPath::find()
{
   QString fileName = m_ui->executableName->text();

   if (fileName.isEmpty())  {
      return;
   }

   QString path = QStandardPaths::findExecutable(fileName);
   m_ui->findPath->setText(path);
}

// tab 3
void StdPath::locate()
{
   m_ui->locateOne->clear();

   int location     = m_ui->locationComboBox->currentIndex();
   QVariant data    = m_ui->locationComboBox->itemData(location);
   QString fileName = m_ui->fileName->text();

   if (fileName.isEmpty()) {
      return;
   }

   QStandardPaths::StandardLocation type = data.value<QStandardPaths::StandardLocation>();
   QStandardPaths::LocateOptions option;

   if (m_ui->fileRadioButton->isChecked()) {
      option = QStandardPaths::LocateFile;

   } else if (m_ui->directoryRadioButton->isChecked()) {
      option = QStandardPaths::LocateDirectory;

   }

   QString path = QStandardPaths::locate(type, fileName, option);
   m_ui->locateOne->setText(path);
}

void StdPath::locateAll()
{
   m_ui->locateAll->clear();

   int location     = m_ui->locationComboBox->currentIndex();
   QVariant data    = m_ui->locationComboBox->itemData(location);
   QString fileName = m_ui->fileName->text();

   if (fileName.isEmpty()) {
      return;
   }

   QStandardPaths::StandardLocation type = data.value<QStandardPaths::StandardLocation>();
   QStandardPaths::LocateOptions option;

   if (m_ui->fileRadioButton->isChecked()) {
      option = QStandardPaths::LocateFile;

   } else if (m_ui->directoryRadioButton->isChecked()) {
      option = QStandardPaths::LocateDirectory;

   }

   QStringList locationList = QStandardPaths::locateAll(type, fileName, option);

   for(int k = 0; k < locationList.size(); ++k)    {
      m_ui->locateAll->append(locationList.at(k));
   }
}
