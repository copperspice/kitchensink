/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QWidget>

class Calendar : public QWidget
{
   CS_OBJECT(Calendar)

      CS_SLOT_1(Private, void weekdayFormatChanged())
      CS_SLOT_2(weekdayFormatChanged)

      CS_SLOT_1(Private, void weekendFormatChanged())
      CS_SLOT_2(weekendFormatChanged)

      CS_SLOT_1(Private, void reformatHeaders())
      CS_SLOT_2(reformatHeaders)

      CS_SLOT_1(Private, void reformatCalendarPage())
      CS_SLOT_2(reformatCalendarPage)
 public:
   Calendar();

 private:
   QComboBox *createColorComboBox();

   void createCalendarGroupBox();
   void createGeneralOptionsGroupBox();
   void createDatesGroupBox();
   void createTextFormatsGroupBox();

   // slot methods
   void localeChanged(int index);
   void firstDayChanged(int index);
   void selectionModeChanged(int index);
   void horizontalHeaderChanged(int index);
   void verticalHeaderChanged(int index);

   void selectedDateChanged();
   void minimumDateChanged(const QDate &date);
   void maximumDateChanged(const QDate &date);

   QGroupBox *calendarGroupBox;
   QGridLayout *calendarLayout;
   QCalendarWidget *m_calendar;

   QGroupBox *generalOptionsGroupBox;
   QLabel *localeLabel;
   QLabel *firstDayLabel;

   QLabel *selectionModeLabel;
   QLabel *horizontalHeaderLabel;
   QLabel *verticalHeaderLabel;

   QComboBox *localeCombo;
   QComboBox *firstDayCombo;
   QComboBox *selectionModeCombo;

   QComboBox *horizontalCombo;
   QComboBox *verticalCombo;

   QCheckBox *gridCheckBox;
   QCheckBox *navigationCheckBox;

   QGroupBox *datesGroupBox;
   QLabel *currentDateLabel;
   QLabel *minimumDateLabel;
   QLabel *maximumDateLabel;
   QDateEdit *currentDateEdit;
   QDateEdit *minimumDateEdit;
   QDateEdit *maximumDateEdit;

   QGroupBox *textFormatsGroupBox;
   QLabel *weekdayColorLabel;
   QLabel *weekendColorLabel;
   QLabel *headerTextFormatLabel;
   QComboBox *weekdayColorCombo;
   QComboBox *weekendColorCombo;
   QComboBox *headerTextFormatCombo;

   QCheckBox *firstFridayCheckBox;
   QCheckBox *mayFirstCheckBox;
};

#endif
