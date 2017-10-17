/// File: Date.h
/// Definition of class Date 
#ifndef DATE_H
#define DATE_H
#include <iostream>

using namespace std;

class Date {

public:

   /// constructor
   Date( int m = 1, int d = 1, int y = 1900 ); 
   /// copy constructor
   Date(const Date &);

   /// Sets
   void setMonth(int mm);
   void setDay(int dd);
   void setYear(int yy);

   /// Gets
   int getMonth();
   int getDay();
   int getYear();

   void setDate( int, int, int ); /// set the date
   void getDate(int &m,int &d,int &y);	/// get the entire date
   Date &operator++();            /// preincrement operator
   Date operator++( int );        /// postincrement operator
   const Date &operator+=( int ); /// add days, modify object
   bool operator>(Date);
   bool leapYear();          	  /// is this a leap year?

private:
   int month;
   int day;
   int year;

   static const int days[];       /// array of days per month
   bool endOfMonth();	          /// is this end of month?
   void helpIncrement();          /// utility function

   /// OK to declare here. A friend is NOT a member of the class
   friend ostream &operator<<( ostream &, const Date & );
};

   bool leapYear(int);          /// is this a leap year?

#endif
