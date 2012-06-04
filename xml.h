#ifndef XML_H
#define XML_H

#include "ui_xml.h"
#include "mdi.h"

#include <QWidget>
#include <QDomDocument>

class Xml : public QWidget
{
   Q_OBJECT

   public:
      explicit Xml(Mdi *parent = 0);
      ~Xml();

   private:
      Ui::Xml *ui;
      //void parseMenu(QDomElement element);

   private slots:
      void actionOpenXml();
      void actionClose();

};

#endif
