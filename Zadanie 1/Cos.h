#include "Func.h"

class Cos {
public:
  static double SumTaylorFromBegin(double x, int n)
  {
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
      result+= (power(-1,i) * power(x, 2*i))/fact(2*i);
    }
    return result;
  }
  static double SumTaylorFromEnd(double x, int n)
  {
    double result = 0.0;
    double tab[n];
    for (int i = 0; i < n; i++)
    {
      tab[i] = (power(-1,i) * power(x, 2*i))/fact(2*i);
    }
    for (int i = n-1; i >= 0; i--)
    {
      result+=tab[i];
    }
    return result;
  }

  static double SumBasedOnPreviouFromBegin(double x, int n)
  {
    double result = 1.0;
    double tab[n];
    tab[0] = 1;
    for (int i = 1; i < n; i++)
    {
      tab[i] = (tab[i-1]*(-1)*(power(x,2)))/((2*i)*(2*i-1));
      result+= tab[i];
    }

    return result;
  }
  static double SumBasedOnPreviouFromEnd(double x, int n)
  {
    double tab[n];
    tab[0] = 1;
    for (int i = 1; i < n; i++)
    {
      tab[i] =  (tab[i-1]*(-1)*(power(x,2)))/((2*i)*(2*i-1));
    }
    double result = 0.0;
    for (int i = n-1; i >= 0; i--)
    {
      result += tab[i];
    }
    return result;
  }



};
