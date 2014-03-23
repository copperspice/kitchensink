
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
      Q_OBJECT

   public:
      Grabber(QWidget *parent = 0);

   private slots:
      void renderIntoPixmap();
      void grabFrameBuffer();
      void clearPixmap();
      void actionClose();
      void about();

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
