/*
** Enumerator class implementing an algorithm that enumerates all feasible sets of links
** Author: Guilherme Iecker Ricardo
** Institute: Systems Engineering and Computer Science Program - COPPE/UFRJ
*/

#pragma once

#include <iostream>	// cout, endl
#include <stdint.h>	// uint64_t
#include <math.h>	// pow, log
#include <vector>	// vector
#include <fstream>	// ifstream

#include "Node.h"
#include "Link.h"
#include "Network.h"
#include "bigInt.h"

typedef unsigned __int128 uint128_t;

using namespace std;

class Enumerator
{
private:
	uint64_t n, m, f;
	vector<Link*> cset;
	Network* network;
	ofstream* outfile;

	void add_link(uint64_t);
	double calculate_interference(Node*, Node*);
	bool is_feasible();
	bool primary_test();
	bool secondary_test();
	double calculate_sinr(Link*);
	void del_link(uint64_t);

public:
	Enumerator(Network*, ofstream*);
	void find_fset_entry(BigInt);
	void find_fset(BigInt);
	uint64_t get_fset();
};

void Enumerator::find_fset_entry(BigInt x)
{
	uint64_t limit = m;
	for (uint64_t i = 0; i < limit; i++)
		find_fset(x + BigInt::pow2(i));
}

void Enumerator::find_fset(BigInt x)
{
	uint64_t limit = BigInt::log2(x);
	add_link(limit);
	if (is_feasible()) {
		uint128_t msb = x.get_msb();
		uint128_t lsb = x.get_lsb();
		outfile->write((char*)&msb, sizeof(uint128_t));
		outfile->write((char*)&lsb, sizeof(uint128_t));
		f++;
		for (uint64_t i = 0; i < limit; i++)
			find_fset(x + BigInt::pow2(i));
	}
	del_link(limit);
}

void Enumerator::add_link(uint64_t index)
{
	if (!cset.empty()) {
		double interfAB, interfBA;
		for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		{
			interfAB = calculate_interference((*i)->get_sender(), network->get_link(index)->get_recver());
			interfBA = calculate_interference(network->get_link(index)->get_sender(), (*i)->get_recver());

			network->get_link(index)->add_interf(interfAB);
			(*i)->add_interf(interfBA);
		}
	}
	network->get_link(index)->get_sender()->inc_degree();
	network->get_link(index)->get_recver()->inc_degree();
	cset.push_back(network->get_link(index));
}

double Enumerator::calculate_interference(Node* a, Node* b)
{
	double dist = a->distance(*b);
	if (dist > network->d0)
		return pow(10.0, ((network->tpower_dBm - network->l0_dB - 10 * network->alpha*log10(dist / network->d0)) / 10.0));
	else
    		return pow(10.0, network->tpower_dBm - network->l0_dB / 10.0);
}

bool Enumerator::is_feasible()
{
	if(cset.size() < 2)
		return true;
	if(cset.size() > n/2)
		return false;
	if(primary_test()&&secondary_test())
		return true;
	return false;
}

bool Enumerator::primary_test()
{
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		if(((*i)->get_sender()->get_degree() > 1)||((*i)->get_recver()->get_degree() > 1))
    			return false;
	}
	return true;
}

bool Enumerator::secondary_test()
{
	double sinr;
	for(vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
	{
		sinr = calculate_sinr(*i);
		if(sinr < network->beta_mW)
			return false;
	}
	return true;
}

double Enumerator::calculate_sinr(Link* l)
{
    return l->get_rpower() / (network->noise_mW + l->clc_interf());
}

void Enumerator::del_link(uint64_t index)
{
	cset.pop_back();
	network->get_link(index)->get_sender()->dec_degree();
	network->get_link(index)->get_recver()->dec_degree();
	network->get_link(index)->clr_interf();
	for (vector<Link*>::iterator i = cset.begin(); i != cset.end(); ++i)
		    (*i)->del_interf();
}

Enumerator::Enumerator(Network* g, ofstream* file):
	n(g->get_nodes().size()), m(g->get_links().size()), network(g), outfile(file)
{
	f = 0;
}

uint64_t Enumerator::get_fset()
{
	return f;
}
