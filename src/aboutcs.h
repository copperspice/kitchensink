/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
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
      QSize sizeHint() const;

   private:
      // slot declarations
      void actionClose();
      void actionHome();

      QWebView *m_viewer;
};

#endif
