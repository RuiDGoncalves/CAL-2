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
public:
	searchDistance(float sPerc, int fDist){
		this->stringPercentage = sPerc;
		this->friendshipDistance = fDist;
	}

	float getStringPercentage(){
		return this->stringPercentage;
	}
	int getFriendshipDistance(){
		return this->friendshipDistance;
	}
	bool operator<(const searchDistance b)const{
		if (stringPercentage == b.stringPercentage)
			return friendshipDistance > b.friendshipDistance;
		return stringPercentage < b.stringPercentage;
	}
};

class orderPair{
public:
	bool operator()(pair<searchDistance,string> a, pair<searchDistance,string> b) const{
		return a.first < b.first;
	}

};

priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> getDistance(string target, Graph<Pessoa> redeAmizades){
	priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> resultadosOrdenados;

	vector<Vertex<Pessoa> *> targets = redeAmizades.getVertexSet();

	stringstream ss(target);
	vector<string> targetVec;
	while(!ss.eof()){
		string tempString;
		ss >> tempString;
		targetVec.push_back(tempString);
	}
	for(unsigned int i = 0; i < targetVec.size(); i++)
		cout << targetVec[i];
	cout << endl;
	for(unsigned int i = 0; i < targets.size(); i++){
		Vertex<Pessoa> * v = targets[i];
		int fDist = v->getDist();
		string name = v->getInfo().getNome();
		vector<string> nameVec;
		stringstream ss2(name);
		while(!ss2.eof()){
			string tempString;
			ss2 >> tempString;
			nameVec.push_back(tempString);
		}
		for(int i = 0; i < nameVec.size(); i++){
			cout << nameVec[i];
		}
		cout << endl;
		int matches = 0;
		for(unsigned int i = 0; i < targetVec.size(); i++)
			for(unsigned int j = 0; j < nameVec.size(); j++)
				if(editDistance(nameVec[j], targetVec[i]) == 0)
					matches++;



		float sDist = ((float)matches )/targetVec.size();
		searchDistance distance(sDist, fDist);
		pair<searchDistance, string> par(distance, name);
		resultadosOrdenados.push(par);

	}

	return resultadosOrdenados;
}

int main(){
	Graph<Pessoa> redeSocial;


	vector<Pessoa> pessoas;
	loadPessoas("Pessoas.txt", redeSocial, pessoas);
//	cout << "Tamanho pessoas - " << pessoas.size() << endl;
//	for(int i = 0; i < pessoas.size(); i++)
//		cout << pessoas[i].getNome() << endl;
//	cout << endl;

	loadAmizades("Amizades.txt", redeSocial, pessoas);

	vector<Vertex<Pessoa>*> vertexSet = redeSocial.getVertexSet();
//	for(int i = 0; i < vertexSet.size(); i++){
//		Vertex<Pessoa> * v = vertexSet[i];
//		cout << "User: " << v->getInfo().getNome() << endl;
//		cout << "Amigos\n";
//		for(int j = 0; j < v->getAdj().size(); j++){
//			Vertex<Pessoa>* amigo = v->getAdj()[j].getDest();
//			cout << amigo->getInfo().getNome() << endl;
//		}
//		cout << endl;
//	}
	redeSocial.unweightedShortestPath(pessoas[0]);
	priority_queue<pair<searchDistance,string>, vector<pair<searchDistance,string> >, orderPair> resultadosOrdenados =  getDistance("Sergio Silva", redeSocial);
	while(!resultadosOrdenados.empty()){
		pair<searchDistance, string> par = resultadosOrdenados.top();
		resultadosOrdenados.pop();
		cout << par.first.getStringPercentage() << " " << par.first.getFriendshipDistance() << " " << par.second << endl;
	}
	return 0;
}
