
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
  const int przedzial = 100;
  double x;
  int iterations = 1000000;
  double startingValue = 0;
  double endValue = 2 * M_PI;
  string nameOfOutput = "Average.txt";
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

  double blad[4][przedzial];
  for (int j = 0; j < przedzial; j++){
    for (int i = 0; i < 4; i++)
      blad[i][j] = 0.0;
    }
  int k = 0;
  int j = 0;
  int c = 0;
  for (x = startingValue; x < endValue; x += plu )
  {
    double FromMathh = sin(cos(x));

    blad[k][j] += BladBezwzgledny(Sin::SumTaylorFromBegin(Cos::SumTaylorFromBegin(x,N), N), FromMathh);   k++;
    blad[k][j] += BladBezwzgledny(Sin::SumTaylorFromEnd(Cos::SumTaylorFromEnd(x,N), N), FromMathh);     k++;
    blad[k][j] += BladBezwzgledny(Sin::SumBasedOnPreviouFromBegin(Cos::SumBasedOnPreviouFromBegin(x,N), N), FromMathh);   k++;
    blad[k][j] += BladBezwzgledny(Sin::SumBasedOnPreviouFromEnd(Cos::SumBasedOnPreviouFromEnd(x,N), N), FromMathh);   k++;
    k%=4;
    c++;
    if (c >= iterations/przedzial){
      j++;
      c = 0;
    }
  }
  ofstream outputError;
  outputError.open("Averages.csv");
  outputError << setprecision(std::numeric_limits<double>::digits10 + 1);
  cout.precision(20);
  double averages[4];
  for(int i = 0 ; i < 4; i++){
    for (int t = 0; t < przedzial; t++)
    {

          blad[i][t]/=(iterations/przedzial);
          averages[i]+=  blad[i][t];
          outputError << blad[i][t] << endl;
    }
    outputError << endl;
    averages[i]/= przedzial;
    cout << averages[i] << endl;
  }



  return 0;
}
