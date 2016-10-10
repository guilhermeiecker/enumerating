#include <iostream>
#include <iomanip>

#include "Network.h"
#include "Recursive.h"

#define TPOWER 300

using namespace std;

int main(int argc, char** argv)
{
  uint64_t n, m;
  double a;

  n = atoi(argv[1]);
  a = (double)atof(argv[2]);

  srand((int)(a*100));

  Network* network = new Network(n, a, TPOWER);
  m = network->get_links().size();

  if((m>3)&&(m<65))
  {
      clock_t t, tt;
      uint64_t  size;
      double    time;
      Recursive* recursive = new Recursive(network);

      t = clock();
      recursive->find_fset(0);
      tt = clock();

      time = ((double)(tt - t))/CLOCKS_PER_SEC;
      size = recursive->get_fset().size();

      cout << fixed << setprecision(6) << n << "\t" << m << "\t" << a << "\t" << time << "\t" << size << endl;
  }

  return 0;
}
