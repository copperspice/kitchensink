/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
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

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QLabel>
#include <QWidget>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QGridLayout>
#include <QGroupBox>

class Calendar : public QWidget
{
   CS_OBJECT(Calendar)

   public:
      Calendar();

   private :
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
   
      void createCalendarGroupBox();
      void createGeneralOptionsGroupBox();
      void createDatesGroupBox();
      void createTextFormatsGroupBox();
      QComboBox *createColorComboBox();

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
