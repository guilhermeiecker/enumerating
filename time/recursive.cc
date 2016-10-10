#include <iomanip>                      // std::setprecision
#include <fstream>      // std::ifstream
#include <string>

#include "Network.h"
#include "Recursive.h"

#define TPOWER 300      // Transmission Power (Default: 300mW)
#define INCRMT 0.05     // Area side increment
#define NODES 4         // Max different number of node values
#define LINKS 61        // Number of links (from 4 to LINKS + 4)
#define RUNS 100        // Number of networks for every combination of n and m
#define AREA 30000      // Initial area side value

using namespace std;

int main(int argc, char** argv) {
	uint64_t n, m, r;
	clock_t t, tt;
	double s;
	double area[LINKS][RUNS];

	n = (uint64_t)atoi(argv[1]);
	m = (uint64_t)atoi(argv[2]);
	r = (uint64_t)atoi(argv[3]);

	string fname("../input/n" + to_string(n) + ".txt");
	ifstream f(fname);

	for (int i = 0; i < LINKS; i++)
		for (int j = 0; j < RUNS; j++)
			f >> area[i][j];
	f.close();

	s = area[m - 4][r];

	srand((int)100*s);
	Network* g = new Network(n, s, TPOWER);

	double time = 0.0;
	//uint64_t size = 0;

	Recursive* a = new Recursive(g);
	t = clock();
	a->find_fset(0);
	tt = clock();
	time = ((double)(tt - t))/CLOCKS_PER_SEC;
	//size = a->get_fset().size();
	cout << fixed << setprecision(6) << time << endl;
	//cout << fixed << setprecision(6) << size << endl;

  return 0;
}
