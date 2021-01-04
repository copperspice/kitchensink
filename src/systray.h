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

#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

class SysTray : public QDialog
{
   CS_OBJECT(SysTray)

   public:
      SysTray();
      void setVisible(bool visible);

   protected:
      void closeEvent(QCloseEvent *event);

   private:
      void createIconGroupBox();
      void createMessageGroupBox();
      void createActions();
      void createTrayIcon();

      void iconActivated(QSystemTrayIcon::ActivationReason reason);
      void messageClicked();
      void showMessage();
      void setIcon(int index);

      // slot declarations
      void actionQuit();

      QGroupBox *iconGroupBox;
      QLabel *iconLabel;
      QComboBox *iconComboBox;
      QCheckBox *showIconCheckBox;

      QGroupBox *messageGroupBox;
      QLabel *typeLabel;
      QLabel *durationLabel;
      QLabel *durationWarningLabel;
      QLabel *titleLabel;
      QLabel *bodyLabel;
      QComboBox *typeComboBox;
      QSpinBox *durationSpinBox;
      QLineEdit *titleEdit;
      QTextEdit *bodyEdit;
      QPushButton *showMessageButton;

      QAction *minimizeAction;
      QAction *maximizeAction;
      QAction *restoreAction;
      QAction *quitAction;
      bool m_quitNow;

      QSystemTrayIcon *trayIcon;
      QMenu *trayIconMenu;
};

#endif
