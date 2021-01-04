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

#include "draglabel.h"
#include "fridgemag.h"

#include <QByteArray>
#include <QDrag>
#include <QMimeData>
#include <QPoint>
#include <QTextStream>
#include <QString>

static const QString qmPath = ":/resources";

FridgeMagnet::FridgeMagnet(QWidget *parent)
   : QWidget(parent)
{
   setWindowTitle(tr("Fridge Magnets"));
   setAcceptDrops(true);

   //
   QString fileName;
   fileName = qmPath + "/words.txt";

   QFile dictionaryFile(fileName);
   dictionaryFile.open(QFile::ReadOnly);

   QTextStream inputStream(&dictionaryFile);

   int x = 5;
   int y = 5;

   while (! inputStream.atEnd()) {
      QString word;
      inputStream >> word;

      if (! word.isEmpty()) {
         DragLabel *wordLabel = new DragLabel(word, this);
         wordLabel->move(x, y);
         wordLabel->show();
         wordLabel->setAttribute(Qt::WA_DeleteOnClose);
         x += wordLabel->width() + 2;

         if (x >= 245) {
            x = 5;
            y += wordLabel->height() + 2;
         }
      }
   }

}

void FridgeMagnet::dragEnterEvent(QDragEnterEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
      if (children().contains(event->source())) {
         event->setDropAction(Qt::MoveAction);
         event->accept();

      } else {
         event->acceptProposedAction();
      }

   } else if (event->mimeData()->hasText()) {
      event->acceptProposedAction();

   } else {
      event->ignore();
   }
}

void FridgeMagnet::dragMoveEvent(QDragMoveEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
      if (children().contains(event->source())) {
         event->setDropAction(Qt::MoveAction);
         event->accept();
      } else {
         event->acceptProposedAction();
      }

   } else if (event->mimeData()->hasText()) {
      event->acceptProposedAction();

   } else {
      event->ignore();
   }
}

void FridgeMagnet::dropEvent(QDropEvent *event)
{
   if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
      const QMimeData *mime = event->mimeData();

      QByteArray itemData = mime->data("application/x-fridgemagnet");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);

      QString text;
      QPoint offset;
      dataStream >> text >> offset;

      DragLabel *newLabel = new DragLabel(text, this);

      newLabel->move(event->pos() - offset);
      newLabel->show();
      newLabel->setAttribute(Qt::WA_DeleteOnClose);

      if (event->source() == this) {
         event->setDropAction(Qt::MoveAction);
         event->accept();

      } else {
         event->acceptProposedAction();

      }

   } else if (event->mimeData()->hasText()) {
      QStringList pieces = event->mimeData()->text().split(QRegularExpression("\\s+"), QStringParser::SkipEmptyParts);
      QPoint position = event->pos();

      for (QString piece : pieces) {
         DragLabel *newLabel = new DragLabel(piece, this);
         newLabel->move(position);
         newLabel->show();
         newLabel->setAttribute(Qt::WA_DeleteOnClose);

         position += QPoint(newLabel->width(), 0);
      }

      event->acceptProposedAction();

   } else {
      event->ignore();

   }
}

void FridgeMagnet::mousePressEvent(QMouseEvent *event)
{
   DragLabel *child = dynamic_cast<DragLabel*>(childAt(event->pos()));

   if (! child) {
      return;
   }

   QPoint hotSpot = event->pos() - child->pos();

   QByteArray itemData;
   QDataStream dataStream(&itemData, QIODevice::WriteOnly);
   dataStream << child->labelText() << QPoint(hotSpot);

   QMimeData *mimeData = new QMimeData;
   mimeData->setData("application/x-fridgemagnet", itemData);
   mimeData->setText(child->labelText());

   QDrag *drag = new QDrag(this);
   drag->setMimeData(mimeData);
   drag->setPixmap(*child->pixmap());
   drag->setHotSpot(hotSpot);

   child->hide();

   if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)  {
      child->close();

   } else {
      child->show();

   }
}

QSize FridgeMagnet::sizeHint() const
{
   return QSize(400,400);
}
