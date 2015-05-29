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
	int ID;
public:
	Pessoa(int ID, string nome);
	string getNome() const;
	void setNome(string nome);
	int getId() const;
	void setId(int id);
	bool operator==(const Pessoa& p1);
};

void loadPessoas(string filename, Graph<Pessoa*> &graph);
void loadAmizades(string filename, Graph<Pessoa*> &graph);
