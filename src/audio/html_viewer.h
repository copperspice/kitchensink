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

#ifndef HTML_VIEWER_H
#define HTML_VIEWER_H

#include "ui_html_viewer.h"

#include <QMainWindow>
#include <QMenu>

class QUrl;

class Html_Viewer : public QMainWindow
{
   CS_OBJECT(Html_Viewer)

   public:
      Html_Viewer();
      ~Html_Viewer();

   private:
      void createActions();
      void setStartupText();

      CS_SLOT_1(Private, void about())
      CS_SLOT_2(about)

      CS_SLOT_1(Private, void open())
      CS_SLOT_2(open)

      CS_SLOT_1(Private, void openUrl())
      CS_SLOT_2(openUrl)

      CS_SLOT_1(Private, void save())
      CS_SLOT_2(save)

      CS_SLOT_1(Private, void updateTextEdit())
      CS_SLOT_2(updateTextEdit)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      CS_SLOT_1(Private, void actionPreview())
      CS_SLOT_2(actionPreview)

      Ui::Html_Form *ui;
      QUrl m_baseUrl;
};

#endif
