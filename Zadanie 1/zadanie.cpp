
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <math.h>
#include "Sin.h"
#include "Cos.h"


double BladBezwzgledny(double myOutput, double MathhOutput)
{
  return fabs(myOutput - MathhOutput);
}



using namespace std;

int main()
{
  int N = 100;
  double x;
  int iterations = 1000000;
  Sin sinus;
  Cos cosin;
  ofstream oFile;
  oFile.open("wyniki.txt");
  if (oFile.is_open())
  {
    double plu = 2*M_PI/iterations;
    oFile << setprecision(std::numeric_limits<double>::digits10 + 1);
    for (x = 0; x < 2 * M_PI; x += plu )
    {
      double FromMathh = sin(cos(x));
      oFile << BladBezwzgledny(sinus.SumTaylorFromBegin(cosin.SumTaylorFromBegin(x,N), N), FromMathh) << endl;
      oFile << BladBezwzgledny(sinus.SumTaylorFromEnd(cosin.SumTaylorFromBegin(x,N), N), FromMathh) << endl;
      oFile << BladBezwzgledny(sinus.SumBasedOnPreviouFromBegin(cosin.SumBasedOnPreviouFromBegin(x,N),N), FromMathh) << endl;
      oFile << BladBezwzgledny(sinus.SumBasedOnPreviouFromEnd(cosin.SumBasedOnPreviouFromEnd(x,N),N), FromMathh) << endl;

    }
  }
  oFile.close();
  ifstream iFile;
  iFile.open("wyniki.txt");
  double blad[4];
  for(int i = 0 ; i < 4; i++)
    blad[i] = 0.0;
  if (iFile.is_open())
  {
    double pom;
      for (int i = 0; i < iterations; i++)
      {
          iFile >> pom;
          blad[i%4]+=pom;
      }
      cout.precision(std::numeric_limits<double>::digits10 + 1);
      for(int i = 0 ; i < 4; i++){
        blad[i]/=iterations;
        cout << blad[i] << endl;
      }
  }




  /*
  std::cout << "Wynik z biblioteki math.h " << sin(cos(x)) << std::endl;
  std::cout << "Wynik bezsposrednio ze wzoru Taylora w kolejnosci od poczatku " << sinus.SumTaylorFromBegin(cosin.SumTaylorFromBegin(x,N), N) << std::endl;
  std::cout << "Wynik bezsposrednio ze wzoru Taylora w kolejnosci od konca "<< sinus.SumTaylorFromEnd(cosin.SumTaylorFromEnd(x,N), N) << std::endl;
  std::cout << "Wynik sumujac elementy szeregu obliczajac kolejny na podstawie poprzedniego od poczatku "
            << sinus.SumBasedOnPreviouFromBegin(cosin.SumBasedOnPreviouFromBegin(x,N),N)
            << std::endl;
  std::cout << "Wynik sumujac elementy szeregu obliczajac kolejny na podstawie poprzedniego od konca  "
            << sinus.SumBasedOnPreviouFromEnd(cosin.SumBasedOnPreviouFromEnd(x,N),N) << std::endl;
            */
  return 0;
}
