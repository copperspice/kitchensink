#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "ui_translate.h"

#include <QWidget>
#include <QStringListModel>

class Translate : public QWidget
{
   Q_OBJECT

   public:
      Translate();
      ~Translate();

   private:
      Ui::Translate *ui;
      QStringListModel *m_model;      
      static QTranslator *m_translator;

      void retranslateUi();
      void changeEvent(QEvent *event);
      void getListData();

   private slots:
      void actionClose();      
      void actionEnglish();
      void actionFrench();
      void actionGerman();      
};

#endif
