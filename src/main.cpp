#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>
#include <sstream>
#include <iterator>

#include "Pessoa.h"
#include "Graph.h"
#include "matcher.h"


using namespace std;


class searchDistance{
	float stringPercentage;
	int friendshipDistance;
	int matchPosition;
	vector<string> target;
	vector<string> name;
public:
	searchDistance(float sPerc, int fDist, int mPos, vector<string> target, vector<string> name){
		this->stringPercentage = sPerc;
		this->friendshipDistance = fDist;
		this->matchPosition = mPos;
		this->target = target;
		this->name = name;
	}

	static int getMinLevenshteinDistance(vector<string> &target, vector<string> &name){
		int minDistance = 9999999;
		for(unsigned int j = 0; j < target.size(); j++)
			for(unsigned int k = 0; k < name.size(); k++){
				int levenshteinDistance = editDistance(name[k], target[j]);
				if(levenshteinDistance < minDistance)
					minDistance = levenshteinDistance;
			}
		return minDistance;
	}

	float getStringPercentage(){
		return this->stringPercentage;
	}
	int getFriendshipDistance(){
		return this->friendshipDistance;
	}
	int getMatchPosition(){
		return this->matchPosition;
	}

	int getMinLevenshteinDistance(const vector<string> &target,const vector<string> &name) const{
		int minDistance = 9999999;
		for(unsigned int j = 0; j < target.size(); j++)
			for(unsigned int k = 0; k < name.size(); k++){
				int levenshteinDistance = editDistance(name[k], target[j]);
				if(levenshteinDistance < minDistance)
					minDistance = levenshteinDistance;
			}
		return minDistance;
	}

	bool operator<(const searchDistance b)const{
		if (stringPercentage == b.stringPercentage){
			if(matchPosition == b.matchPosition){
				int distance = getMinLevenshteinDistance(target, name);
				int bDistance = b.getMinLevenshteinDistance(b.target, b.name);
				if(distance == bDistance)
					return friendshipDistance > b.friendshipDistance;
				return distance > bDistance;
			}
			return matchPosition > b.matchPosition;
		}
		return stringPercentage < b.stringPercentage;
	}
};



class orderPair{
public:
	bool operator()(pair<searchDistance,string> a, pair<searchDistance,string> b) const{
		return a.first < b.first;
	}

};

vector<string> stringToVector(string &name){
	stringstream ss(name);
	vector<string> returnVec;
	while(!ss.eof()){
		string tempString;
		ss >> tempString;
		returnVec.push_back(tempString);
	}

	return returnVec;
}

priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> getDistance(string &target, Graph<Pessoa> &redeAmizades){
	priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> resultadosOrdenados;

	vector<Vertex<Pessoa> *> targets = redeAmizades.getVertexSet();

	vector<string> targetVec = stringToVector(target);
	for(unsigned int i = 1; i < targets.size(); i++){	//O ciclo começa a 1 para ignorar o utilizador, que é o elemento nº 0 do vector
		Vertex<Pessoa> * v = targets[i];
		string name = v->getInfo().getNome();
		vector<string> nameVec = stringToVector(name);

		int matches = 0;
		int mPos = 0;
		for(unsigned int j = 0; j < targetVec.size(); j++)
			for(unsigned int k = 0; k < nameVec.size(); k++)
				if(editDistance(nameVec[k], targetVec[j]) == 0){
					mPos = k;
					matches++;
				}

		float sDist = ((float)matches )/targetVec.size();
		int fDist = v->getDist();
		searchDistance distance(sDist, fDist, mPos, targetVec, nameVec);
		pair<searchDistance, string> par(distance, name);
		resultadosOrdenados.push(par);

	}

	return resultadosOrdenados;
}

void printResultados(priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> &resultadosOrdenados){
	int i = 0;
	while(!resultadosOrdenados.empty()){
		i++;
		pair<searchDistance, string> par = resultadosOrdenados.top();
		resultadosOrdenados.pop();
		//cout << par.first.getStringPercentage() << " " << par.first.getFriendshipDistance() << " " << par.second << endl;
		cout << i << "-" << par.second << endl;
	}
}

int main(){
	Graph<Pessoa> redeSocial;


	vector<Pessoa> pessoas;
	loadPessoas("Pessoas.txt", redeSocial, pessoas);

	loadAmizades("Amizades.txt", redeSocial, pessoas);

	vector<Vertex<Pessoa>*> vertexSet = redeSocial.getVertexSet();
	redeSocial.unweightedShortestPath(pessoas[0]);
	string inputSearch;
	priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> resultadosOrdenados;
	while(1){
		cout << "Procure por um utilizador. Se quiser sair insira 'exit'\nProcura: ";
		getline(cin, inputSearch);
		if(inputSearch == "exit")
			break;
		resultadosOrdenados =  getDistance(inputSearch, redeSocial);
		printResultados(resultadosOrdenados);
	}
	return 0;
}
