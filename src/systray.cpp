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

#include "systray.h"

#include <QCloseEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

const static QString sysPath = ":/resources/";

SysTray::SysTray()
{
   setWindowTitle(tr("System Tray"));

   createIconGroupBox();
   createMessageGroupBox();
   createActions();
   createTrayIcon();

   m_quitNow = false;

   iconLabel->setMinimumWidth(durationLabel->sizeHint().width());

   connect(showMessageButton, &QAbstractButton::clicked,         this,     &SysTray::showMessage);
   connect(showIconCheckBox,  &QAbstractButton::toggled,         trayIcon, &QSystemTrayIcon::setVisible);

   // static_cast is required since this signal is overloaded
   connect(iconComboBox,      static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                  this, &SysTray::setIcon);

   connect(trayIcon,          &QSystemTrayIcon::messageClicked,  this,     &SysTray::messageClicked);
   connect(trayIcon,          &QSystemTrayIcon::activated,       this,     &SysTray::iconActivated);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(iconGroupBox);
   mainLayout->addWidget(messageGroupBox);
   setLayout(mainLayout);

   iconComboBox->setCurrentIndex(1);
   trayIcon->show();
}

void SysTray::createIconGroupBox()
{
   iconGroupBox = new QGroupBox(tr("Tray Icon"));

   iconLabel    = new QLabel("Icon:");

   iconComboBox = new QComboBox;
   iconComboBox->addItem(QIcon(sysPath + "bad.png"),   tr("Bad"));
   iconComboBox->addItem(QIcon(sysPath + "heart.png"), tr("Heart"));
   iconComboBox->addItem(QIcon(sysPath + "trash.png"), tr("Trash"));

   showIconCheckBox = new QCheckBox(tr("Show icon"));
   showIconCheckBox->setChecked(true);

   QHBoxLayout *iconLayout = new QHBoxLayout;
   iconLayout->addWidget(iconLabel);
   iconLayout->addWidget(iconComboBox);
   iconLayout->addStretch();
   iconLayout->addWidget(showIconCheckBox);
   iconGroupBox->setLayout(iconLayout);
}

void SysTray::createMessageGroupBox()
{
   messageGroupBox = new QGroupBox(tr("Balloon Message"));

   typeLabel = new QLabel(tr("Type:"));

   typeComboBox = new QComboBox;
   typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
   typeComboBox->addItem(style()->standardIcon(
          QStyle::SP_MessageBoxInformation), tr("Information"),QSystemTrayIcon::Information);

   typeComboBox->addItem(style()->standardIcon(
          QStyle::SP_MessageBoxWarning), tr("Warning"), QSystemTrayIcon::Warning);

   typeComboBox->addItem(style()->standardIcon(
          QStyle::SP_MessageBoxCritical), tr("Critical"), QSystemTrayIcon::Critical);

   typeComboBox->setCurrentIndex(1);

   durationLabel = new QLabel(tr("Duration:"));

   durationSpinBox = new QSpinBox;
   durationSpinBox->setRange(5, 60);
   durationSpinBox->setSuffix(" s");
   durationSpinBox->setValue(15);

   durationWarningLabel = new QLabel(tr("(Some systems might ignore this hint.)"));
   durationWarningLabel->setIndent(10);

   titleLabel = new QLabel(tr("Title:"));

   titleEdit = new QLineEdit(tr("Can not connect to a network."));

   bodyLabel = new QLabel(tr("Body:"));

   bodyEdit = new QTextEdit;
   bodyEdit->setPlainText(tr("We have no idea how to provide support.\nClick the balloon for details."));

   showMessageButton = new QPushButton(tr("Show Message"));
   showMessageButton->setDefault(true);

   QGridLayout *messageLayout = new QGridLayout;
   messageLayout->addWidget(typeLabel, 0, 0);
   messageLayout->addWidget(typeComboBox, 0, 1, 1, 2);
   messageLayout->addWidget(durationLabel, 1, 0);
   messageLayout->addWidget(durationSpinBox, 1, 1);
   messageLayout->addWidget(durationWarningLabel, 1, 2, 1, 3);
   messageLayout->addWidget(titleLabel, 2, 0);
   messageLayout->addWidget(titleEdit, 2, 1, 1, 4);
   messageLayout->addWidget(bodyLabel, 3, 0);
   messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
   messageLayout->addWidget(showMessageButton, 5, 0, 1, 5, Qt::AlignHCenter);
   messageLayout->setColumnStretch(3, 1);
   messageLayout->setRowStretch(4, 1);
   messageGroupBox->setLayout(messageLayout);
}

void SysTray::createTrayIcon()
{
   trayIconMenu = new QMenu(this);
   trayIconMenu->addAction(minimizeAction);
   trayIconMenu->addAction(maximizeAction);
   trayIconMenu->addAction(restoreAction);
   trayIconMenu->addSeparator();
   trayIconMenu->addAction(quitAction);

   trayIcon = new QSystemTrayIcon(this);
   trayIcon->setContextMenu(trayIconMenu);
}

void SysTray::createActions()
{
   minimizeAction = new QAction(tr("Mi&nimize"), this);
   connect(minimizeAction, &QAction::triggered,  this, &SysTray::hide);

   maximizeAction = new QAction(tr("Ma&ximize"), this);
   connect(maximizeAction, &QAction::triggered,  this, &SysTray::showMaximized);

   restoreAction = new QAction(tr("&Restore"),   this);
   connect(restoreAction,  &QAction::triggered,  this, &SysTray::showNormal);

   quitAction = new QAction(tr("&Quit"), this);
   connect(quitAction,     &QAction::triggered,  this, &SysTray::actionQuit);
}

//
void SysTray::setVisible(bool visible)
{
   minimizeAction->setEnabled(visible);
   maximizeAction->setEnabled(!isMaximized());
   restoreAction->setEnabled(isMaximized() || ! visible);

   QDialog::setVisible(visible);
}

void SysTray::setIcon(int index)
{
   QIcon icon = iconComboBox->itemIcon(index);
   trayIcon->setIcon(icon);
   setWindowIcon(icon);

   trayIcon->setToolTip(iconComboBox->itemText(index));
}

void SysTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
   switch (reason) {
      case QSystemTrayIcon::Trigger:

      case QSystemTrayIcon::DoubleClick:
         iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1)
                 % iconComboBox->count());
         break;

      case QSystemTrayIcon::MiddleClick:
         showMessage();
         break;

      default:
         break;
   }
}

void SysTray::showMessage()
{
   QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(
          typeComboBox->itemData(typeComboBox->currentIndex()).toInt());

   trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
          durationSpinBox->value() * 1000);
}

void SysTray::messageClicked()
{
   QMessageBox::information(nullptr, tr("Systray"),
           tr("We already provided the best known support.\nMaybe you can ask another user."));
}

void SysTray::closeEvent(QCloseEvent *event)
{
   if (! m_quitNow) {
      QMessageBox::information(this, tr("System Tray"),
           tr("The System Tray sample will continue to run. To terminate choose "
              "<b>Quit</b> in the context menu of the system tray."));

      this->parentWidget()->hide();
      event->ignore();
   }
}

void SysTray::actionQuit() {
   // called from the sys tray menu
   m_quitNow = true;
   this->parentWidget()->close();
}


