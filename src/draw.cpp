/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#include "draw_area.h"
#include "draw.h"

#include <QtGui>

const int IdRole = Qt::UserRole;

Draw::Draw()
   : QWidget()
{
    setWindowTitle(tr("Basic Drawing"));

    m_renderArea = new DrawArea;

    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("Polygon"),    DrawArea::Polygon);
    shapeComboBox->addItem(tr("Rectangle"),  DrawArea::Rect);
    shapeComboBox->addItem(tr("Rounded Rectangle"), DrawArea::RoundedRect);
    shapeComboBox->addItem(tr("Ellipse"),    DrawArea::Ellipse);
    shapeComboBox->addItem(tr("Pie"),        DrawArea::Pie);
    shapeComboBox->addItem(tr("Chord"),      DrawArea::Chord);
    shapeComboBox->addItem(tr("Path"),       DrawArea::Path);
    shapeComboBox->addItem(tr("Line"),       DrawArea::Line);
    shapeComboBox->addItem(tr("Polyline"),   DrawArea::Polyline);
    shapeComboBox->addItem(tr("Arc"),        DrawArea::Arc);
    shapeComboBox->addItem(tr("Points"),     DrawArea::Points);
    shapeComboBox->addItem(tr("Text"),       DrawArea::Text);

    shapeLabel = new QLabel(tr("&Shape:"));
    shapeLabel->setBuddy(shapeComboBox);

    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 20);
    penWidthSpinBox->setSpecialValueText(tr("0 (cosmetic pen)"));

    penWidthLabel = new QLabel(tr("Pen &Width:"));
    penWidthLabel->setBuddy(penWidthSpinBox);

    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("Solid"), Qt::SolidLine);
    penStyleComboBox->addItem(tr("Dash"), Qt::DashLine);
    penStyleComboBox->addItem(tr("Dot"), Qt::DotLine);
    penStyleComboBox->addItem(tr("Dash Dot"), Qt::DashDotLine);
    penStyleComboBox->addItem(tr("Dash Dot Dot"), Qt::DashDotDotLine);
    penStyleComboBox->addItem(tr("None"), Qt::NoPen);

    penStyleLabel = new QLabel(tr("&Pen Style:"));
    penStyleLabel->setBuddy(penStyleComboBox);

    penCapComboBox = new QComboBox;
    penCapComboBox->addItem(tr("Flat"), Qt::FlatCap);
    penCapComboBox->addItem(tr("Square"), Qt::SquareCap);
    penCapComboBox->addItem(tr("Round"), Qt::RoundCap);

    penCapLabel = new QLabel(tr("Pen &Cap:"));
    penCapLabel->setBuddy(penCapComboBox);

    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem(tr("Miter"), Qt::MiterJoin);
    penJoinComboBox->addItem(tr("Bevel"), Qt::BevelJoin);
    penJoinComboBox->addItem(tr("Round"), Qt::RoundJoin);

    penJoinLabel = new QLabel(tr("Pen &Join:"));
    penJoinLabel->setBuddy(penJoinComboBox);    

    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("Linear Gradient"),  Qt::LinearGradientPattern);
    brushStyleComboBox->addItem(tr("Radial Gradient"),  Qt::RadialGradientPattern);
    brushStyleComboBox->addItem(tr("Conical Gradient"), Qt::ConicalGradientPattern);
    brushStyleComboBox->addItem(tr("Texture"), Qt::TexturePattern);
    brushStyleComboBox->addItem(tr("Solid"), Qt::SolidPattern);
    brushStyleComboBox->addItem(tr("Horizontal"), Qt::HorPattern);
    brushStyleComboBox->addItem(tr("Vertical"), Qt::VerPattern);
    brushStyleComboBox->addItem(tr("Cross"), Qt::CrossPattern);
    brushStyleComboBox->addItem(tr("Backward Diagonal"), Qt::BDiagPattern);
    brushStyleComboBox->addItem(tr("Forward Diagonal"), Qt::FDiagPattern);
    brushStyleComboBox->addItem(tr("Diagonal Cross"), Qt::DiagCrossPattern);
    brushStyleComboBox->addItem(tr("Dense 1"), Qt::Dense1Pattern);
    brushStyleComboBox->addItem(tr("Dense 2"), Qt::Dense2Pattern);
    brushStyleComboBox->addItem(tr("Dense 3"), Qt::Dense3Pattern);
    brushStyleComboBox->addItem(tr("Dense 4"), Qt::Dense4Pattern);
    brushStyleComboBox->addItem(tr("Dense 5"), Qt::Dense5Pattern);
    brushStyleComboBox->addItem(tr("Dense 6"), Qt::Dense6Pattern);
    brushStyleComboBox->addItem(tr("Dense 7"), Qt::Dense7Pattern);
    brushStyleComboBox->addItem(tr("None"), Qt::NoBrush);

    brushStyleLabel = new QLabel(tr("&Brush:"));
    brushStyleLabel->setBuddy(brushStyleComboBox);

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
    DrawArea::Shape shape = DrawArea::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());
    m_renderArea->setShape(shape);
}

void Draw::penChanged()
{
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
            penStyleComboBox->currentIndex(), IdRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
            penCapComboBox->currentIndex(), IdRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
            penJoinComboBox->currentIndex(), IdRole).toInt());

    m_renderArea->setPen(QPen(Qt::blue, width, style, cap, join));
}

void Draw::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
        brushStyleComboBox->currentIndex(), IdRole).toInt());

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

