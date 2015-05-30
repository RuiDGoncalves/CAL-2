/*
 * matcher.h
 *
 *  Created on: 15/05/2015
 *      Author: duarte
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int *compute_prefix_function(string pattern);
int kmp(string target, string pattern);
int editDistance(string pattern, string target);
int numStringMatching(string filename, string toSearch);
float numApproximateStringMatching(string filename, string toSearch);

#endif /* MATCHER_H_ */
