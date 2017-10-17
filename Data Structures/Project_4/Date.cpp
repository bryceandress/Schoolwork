/// File: Date.cpp
/// Member function implementations for Date class
#include <iostream>
#include "Date.h"

using namespace std;

//// Initialize static member at file scope; 
//// one class-wide copy.
const int Date::days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

//// Date constructor
Date::Date( int m, int d, int y ) 
{ setDate( m, d, y );}

/// Copy Constructor
Date::Date(const Date &d)
{setDate(d.month,d.day,d.year);}

/// Sets
/// Set month. If value is out of range, set to default of 1   
void Date::setMonth(int mm)
{  month = (mm >= 1 && mm <= 12) ? mm : 1;
}

/// Set day. If value is out of range, set to default of 1   
void Date::setDay(int dd)
{  /// Test for a leap year to determine #days in Feb.
   if (month == 2 && leapYear())  /// Feb in a leap year
      day = (dd >= 1 && dd <= 29) ? dd : 1;
   else
      day = (dd >= 1 && dd <= days[month]) ? dd : 1;
}

/// Set year. If value is out of range, set to default of 2005
void Date::setYear(int yy)
{year = yy;}

bool Date::operator>(Date date)
{
  if (getYear() <= date.getYear())
    return true;
  else if (getMonth() <= date.getMonth())
    return true;
  else if (getDay() <= date.getDay())
    return true;
  else
    return false;
}
/// Return month
int Date::getMonth()
{  return(month); 
}

/// Return day
int Date::getDay()
{  return(day);
}

/// Return year
int Date::getYear()
{  return(year);
}

/// Set the date
void Date::setDate(int mm, int dd, int yy )
{  setMonth(mm);
   setDay(dd);
   setYear(yy);
}

/// Place date members into parameters
void Date::getDate(int &m,int &d,int &y)
{  m=getMonth();
   d=getDay();
   y=getYear();
}

/// Preincrement operator overloaded as a member function.
Date &Date::operator++()
{
   helpIncrement();
   return *this;  /// reference return to create an lvalue
}

/// Postincrement operator overloaded as a member function.
/// Note that the dummy integer parameter does not have a
/// parameter name.
Date Date::operator++( int )
{
   Date temp = *this;
   helpIncrement();

   /// return non-incremented, saved, temporary object
   return temp;   /// value return; not a reference return
}

/// Add a specific number of days to a date
const Date &Date::operator+=( int additionalDays )
{
   for ( int i = 0; i < additionalDays; i++ )
      helpIncrement();

   return *this;    /// enables cascading
}

/// If the year in the data is a leap year, return true; 
/// otherwise, return false
bool Date::leapYear()
{
   if ( year % 400 == 0 || ( year % 100 != 0 && year % 4 == 0 ) )
      return true;   /// a leap year
   else
      return false;  /// not a leap year
}

/// If the year is a leap year, return true; 
/// otherwise, return false
bool leapYear(int y)
{
   if ( y % 400 == 0 || ( y % 100 != 0 && y % 4 == 0 ) )
      return true;   /// a leap year
   else
      return false;  /// not a leap year
}

/// Determine if the day is the end of the month
bool Date::endOfMonth()
{
   if ( month == 2 && leapYear() )
      return day == 29; /// last day of Feb. in leap year
   else
      return day == days[ month ];
}

/// Function to help increment the date
void Date::helpIncrement()
{
   if ( endOfMonth() && month == 12 ) {  /// end year
      day = 1;
      month = 1;
      ++year;
   }
   else if ( endOfMonth() ) {            /// end month
      day = 1;
      ++month;
   }
   else       /// not end of month or year; increment day
      ++day;
}

/// Overloaded output operator
ostream &operator<<( ostream &output, const Date &d )
{
   static char *monthName[ 13 ] = { "", "January",
      "February", "March", "April", "May", "June",
      "July", "August", "September", "October",
      "November", "December" };

   output << monthName[ d.month ] << ' '
          << d.day << ", " << d.year;

   return output;   /// enables cascading
}

