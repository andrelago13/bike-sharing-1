#ifndef TOOLS_H_
#define TOOLS_H_

#include <string>
#include <vector>

using namespace std;

int str_to_int(string &str);

void get_option(int &option, int min_range, int max_range);

void clear_screen();

template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x);

template <class Comparable>
void insertionSort(vector<Comparable> &v);

string readPassword();


#endif /* TOOLS_H_ */