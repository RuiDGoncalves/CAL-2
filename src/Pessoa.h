#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <iostream>
#include "Graph.h"
using namespace std;

class ExceptionPersontNotFound{};


class Pessoa{
private:
	string nome;
	int profundidade; //numero de arestas ate ao vertice
	int ID;
public:
	vector<string> amigos;
	Pessoa(string nome, int profundidade, int ID, vector<string> amigos);
	string getNome() const;
	void setNome(string nome);
	int getProfundidade() const;
	void setProfundidade(int profundidade);
	int getId() const;
	void setId(int id);
	bool operator==(const Pessoa& r1);
};

void loadPessoas(string filename,Graph<Pessoa*> &graph, list <Pessoa*>);

