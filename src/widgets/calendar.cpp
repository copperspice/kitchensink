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

#include "calendar.h"
#include "util.h"

#include <QTextCharFormat>

Calendar::Calendar()
   : QWidget()
{
   createCalendarGroupBox();
   createDatesGroupBox();
   createGeneralOptionsGroupBox();
   createTextFormatsGroupBox();

   setWindowTitle(tr("Calendar Widget"));

   QGridLayout *layout = new QGridLayout;
   layout->addWidget(calendarGroupBox, 0, 0);
   layout->addWidget(datesGroupBox, 1, 0);
   layout->addWidget(generalOptionsGroupBox, 0, 1);
   layout->addWidget(textFormatsGroupBox, 1, 1);
   layout->setSizeConstraint(QLayout::SetFixedSize);
   setLayout(layout);

   calendarLayout->setRowMinimumHeight(0,   m_calendar->sizeHint().height());
   calendarLayout->setColumnMinimumWidth(0, m_calendar->sizeHint().width());
}

void Calendar::localeChanged(int index)
{
   m_calendar->setLocale(localeCombo->itemData(index).toLocale());
}

void Calendar::firstDayChanged(int index)
{
   m_calendar->setFirstDayOfWeek(Qt::DayOfWeek(firstDayCombo->itemData(index).toInt()));
}

void Calendar::selectionModeChanged(int index)
{
   m_calendar->setSelectionMode(QCalendarWidget::SelectionMode(selectionModeCombo->itemData(index).toInt()));
}

void Calendar::horizontalHeaderChanged(int index)
{
   m_calendar->setHorizontalHeaderFormat(
            QCalendarWidget::HorizontalHeaderFormat(horizontalHeaderCombo->itemData(index).toInt()));
}

void Calendar::verticalHeaderChanged(int index)
{
   m_calendar->setVerticalHeaderFormat(
            QCalendarWidget::VerticalHeaderFormat(verticalHeaderCombo->itemData(index).toInt()));
}

void Calendar::selectedDateChanged()
{
   currentDateEdit->setDate(m_calendar->selectedDate());
}

void Calendar::minimumDateChanged(const QDate &date)
{
   m_calendar->setMinimumDate(date);
   maximumDateEdit->setDate(m_calendar->maximumDate());
}

void Calendar::maximumDateChanged(const QDate &date)
{
   m_calendar->setMaximumDate(date);
   minimumDateEdit->setDate(m_calendar->minimumDate());
}

void Calendar::weekdayFormatChanged()
{
   QTextCharFormat format;
   format.setForeground( weekdayColorCombo->itemData(weekdayColorCombo->currentIndex()).value<QColor>() );

   m_calendar->setWeekdayTextFormat(Qt::Monday,    format);
   m_calendar->setWeekdayTextFormat(Qt::Tuesday,   format);
   m_calendar->setWeekdayTextFormat(Qt::Wednesday, format);
   m_calendar->setWeekdayTextFormat(Qt::Thursday,  format);
   m_calendar->setWeekdayTextFormat(Qt::Friday,    format);

   reformatCalendarPage();
}

void Calendar::weekendFormatChanged()
{
   QTextCharFormat format;
   format.setForeground( weekendColorCombo->itemData(weekendColorCombo->currentIndex()).value<QColor>() );

   m_calendar->setWeekdayTextFormat(Qt::Saturday, format);
   m_calendar->setWeekdayTextFormat(Qt::Sunday,   format);
}

void Calendar::reformatHeaders()
{
   QString text = headerTextFormatCombo->currentText();
   QTextCharFormat format;

   if (text == tr("Bold")) {
      format.setFontWeight(QFont::Bold);

   } else if (text == tr("Italic")) {
      format.setFontItalic(true);

   } else if (text == tr("Green")) {
      format.setForeground(Qt::green);

   }
   m_calendar->setHeaderTextFormat(format);
}

void Calendar::reformatCalendarPage()
{
   // first Friday of the month
   QDate firstFriday(m_calendar->yearShown(), m_calendar->monthShown(), 1);

   while (firstFriday.dayOfWeek() != Qt::Friday) {
      firstFriday = firstFriday.addDays(1);
   }

   QTextCharFormat firstFridayFormat;

   if (firstFridayCheckBox->isChecked()) {
      firstFridayFormat.setForeground(Qt::blue);
      m_calendar->setDateTextFormat(firstFriday, firstFridayFormat);

   } else {
      firstFridayFormat.setForeground( weekdayColorCombo->itemData(weekdayColorCombo->currentIndex()).value<QColor>() );
      m_calendar->setDateTextFormat(firstFriday, firstFridayFormat);

   }

   // May 1st in red takes precedence over first Friday
   const QDate mayFirst(m_calendar->yearShown(), 5, 1);
   QTextCharFormat mayFirstFormat;

   if (mayFirstCheckBox->isChecked()) {
      mayFirstFormat.setForeground(Qt::red);
      m_calendar->setDateTextFormat(mayFirst, mayFirstFormat);

   } else {

      if (! firstFridayCheckBox->isChecked() ) {
         mayFirstFormat.setForeground( weekdayColorCombo->itemData(weekdayColorCombo->currentIndex()).value<QColor>() );
         m_calendar->setDateTextFormat(mayFirst, mayFirstFormat);
      }
   }
}

void Calendar::createCalendarGroupBox()
{
   calendarGroupBox = new QGroupBox(tr("Preview"));

   QFont font = calendarGroupBox->font();
   font.setPointSize(10);
   calendarGroupBox->setFont(font);

   m_calendar = new QCalendarWidget;
   m_calendar->setMinimumDate(QDate(1900, 1, 1));
   m_calendar->setMaximumDate(QDate(2300, 1, 1));
   m_calendar->setGridVisible(true);

   connect(m_calendar, SIGNAL(currentPageChanged(int,int)), this, SLOT(reformatCalendarPage()));

   calendarLayout = new QGridLayout;
   calendarLayout->addWidget(m_calendar, 0, 0, Qt::AlignCenter);
   calendarGroupBox->setLayout(calendarLayout);
}

void Calendar::createGeneralOptionsGroupBox()
{
   generalOptionsGroupBox = new QGroupBox(tr("General Options"));

   QFont font = generalOptionsGroupBox->font();
   font.setPointSize(10);
   generalOptionsGroupBox->setFont(font);

   localeCombo = new QComboBox;
   int curLocaleIndex = -1;
   int index = 0;

   for (int _lang = QLocale::C; _lang <= QLocale::LastLanguage; ++_lang) {
      QLocale::Language lang = static_cast<QLocale::Language>(_lang);
      QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);

      for (int i = 0; i < countries.count(); ++i) {
         QLocale::Country country = countries.at(i);
         QString label = QLocale::languageToString(lang);
         label += QLatin1Char('/');
         label += QLocale::countryToString(country);

         QLocale locale(lang, country);
         if (this->locale().language() == lang && this->locale().country() == country) {
            curLocaleIndex = index;
         }

         localeCombo->addItem(label, locale);
         ++index;
      }
   }

   if (curLocaleIndex != -1) {
      localeCombo->setCurrentIndex(curLocaleIndex);
   }

   localeLabel = new QLabel(tr("&Locale"));
   localeLabel->setBuddy(localeCombo);

   firstDayCombo = new QComboBox;
   firstDayCombo->addItem(tr("Sunday"),    Qt::Sunday);
   firstDayCombo->addItem(tr("Monday"),    Qt::Monday);
   firstDayCombo->addItem(tr("Tuesday"),   Qt::Tuesday);
   firstDayCombo->addItem(tr("Wednesday"), Qt::Wednesday);
   firstDayCombo->addItem(tr("Thursday"),  Qt::Thursday);
   firstDayCombo->addItem(tr("Friday"),    Qt::Friday);
   firstDayCombo->addItem(tr("Saturday"),  Qt::Saturday);

   firstDayLabel = new QLabel(tr("Wee&k starts on:"));
   firstDayLabel->setBuddy(firstDayCombo);

   selectionModeCombo = new QComboBox;
   selectionModeCombo->addItem(tr("Single selection"), QCalendarWidget::SingleSelection);
   selectionModeCombo->addItem(tr("None"), QCalendarWidget::NoSelection);

   selectionModeLabel = new QLabel(tr("&Selection mode:"));
   selectionModeLabel->setBuddy(selectionModeCombo);

   horizontalHeaderCombo = new QComboBox;
   horizontalHeaderCombo->addItem(tr("Single letter day names"), QCalendarWidget::SingleLetterDayNames);
   horizontalHeaderCombo->addItem(tr("Short day names"), QCalendarWidget::ShortDayNames);
   horizontalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoHorizontalHeader);
   horizontalHeaderCombo->setCurrentIndex(1);

   horizontalHeaderLabel = new QLabel(tr("&Horizontal header:"));
   horizontalHeaderLabel->setBuddy(horizontalHeaderCombo);

   verticalHeaderCombo = new QComboBox;
   verticalHeaderCombo->addItem(tr("ISO week numbers"),QCalendarWidget::ISOWeekNumbers);
   verticalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoVerticalHeader);

   verticalHeaderLabel = new QLabel(tr("&Vertical header:"));
   verticalHeaderLabel->setBuddy(verticalHeaderCombo);

   gridCheckBox = new QCheckBox(tr("&Show Grid"));
   gridCheckBox->setChecked(m_calendar->isGridVisible());

   navigationCheckBox = new QCheckBox(tr("&Navigation bar"));
   navigationCheckBox->setChecked(true);

   connect(localeCombo,          SIGNAL(currentIndexChanged(int)), this, SLOT(localeChanged(int)));
   connect(firstDayCombo,        SIGNAL(currentIndexChanged(int)), this, SLOT(firstDayChanged(int)));
   connect(selectionModeCombo,   SIGNAL(currentIndexChanged(int)), this, SLOT(selectionModeChanged(int)));
   connect(gridCheckBox,         SIGNAL(toggled(bool)), m_calendar,      SLOT(setGridVisible(bool)));
   connect(navigationCheckBox,   SIGNAL(toggled(bool)), m_calendar,      SLOT(setNavigationBarVisible(bool)));
   connect(horizontalHeaderCombo,SIGNAL(currentIndexChanged(int)), this, SLOT(horizontalHeaderChanged(int)));
   connect(verticalHeaderCombo,  SIGNAL(currentIndexChanged(int)), this, SLOT(verticalHeaderChanged(int)));

   QHBoxLayout *checkBoxLayout = new QHBoxLayout;
   checkBoxLayout->addWidget(gridCheckBox);
   checkBoxLayout->addStretch();
   checkBoxLayout->addWidget(navigationCheckBox);

   QGridLayout *outerLayout = new QGridLayout;
   outerLayout->addWidget(localeLabel,        0, 0);
   outerLayout->addWidget(localeCombo,        0, 1);
   outerLayout->addWidget(firstDayLabel,      1, 0);
   outerLayout->addWidget(firstDayCombo,      1, 1);
   outerLayout->addWidget(selectionModeLabel, 2, 0);
   outerLayout->addWidget(selectionModeCombo, 2, 1);
   outerLayout->addWidget(horizontalHeaderLabel, 3, 0);
   outerLayout->addWidget(horizontalHeaderCombo, 3, 1);
   outerLayout->addWidget(verticalHeaderLabel,   4, 0);
   outerLayout->addWidget(verticalHeaderCombo,   4, 1);
   outerLayout->addLayout(checkBoxLayout,        5, 1);
   outerLayout->setHorizontalSpacing(10);
   generalOptionsGroupBox->setLayout(outerLayout);

   firstDayChanged(firstDayCombo->currentIndex());
   selectionModeChanged(selectionModeCombo->currentIndex());
   horizontalHeaderChanged(horizontalHeaderCombo->currentIndex());
   verticalHeaderChanged(verticalHeaderCombo->currentIndex());
}

void Calendar::createDatesGroupBox()
{
   datesGroupBox = new QGroupBox(tr("Dates"));

   QFont font = datesGroupBox->font();
   font.setPointSize(10);
   datesGroupBox->setFont(font);

   minimumDateEdit = new QDateEdit;
   minimumDateEdit->setDisplayFormat("MMM d yyyy");
   minimumDateEdit->setDateRange(m_calendar->minimumDate(),m_calendar->maximumDate());
   minimumDateEdit->setDate(m_calendar->minimumDate());

   minimumDateLabel = new QLabel(tr("&Minimum Date:"));
   minimumDateLabel->setBuddy(minimumDateEdit);

   currentDateEdit = new QDateEdit;
   currentDateEdit->setDisplayFormat("MMM d yyyy");
   currentDateEdit->setDate(m_calendar->selectedDate());
   currentDateEdit->setDateRange(m_calendar->minimumDate(),m_calendar->maximumDate());

   currentDateLabel = new QLabel(tr("&Current Date:"));
   currentDateLabel->setBuddy(currentDateEdit);

   maximumDateEdit = new QDateEdit;
   maximumDateEdit->setDisplayFormat("MMM d yyyy");
   maximumDateEdit->setDateRange(m_calendar->minimumDate(),m_calendar->maximumDate());
   maximumDateEdit->setDate(m_calendar->maximumDate());

   maximumDateLabel = new QLabel(tr("Ma&ximum Date:"));
   maximumDateLabel->setBuddy(maximumDateEdit);

   connect(currentDateEdit, SIGNAL(dateChanged(const QDate &)), m_calendar, SLOT(setSelectedDate(const QDate &)));
   connect(m_calendar,      SIGNAL(selectionChanged()),         this,       SLOT(selectedDateChanged()));
   connect(minimumDateEdit, SIGNAL(dateChanged(const QDate &)), this,       SLOT(minimumDateChanged(const QDate &)));
   connect(maximumDateEdit, SIGNAL(dateChanged(const QDate &)), this,       SLOT(maximumDateChanged(const QDate &)));

   QGridLayout *dateBoxLayout = new QGridLayout;
   dateBoxLayout->addWidget(minimumDateLabel,   0, 0);
   dateBoxLayout->addWidget(minimumDateEdit,    0, 1);
   dateBoxLayout->addWidget(currentDateLabel,   1, 0);
   dateBoxLayout->addWidget(currentDateEdit,    1, 1);
   dateBoxLayout->addWidget(maximumDateLabel,   2, 0);
   dateBoxLayout->addWidget(maximumDateEdit,    2, 1);
   dateBoxLayout->setRowStretch(3, 1);

   datesGroupBox->setLayout(dateBoxLayout);
}

void Calendar::createTextFormatsGroupBox()
{
   textFormatsGroupBox = new QGroupBox(tr("Text Formats"));

   QFont font = textFormatsGroupBox->font();
   font.setPointSize(10);
   textFormatsGroupBox->setFont(font);

   weekdayColorCombo = createColorComboBox();
   weekdayColorCombo->setCurrentIndex(weekdayColorCombo->findText(tr("Black")));

   weekdayColorLabel = new QLabel(tr("&Monday to Friday:"));
   weekdayColorLabel->setBuddy(weekdayColorCombo);

   weekendColorCombo = createColorComboBox();
   weekendColorCombo->setCurrentIndex(weekendColorCombo->findText(tr("Red")));

   weekendColorLabel = new QLabel(tr("Saturday, Sunday:"));
   weekendColorLabel->setBuddy(weekendColorCombo);

   //
   headerTextFormatCombo = new QComboBox;
   headerTextFormatCombo->addItem(tr("Bold"));
   headerTextFormatCombo->addItem(tr("Italic"));
   headerTextFormatCombo->addItem(tr("Plain"));

   headerTextFormatLabel = new QLabel(tr("&Header text:"));
   headerTextFormatLabel->setBuddy(headerTextFormatCombo);

   firstFridayCheckBox = new QCheckBox(tr("First Friday (blue)"));
   mayFirstCheckBox    = new QCheckBox(tr("May first (red)"));

   connect(weekdayColorCombo,    SIGNAL(currentIndexChanged(int)), this, SLOT(weekdayFormatChanged()));
   connect(weekendColorCombo,    SIGNAL(currentIndexChanged(int)), this, SLOT(weekendFormatChanged()));
   connect(headerTextFormatCombo,SIGNAL(currentIndexChanged(const QString &)), this, SLOT(reformatHeaders()));
   connect(firstFridayCheckBox,  SIGNAL(toggled(bool)), this, SLOT(reformatCalendarPage()));
   connect(mayFirstCheckBox,     SIGNAL(toggled(bool)), this, SLOT(reformatCalendarPage()));

   //
   QHBoxLayout *checkBoxLayout = new QHBoxLayout;
   checkBoxLayout->addWidget(firstFridayCheckBox);
   checkBoxLayout->addStretch();
   checkBoxLayout->addWidget(mayFirstCheckBox);

   QGridLayout *outerLayout = new QGridLayout;
   outerLayout->addWidget(weekdayColorLabel,     0, 0);
   outerLayout->addWidget(weekdayColorCombo,     0, 1);
   outerLayout->addWidget(weekendColorLabel,     1, 0);
   outerLayout->addWidget(weekendColorCombo,     1, 1);
   outerLayout->addWidget(headerTextFormatLabel, 2, 0);
   outerLayout->addWidget(headerTextFormatCombo, 2, 1);
   outerLayout->addLayout(checkBoxLayout,        3, 1);

   outerLayout->setColumnStretch(0, 1);
   outerLayout->setColumnStretch(1, 3);
   outerLayout->setHorizontalSpacing(10);
   textFormatsGroupBox->setLayout(outerLayout);

   weekdayFormatChanged();
   weekendFormatChanged();

   reformatHeaders();
   reformatCalendarPage();
}

QComboBox *Calendar::createColorComboBox()
{
   QComboBox *comboBox = new QComboBox;
   comboBox->addItem(tr("Black"),   QColor(Qt::black));
   comboBox->addItem(tr("Blue"),    QColor(Qt::blue));
   comboBox->addItem(tr("Green"),   QColor(Qt::green));
   comboBox->addItem(tr("Red"),     QColor(Qt::darkRed));
   comboBox->addItem(tr("Magenta"), QColor(Qt::magenta));
   comboBox->addItem(tr("Yellow"),  QColor(Qt::darkYellow));

   return comboBox;
}
