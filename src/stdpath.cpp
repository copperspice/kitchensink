/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "stdpath.h"
#include "util.h"

#include <QList>
#include <QStandardPaths>
#include <QStringList>

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
   tempList.append(QStandardPaths::GenericConfigLocation);
   tempList.append(QStandardPaths::AppDataLocation);
   tempList.append(QStandardPaths::AppConfigLocation);

   for (const auto &item : tempList) {
      m_ui->locationComboBox->addItem(QStandardPaths::displayName(item), QVariant::fromValue(item));
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

   QVariant locationData = m_ui->locationComboBox->itemData(index);

   QStandardPaths::StandardLocation type = locationData.value<QStandardPaths::StandardLocation>();
   QStringList paths = QStandardPaths::standardLocations(type);

   for (const auto &item : paths) {
      m_ui->belongLocations->append(item);
   }
}

void StdPath::writeableLocation(int index)
{
   m_ui->writeLocation->clear();

   QVariant locationData = m_ui->locationComboBox->itemData(index);

   QStandardPaths::StandardLocation type = locationData.value<QStandardPaths::StandardLocation>();
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

   int location = m_ui->locationComboBox->currentIndex();

   QVariant locationData = m_ui->locationComboBox->itemData(location);
   QString fileName      = m_ui->fileName->text();

   if (fileName.isEmpty()) {
      return;
   }

   QStandardPaths::StandardLocation type = locationData.value<QStandardPaths::StandardLocation>();
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

   int location = m_ui->locationComboBox->currentIndex();

   QVariant locationData = m_ui->locationComboBox->itemData(location);
   QString fileName      = m_ui->fileName->text();

   if (fileName.isEmpty()) {
      return;
   }

   QStandardPaths::StandardLocation type = locationData.value<QStandardPaths::StandardLocation>();
   QStandardPaths::LocateOptions option;

   if (m_ui->fileRadioButton->isChecked()) {
      option = QStandardPaths::LocateFile;

   } else if (m_ui->directoryRadioButton->isChecked()) {
      option = QStandardPaths::LocateDirectory;

   }

   QStringList pathList = QStandardPaths::locateAll(type, fileName, option);

   for (const auto &item : pathList) {
      m_ui->locateAll->append(item);
   }
}
