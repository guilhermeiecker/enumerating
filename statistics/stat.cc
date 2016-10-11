#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdint.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);  // number of nodes
    string input("../results/n" + to_string(n) + ".txt"); // set file name at execution time

    int m, f;     // number of links, number of feasible sets
    double a, t;  // area size, execution time

    double  number_of_samples[61];
    double  sum_average_f[61], sum_sd_f[61];
    double  sum_average_t[61], sum_sd_t[61];

    double  average_t[61];
    double  average_f[61];

    double  sd_t[61];
    double  sd_f[61];

    // calculates average
    ifstream f_average(input);
    while (f_average >> n >> m >> a >> t >> f)  // reads file line by line
    {
      number_of_samples[m - 4]++;
      sum_average_t[m - 4] += t;
      sum_average_f[m - 4] += f;
    }
    f_average.close();

    for(int i = 0; i < 61; i++)
    {
      average_t[i] = sum_average_t[i] / number_of_samples[i];
      average_f[i] = sum_average_f[i] / number_of_samples[i];
    }


    // calculates standard deviation
    ifstream f_sd(input);
    while (f_sd >> n >> m >> a >> t >> f)  // reads file line by line
    {
      number_of_samples[m - 4]++;
      sum_sd_t[m - 4] += pow((t - average_t[m - 4]),2);
      sum_sd_f[m - 4] += pow((f - average_f[m - 4]),2);
    }
    f_average.close();

    for(int i = 0; i < 61; i++)
    {
      sd_t[i] = sqrt(sum_sd_t[i] / (number_of_samples[i] - 1));
      sd_f[i] = sqrt(sum_sd_f[i] / (number_of_samples[i] - 1));
    }

    string output("n" + to_string(n) + ".txt"); // set file name at execution time
    ofstream result(output);
    result << "m\t#samples\taverageT\tsdT\taverageF\tsdF" << endl;
    for(int i  = 0; i < 61; i++)
      result << fixed << setprecision(6) << i + 4 << "\t" << number_of_samples[i] << "\t" << average_t[i] << "\t" << sd_t[i] << "\t" << average_f[i] << "\t" << sd_f[i] << endl;

    return 0;
}
