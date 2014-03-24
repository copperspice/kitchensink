
#ifndef GRABBER_H
#define GRABBER_H

#include <QMainWindow>
#include <QMenu>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QScrollArea;
class QSlider;
QT_END_NAMESPACE
class GLWidget;

class Grabber : public QMainWindow
{
      CS_OBJECT(Grabber)

   public:
      Grabber(QWidget *parent = 0);

   private :
      CS_SLOT_1(Private, void renderIntoPixmap())
      CS_SLOT_2(renderIntoPixmap) 
      CS_SLOT_1(Private, void grabFrameBuffer())
      CS_SLOT_2(grabFrameBuffer) 
      CS_SLOT_1(Private, void clearPixmap())
      CS_SLOT_2(clearPixmap) 
      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose) 
      CS_SLOT_1(Private, void about())
      CS_SLOT_2(about) 

   private:
      void createActions();
      void createMenus();
      QSlider *createSlider(const char *changedSignal, const char *setterSlot);
      void setPixmap(const QPixmap &pixmap);
      QSize getSize();

      QWidget *centralWidget;
      QScrollArea *glWidgetArea;
      QScrollArea *pixmapLabelArea;
      GLWidget *glWidget;
      QLabel *pixmapLabel;
      QSlider *xSlider;
      QSlider *ySlider;
      QSlider *zSlider;

      QMenu *fileMenu;
      QMenu *helpMenu;

      QAction *grabFrameBufferAct;
      QAction *renderIntoPixmapAct;
      QAction *clearPixmapAct;
      QAction *exitAct;
      QAction *aboutAct;
      QAction *aboutQtAct;
};

#endif
