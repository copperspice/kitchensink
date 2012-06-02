#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "ui_translate.h"

#include <QWidget>

class Translate : public QWidget
{
   Q_OBJECT

   public:
      Translate();
      ~Translate();

   private:
      Ui::Translate *ui;
      QTranslator *m_translator;
      void retranslateUi();
      void changeEvent(QEvent *event);

   private slots:
      void actionClose();      
      void actionEnglish();
      void actionFrench();
      void actionGerman();      
};

#endif
