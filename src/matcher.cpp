/*
 * matcher.cpp
 *
 *  Created on: 15/05/2015
 *      Author: duarte
 */

#include "matcher.h"

using namespace std;

int *compute_prefix_function(string pattern){
	int m = pattern.size();
	int* pi = new int[m];
	pi[0] = 0;

	int k = 0;
	for(int q = 1; q < m-1; q++){
		while(k > 0 && pattern[k] != pattern[q])
			k = pi[k-1];
		if(pattern[k] == pattern[q])
			k++;
		pi[q] = k;
	}

	return pi;
}

int kmp(string target, string pattern){
	int n = target.size();
	int m = pattern.size();

	int* pi = compute_prefix_function(pattern);
//	for (int i = 0; i < m; i++)
//		cout << pi[i] << ' ';
//	cout << endl;

	int q = 0;

	for(int i = 0; i < n-1; i++){
		while(q > 0 && pattern[q+1] != target[i])
			q = pi[q];
		if(pattern[q+1] == target[i])
			q++;
		if(q == m-1){
			free(pi);
			cout << "Pattern occurs with shift " << i - m;
			return i - m;
		}
	}

	free(pi);
	return -1;
}



int numStringMatching(string filename, string toSearch){
	ifstream file;
	file.open(filename.c_str());

	int m = toSearch.size();

	int q = 0;

	string line;
	//int k = 0;
	while(!file.eof()){
		getline(file, line);
		int i = 0;
		//cout << "linha " << k << endl;
		do{
			i = kmp(line, toSearch);
			//cout << i << endl;
			if(i >= 0){
				line.erase(line.begin() + i, line.begin()+i+m);
				q++;
			}
		}while(i >= 0);
		//cout << endl;
	}
	return q;
}

int editDistance(string pattern, string target){
	int d[target.size()+1];
	for(unsigned int i = 0; i <= target.size(); i++)
		d[i] = i;
	for(unsigned int i = 1; i <= pattern.size(); i++){
		int old = d[0];
		d[0] = i;
		int newValue;
		for(unsigned int j = 1; j <= target.size(); j++){
			if(pattern[i-1] == target[j-1])
				newValue = old;
			else
				newValue = 1 + min(old, min(d[j],d[j-1]));
			old = d[j];
			d[j] = newValue;
		}
	}
	return d[target.size()];

//	const size_t len1 = pattern.size(), len2 = target.size();
//	vector<int> col(len2+1), prevCol(len2+1);
//
//	for (unsigned int i = 0; i < prevCol.size(); i++)
//		prevCol[i] = i;
//	for (unsigned int i = 0; i < len1; i++) {
//		col[0] = i+1;
//		for (unsigned int j = 0; j < len2; j++)
//						// note that std::min({arg1, arg2, arg3}) works only in C++11,
//						// for C++98 use std::min(std::min(arg1, arg2), arg3)
//			col[j+1] = min(min( prevCol[1 + j] + 1, col[j] + 1), prevCol[j] + (pattern[i]==target[j] ? 0 : 1) );
//		col.swap(prevCol);
//	}
//	return prevCol[len2];
}

float numApproximateStringMatching(string filename, string toSearch){
	ifstream file;
	file.open(filename.c_str());
	string target;
	int distance = 0;
	int i = 0;
	while(!file.eof()){
		file >> target;
		if(target == "\n" || target == " ")
			continue;
		i++;
		distance += editDistance(toSearch, target);
		cout << target << " = " << distance << endl;
	}
	return ((float) distance) / i;
}
