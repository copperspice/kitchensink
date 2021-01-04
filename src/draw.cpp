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

#include "draw_area.h"
#include "draw.h"

#include <QGridLayout>

const int IdRole = Qt::UserRole;

Draw::Draw()
   : QWidget()
{
   setWindowTitle(tr("Basic Drawing"));

   m_renderArea = new DrawArea;

   shapeComboBox = new QComboBox;
   shapeComboBox->addItem(tr("Polygon"),           QVariant::fromValue(DrawArea::Shape::Polygon));
   shapeComboBox->addItem(tr("Rectangle"),         QVariant::fromValue(DrawArea::Shape::Rect));
   shapeComboBox->addItem(tr("Rounded Rectangle"), QVariant::fromValue(DrawArea::Shape::RoundedRect));
   shapeComboBox->addItem(tr("Ellipse"),           QVariant::fromValue(DrawArea::Shape::Ellipse));
   shapeComboBox->addItem(tr("Pie"),               QVariant::fromValue(DrawArea::Shape::Pie));
   shapeComboBox->addItem(tr("Chord"),             QVariant::fromValue(DrawArea::Shape::Chord));
   shapeComboBox->addItem(tr("Path"),              QVariant::fromValue(DrawArea::Shape::Path));
   shapeComboBox->addItem(tr("Line"),              QVariant::fromValue(DrawArea::Shape::Line));
   shapeComboBox->addItem(tr("Polyline"),          QVariant::fromValue(DrawArea::Shape::Polyline));
   shapeComboBox->addItem(tr("Arc"),               QVariant::fromValue(DrawArea::Shape::Arc));
   shapeComboBox->addItem(tr("Points"),            QVariant::fromValue(DrawArea::Shape::Points));
   shapeComboBox->addItem(tr("Text"),              QVariant::fromValue(DrawArea::Shape::Text));

   shapeLabel = new QLabel(tr("&Shape:"));
   shapeLabel->setBuddy(shapeComboBox);

   penStyleComboBox = new QComboBox;
   penStyleComboBox->addItem(tr("Solid"),          QVariant::fromValue(Qt::SolidLine));
   penStyleComboBox->addItem(tr("Dash"),           QVariant::fromValue(Qt::DashLine));
   penStyleComboBox->addItem(tr("Dot"),            QVariant::fromValue(Qt::DotLine));
   penStyleComboBox->addItem(tr("Dash Dot"),       QVariant::fromValue(Qt::DashDotLine));
   penStyleComboBox->addItem(tr("Dash Dot Dot"),   QVariant::fromValue(Qt::DashDotDotLine));
   penStyleComboBox->addItem(tr("None"),           QVariant::fromValue(Qt::NoPen));

   penStyleLabel = new QLabel(tr("&Pen Style:"));
   penStyleLabel->setBuddy(penStyleComboBox);

   penCapComboBox = new QComboBox;
   penCapComboBox->addItem(tr("Flat"),    QVariant::fromValue(Qt::FlatCap));
   penCapComboBox->addItem(tr("Square"),  QVariant::fromValue(Qt::SquareCap));
   penCapComboBox->addItem(tr("Round"),   QVariant::fromValue(Qt::RoundCap));

   penCapLabel = new QLabel(tr("Pen &Cap:"));
   penCapLabel->setBuddy(penCapComboBox);

   penJoinComboBox = new QComboBox;
   penJoinComboBox->addItem(tr("Miter"),  QVariant::fromValue(Qt::MiterJoin));
   penJoinComboBox->addItem(tr("Bevel"),  QVariant::fromValue(Qt::BevelJoin));
   penJoinComboBox->addItem(tr("Round"),  QVariant::fromValue(Qt::RoundJoin));

   penJoinLabel = new QLabel(tr("Pen &Join:"));
   penJoinLabel->setBuddy(penJoinComboBox);

   brushStyleComboBox = new QComboBox;
   brushStyleComboBox->addItem(tr("Linear Gradient"),   QVariant::fromValue(Qt::LinearGradientPattern));
   brushStyleComboBox->addItem(tr("Radial Gradient"),   QVariant::fromValue(Qt::RadialGradientPattern));
   brushStyleComboBox->addItem(tr("Conical Gradient"),  QVariant::fromValue(Qt::ConicalGradientPattern));
   brushStyleComboBox->addItem(tr("Texture"),           QVariant::fromValue(Qt::TexturePattern));
   brushStyleComboBox->addItem(tr("Solid"),             QVariant::fromValue(Qt::SolidPattern));
   brushStyleComboBox->addItem(tr("Horizontal"),        QVariant::fromValue(Qt::HorPattern));
   brushStyleComboBox->addItem(tr("Vertical"),          QVariant::fromValue(Qt::VerPattern));
   brushStyleComboBox->addItem(tr("Cross"),             QVariant::fromValue(Qt::CrossPattern));
   brushStyleComboBox->addItem(tr("Backward Diagonal"), QVariant::fromValue(Qt::BDiagPattern));
   brushStyleComboBox->addItem(tr("Forward Diagonal"),  QVariant::fromValue(Qt::FDiagPattern));
   brushStyleComboBox->addItem(tr("Diagonal Cross"),    QVariant::fromValue(Qt::DiagCrossPattern));
   brushStyleComboBox->addItem(tr("Dense 1"),           QVariant::fromValue(Qt::Dense1Pattern));
   brushStyleComboBox->addItem(tr("Dense 2"),           QVariant::fromValue(Qt::Dense2Pattern));
   brushStyleComboBox->addItem(tr("Dense 3"),           QVariant::fromValue(Qt::Dense3Pattern));
   brushStyleComboBox->addItem(tr("Dense 4"),           QVariant::fromValue(Qt::Dense4Pattern));
   brushStyleComboBox->addItem(tr("Dense 5"),           QVariant::fromValue(Qt::Dense5Pattern));
   brushStyleComboBox->addItem(tr("Dense 6"),           QVariant::fromValue(Qt::Dense6Pattern));
   brushStyleComboBox->addItem(tr("Dense 7"),           QVariant::fromValue(Qt::Dense7Pattern));
   brushStyleComboBox->addItem(tr("None"),              QVariant::fromValue(Qt::NoBrush));

   brushStyleLabel = new QLabel(tr("&Brush:"));
   brushStyleLabel->setBuddy(brushStyleComboBox);

   penWidthSpinBox = new QSpinBox;
   penWidthSpinBox->setRange(0, 20);
   penWidthSpinBox->setSpecialValueText(tr("0 (cosmetic pen)"));

   penWidthLabel = new QLabel(tr("Pen &Width:"));
   penWidthLabel->setBuddy(penWidthSpinBox);

   otherOptionsLabel       = new QLabel(tr("Options:"));
   antialiasingCheckBox    = new QCheckBox(tr("&Antialiasing"));
   transformationsCheckBox = new QCheckBox(tr("&Transformations"));

   //
   QGridLayout *mainLayout = new QGridLayout;

   mainLayout->setColumnStretch(5, 1);
   mainLayout->setHorizontalSpacing(10);
   mainLayout->setVerticalSpacing(10);
   mainLayout->addWidget(m_renderArea,      0, 0, 1, 6);

   mainLayout->addWidget(shapeLabel,        2, 0);
   mainLayout->addWidget(shapeComboBox,     2, 1);
   mainLayout->addWidget(penWidthLabel,     3, 0);
   mainLayout->addWidget(penWidthSpinBox,   3, 1);
   mainLayout->addWidget(penStyleLabel,     4, 0);
   mainLayout->addWidget(penStyleComboBox,  4, 1);

   mainLayout->addWidget(penJoinLabel,      2, 3);
   mainLayout->addWidget(penJoinComboBox,   2, 4);
   mainLayout->addWidget(penCapLabel,       3, 3);
   mainLayout->addWidget(penCapComboBox,    3, 4);
   mainLayout->addWidget(brushStyleLabel,   4, 3);
   mainLayout->addWidget(brushStyleComboBox,4, 4);

   mainLayout->addWidget(otherOptionsLabel,       5, 0);
   mainLayout->addWidget(antialiasingCheckBox,    5, 1);
   mainLayout->addWidget(transformationsCheckBox, 5, 4);
   setLayout(mainLayout);

   // signals
   connect(shapeComboBox,           SIGNAL(activated(int)),     this, SLOT(shapeChanged()));
   connect(penWidthSpinBox,         SIGNAL(valueChanged(int)),  this, SLOT(penChanged()));
   connect(penStyleComboBox,        SIGNAL(activated(int)),     this, SLOT(penChanged()));
   connect(penCapComboBox,          SIGNAL(activated(int)),     this, SLOT(penChanged()));
   connect(penJoinComboBox,         SIGNAL(activated(int)),     this, SLOT(penChanged()));
   connect(brushStyleComboBox,      SIGNAL(activated(int)),     this, SLOT(brushChanged()));
   connect(antialiasingCheckBox,    SIGNAL(toggled(bool)),      m_renderArea, SLOT(setAntialiased(bool)));
   connect(transformationsCheckBox, SIGNAL(toggled(bool)),      m_renderArea, SLOT(setTransformed(bool)));

   shapeChanged();
   penChanged();
   brushChanged();
   antialiasingCheckBox->setChecked(true);
}

void Draw::shapeChanged()
{
   DrawArea::Shape shape = shapeComboBox->itemData(shapeComboBox->currentIndex(), IdRole).value<DrawArea::Shape>();
   m_renderArea->setShape(shape);
}

void Draw::penChanged()
{
   int width = penWidthSpinBox->value();
   Qt::PenStyle style    = penStyleComboBox->itemData(penStyleComboBox->currentIndex(), IdRole).value<Qt::PenStyle>();
   Qt::PenCapStyle cap   = penCapComboBox->itemData(penCapComboBox->currentIndex(), IdRole).value<Qt::PenCapStyle>();
   Qt::PenJoinStyle join = penJoinComboBox->itemData(penJoinComboBox->currentIndex(), IdRole).value<Qt::PenJoinStyle>();

   m_renderArea->setPen(QPen(Qt::blue, width, style, cap, join));
}

void Draw::brushChanged()
{
   Qt::BrushStyle style = brushStyleComboBox->itemData(brushStyleComboBox->currentIndex(), IdRole).value<Qt::BrushStyle>();

   if (style == Qt::LinearGradientPattern) {
     QLinearGradient linearGradient(0, 0, 100, 100);
     linearGradient.setColorAt(0.0, Qt::white);
     linearGradient.setColorAt(0.2, Qt::green);
     linearGradient.setColorAt(1.0, Qt::black);
     m_renderArea->setBrush(linearGradient);

   } else if (style == Qt::RadialGradientPattern) {
     QRadialGradient radialGradient(50, 50, 50, 70, 70);
     radialGradient.setColorAt(0.0, Qt::white);
     radialGradient.setColorAt(0.2, Qt::green);
     radialGradient.setColorAt(1.0, Qt::black);
     m_renderArea->setBrush(radialGradient);

   } else if (style == Qt::ConicalGradientPattern) {
     QConicalGradient conicalGradient(50, 50, 150);
     conicalGradient.setColorAt(0.0, Qt::white);
     conicalGradient.setColorAt(0.2, Qt::green);
     conicalGradient.setColorAt(1.0, Qt::black);
     m_renderArea->setBrush(conicalGradient);

   } else if (style == Qt::TexturePattern) {
     m_renderArea->setBrush(QBrush(QPixmap(":/resources/brick.png")));

   } else {
     m_renderArea->setBrush(QBrush(Qt::green, style));
   }
}
