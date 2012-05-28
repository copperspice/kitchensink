#ifndef ABOUTCS_H
#define ABOUTCS_H

#include <QWidget>
#include <QtWebKit>

class AboutCS : public QWidget
{
   Q_OBJECT

   public:
      AboutCS();

   private:
      QWebView *m_viewer;

   private slots:
      void actionClose();
      void actionHome();
};

#endif
