#ifndef XML_H
#define XML_H

#include "ui_xml.h"
#include "mdi.h"

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QStandardItem>

class Xml : public QWidget
{
   Q_OBJECT

   public:
      explicit Xml();
      ~Xml();

   private:
      Ui::Xml *ui;
      QString m_fileName;
      QStandardItemModel *m_model;

      void processXml();
      void parseElement(QStandardItem *parentItem, QDomElement element);
      void parseMealElement(QStandardItem *parentItem, QDomElement element);
      QStandardItem *addElement(QStandardItem *parentItem, QString text);

   private slots:
      void actionOpenXml();
      void actionClose();

};

#endif
