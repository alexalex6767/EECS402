#include <iostream>
using namespace std;

//Programmer: Tzu-Yu Peng, uniqname: typeng
//Date: September 2023
//Purpose: Make a program that can accure interest from investment

//global constant that will not be changed
//the first three are the interest rate depends on balanceAmt
//Others are the threshold to determine the intRate
const double MIN_INT_RATE = 0.0015;
const double MAX_INT_RATE = 0.004;
const double STD_INT_RATE = 0.00225;
const double CUSTO_BALANCE_1000 = 1000;
const double CUSTO_BALANCE_15000 = 15000;

//Prototype
//This is the prototype of the function for accruing total interest
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
);

//This is the prototype of the function for accruing one month interest
bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
);


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  //initialization and declaration
  double balanceAmt = 0;
  int numMonths = 0;
  char printOrNot;
  bool trueOrFalseForPrint;
  const char Y_FOR_PRINT = 'y';

  
  //Customers enters their balance
  cout << "Enter the initial balance of the account: ";
  cin >> balanceAmt;

  //Customer enters their number of months
  cout << "Enter the number of months to accrue interest: ";
  cin >> numMonths;

  //Customer decides whether they want each month's detail
  cout << "Show month-by-month results - 'y' for yes, any other for no:";
  cin >> printOrNot;

  double initBalance = balanceAmt;//Save initial balance this to print
  
  if (printOrNot == Y_FOR_PRINT)
  {
    trueOrFalseForPrint = true;
  }
  else
  {
    trueOrFalseForPrint = false;
  }

  if (accrueInterest(balanceAmt, numMonths, trueOrFalseForPrint))
  {
    //print out all the required output
    cout << "Interest accrued for " <<  numMonths << " months!"  << endl;
    cout << endl;

    cout << "Initial balance: " << initBalance << endl;
    cout << "Total interest accrued: " << balanceAmt - initBalance << endl;
    cout << "Final balance: " << balanceAmt << endl;
  }
  
  //if the inputs do not meet the requests
  else if (balanceAmt < 0)
  {
    cout << "ERROR in accrueOneMonthsInterest: balanceAmt must be >= 0," <<
            " but the value " << balanceAmt << " was provided!" << endl;
    cout << "Sorry, an error was detected. Unable to provide results!"
         << endl;
  }

  else if(numMonths <= 0)
  {
    cout << "ERROR in accrueInterest: numMonths must be > 0, but the value "
         << numMonths << " was provided!" << endl;
    cout << "Sorry, an error was detected. Unable to provide results!"
         << endl;
  }
  return 0;
};
#endif


//Function for accrue interest for months
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
)
{
  if (balanceAmt < 0 || numMonths <= 0)
  {
    return false;
  }
  
  //Print or not print monthly accured interest
  if(doPrintEachMonth)
  {
    for(int i = 0; i < numMonths; i++)
    {
      accrueOneMonthsInterest(balanceAmt, doPrintEachMonth);
    }
   }
 
  if(!doPrintEachMonth)
  {
    for(int i = 0; i < numMonths; i++)
    {
      accrueOneMonthsInterest(balanceAmt, doPrintEachMonth);
    }
  }
  
  return true;
};


bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
)
{
  //Initialization and declaration
  double intRate = 0;
  double intAccrued;

 
  
  //Check whether the program runs as expected or not
  if(balanceAmt < 0)
  {
    return false;
  }

  
  //Select interest rate
  if(balanceAmt < CUSTO_BALANCE_1000)
  {
    intRate = MIN_INT_RATE;
  }

  else if((balanceAmt >= CUSTO_BALANCE_1000) &
          (balanceAmt < CUSTO_BALANCE_15000))
  {
    intRate = STD_INT_RATE;
  }

  else if(balanceAmt >= CUSTO_BALANCE_15000)
  {
    intRate = MAX_INT_RATE;
  }

  
  //Print or not print interest info
  if(doPrintInfo)
  {
    cout << "Accruing interest for 1 month: " << endl;
    cout << "  Initial balance: " << balanceAmt << endl;
    cout << "  Initial rate: " << intRate  << endl;

    intAccrued = balanceAmt * intRate;
    cout << "  Interest accrued:  " << intAccrued << endl;
      
    balanceAmt += intAccrued;
    cout << "  New balance: " << balanceAmt << endl;
  }

  if(!doPrintInfo)
  {
    intAccrued = balanceAmt * intRate;
    balanceAmt += intAccrued;
  }

  return true;
};

