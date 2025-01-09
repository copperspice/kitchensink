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

#ifndef ABOUTCS_H
#define ABOUTCS_H

#include <QWidget>

class QWebView;

class AboutCS : public QWidget
{
   CS_OBJECT(AboutCS)

 public:
   AboutCS(QString route);

 protected:
   QSize sizeHint() const override;

 private:
   // slot declarations
   void actionClose();
   void actionHome();

   QWebView *m_viewer;
};

#endif
