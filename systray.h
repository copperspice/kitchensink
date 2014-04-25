/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
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
};


#endif
