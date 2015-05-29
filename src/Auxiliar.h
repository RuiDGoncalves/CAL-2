#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<string> partString(string exp){

	vector<string> words;

	char * pch;
	const char tokens[3] = " -";
	printf ("Splitting string \"%s\" into tokens:\n",exp);
	char expC[exp.length() + 1];
	strcpy(expC, exp.c_str());
	pch = strtok(expC,tokens);
	while (pch != NULL)
	{
		words.push_back(pch);
		pch = strtok (NULL, " ,.-");
	}

	return words;
}
