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

   public:
      Calendar();

   private:
      void createCalendarGroupBox();
      void createGeneralOptionsGroupBox();
      void createDatesGroupBox();
      void createTextFormatsGroupBox();
      QComboBox *createColorComboBox();

      CS_SLOT_1(Private, void localeChanged(int index))
      CS_SLOT_2(localeChanged)

      CS_SLOT_1(Private, void firstDayChanged(int index))
      CS_SLOT_2(firstDayChanged)

      CS_SLOT_1(Private, void selectionModeChanged(int index))
      CS_SLOT_2(selectionModeChanged)

      CS_SLOT_1(Private, void horizontalHeaderChanged(int index))
      CS_SLOT_2(horizontalHeaderChanged)

      CS_SLOT_1(Private, void verticalHeaderChanged(int index))
      CS_SLOT_2(verticalHeaderChanged)

      CS_SLOT_1(Private, void selectedDateChanged())
      CS_SLOT_2(selectedDateChanged)

      CS_SLOT_1(Private, void minimumDateChanged(const QDate & date))
      CS_SLOT_2(minimumDateChanged)

      CS_SLOT_1(Private, void maximumDateChanged(const QDate & date))
      CS_SLOT_2(maximumDateChanged)

      CS_SLOT_1(Private, void weekdayFormatChanged())
      CS_SLOT_2(weekdayFormatChanged)

      CS_SLOT_1(Private, void weekendFormatChanged())
      CS_SLOT_2(weekendFormatChanged)

      CS_SLOT_1(Private, void reformatHeaders())
      CS_SLOT_2(reformatHeaders)

      CS_SLOT_1(Private, void reformatCalendarPage())
      CS_SLOT_2(reformatCalendarPage)

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
      QCheckBox *gridCheckBox;
      QCheckBox *navigationCheckBox;
      QComboBox *horizontalHeaderCombo;
      QComboBox *verticalHeaderCombo;

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
