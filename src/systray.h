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

      CS_SLOT_1(Private, void setIcon(int index))
      CS_SLOT_2(setIcon)

      CS_SLOT_1(Private, void iconActivated(QSystemTrayIcon::ActivationReason reason))
      CS_SLOT_2(iconActivated)

      CS_SLOT_1(Private, void showMessage())
      CS_SLOT_2(showMessage)

      CS_SLOT_1(Private, void messageClicked())
      CS_SLOT_2(messageClicked)

      CS_SLOT_1(Private, void actionQuit())
      CS_SLOT_2(actionQuit)

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
