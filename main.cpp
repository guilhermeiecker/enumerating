/*
** Entry point of the feasible sets enumeration system
** Author: Guilherme Iecker Ricardo
** Institute: Systems Engineering and Computer Science Program - COPPE/UFRJ
*/


#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "Enumerator.h"

#define NETWORKS_PATH "networks/"

using namespace std;

int main(int argc, char** argv)
{
	// Handler for wrong arguments set
	if(argc != 4)
	{
		cout << "Missing arguments!" << endl;
		cout << "USAGE: ./main <number of nodes> <area side> <round>" << endl;
	
		return 0;
	}

	clock_t t, tt;
	
	t = clock();

	// Reads basic model parameters from arguments
	uint64_t n = atoi(argv[1]);
        double area = (double)atof(argv[2]);
        uint64_t run = atoi(argv[3]);
        double tpower = 300.0;
	
	srand(run);
	uint64_t m, f;
	m = f = 0;
	
	// Builds network and checks the number of links
	Network* network;
        network = new Network(n, area, tpower);
        m = network->get_links().size();

	if(m == 0)
        {
                cout << n << "\t" << area << "\t" << run << "\t" << m << "\t0" << endl;
                return 0;
        }
        if(m > 128)
        {
                cout << n << "\t" << area << "\t" << run << "\t" << m << "\t0" << endl;
                return 0;
        }
	
	// Opens binary file to write feasible sets
	// Sets the first 128 bits of the binary file to 0s in order to receive the value of m and f after enumeration process
	string name;
	name = NETWORKS_PATH + to_string(n) + "-" + to_string((int)area) + "-" + to_string(run) + ".dat";
	ofstream outfile;
	outfile.open(name, ios::binary | ios::out);
	outfile.write((char*)&f, sizeof(uint128_t));

	// Feasible sets enumeration
	Enumerator* enumerator;
	enumerator = new Enumerator(network, &outfile);
        enumerator->find_fset(0);
        f = enumerator->get_fset();

	// Returns to the begining of the file and replace the 0s with the actual value of m and f
	// Closes the file
	outfile.seekp(ios_base::beg);
	outfile.write((char*)&m, sizeof(uint64_t));
	outfile.write((char*)&f, sizeof(uint64_t));

	outfile.close();

	tt = clock();

	// Prints the results to the screen
        cout << n << "\t" << area << "\t" << run << "\t" << m << "\t" << f << "\t" << fixed << setprecision(6) << ((double)(tt - t))/CLOCKS_PER_SEC << endl;
	
	return 0;
}
