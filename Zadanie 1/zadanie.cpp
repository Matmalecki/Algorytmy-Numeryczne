
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include "Sin.h"
#include "Cos.h"
#include "string.h"

double BladBezwzgledny(double myOutput, double MathhOutput)
{
  return fabs(myOutput - MathhOutput);
}

using namespace std;

int main(int argc, char * argv[])
{

  int N = 50;
  double x;
  int iterations = 1000000;
  double startingValue = 0;
  double endValue = 2 * M_PI;
  string nameOfOutput = "AvgError.txt";
  if (argc > 1)
  {
    if (!strcmp(argv[1],"--help"))
    {
      cout << "N - liczba sumowanych skladnikow" << endl;
      cout << "Brak argumentow - ustawienia domyslne:" << endl;
      cout << "Argumenty od 0 do 2PI oraz N = 50" << endl;
      cout << "(Opcjonalnie) Pierwszy arg - liczba N" << endl;
      cout << "(Opcjonalnie) Drugi arg - \"smallArgs\" Argumenty od 0 do 2PI/10000" << endl;
      return 0;
    }else
    N = atoi(argv[1]);

    if (argc > 2)
    {
      if (!strcmp(argv[2],"smallArgs"))
      {
        endValue = (2 * M_PI)/10000;
        nameOfOutput = "AvgErrorForSmallArgs.txt";
      }
    }
  }
  double plu = (endValue-startingValue)/iterations;

  Sin sinus;
  Cos cosin;
  double blad[4];
  for (int i = 0; i < 4; i++)
    blad[i] = 0.0;
  int k = 0;
  cout.precision(20);
  for (x = startingValue; x < endValue; x += plu )
  {
    double FromMathh = sin(cos(x));
    blad[k] += BladBezwzgledny(Sin::SumTaylorFromBegin(Cos::SumTaylorFromBegin(x,N), N), FromMathh);   k++;
    blad[k] += BladBezwzgledny(Sin::SumTaylorFromEnd(Cos::SumTaylorFromEnd(x,N), N), FromMathh);     k++;
    blad[k] += BladBezwzgledny(Sin::SumBasedOnPreviouFromBegin(Cos::SumBasedOnPreviouFromBegin(x,N), N), FromMathh);   k++;
    blad[k] += BladBezwzgledny(Sin::SumBasedOnPreviouFromEnd(Cos::SumBasedOnPreviouFromEnd(x,N), N), FromMathh);   k++;
    k%=4;
  }
  ofstream outputError;
  outputError.open(nameOfOutput.c_str());
  outputError << setprecision(std::numeric_limits<double>::digits10 + 1);

  cout.precision(20);
  for(int i = 0 ; i < 4; i++){
        blad[i]/=iterations;
        cout  << blad[i] << endl;
        outputError << blad[i] << endl;
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
