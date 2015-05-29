#include "Pessoa.h"
using namespace std;

Pessoa::Pessoa(string nome, int profundidade, int ID, vector<string> amigos){
	this->nome = nome;
	this->profundidade = profundidade;
	this->ID = ID;
	this->amigos = amigos;
}

string Pessoa::getNome() const {
	return nome;
}

void Pessoa::setNome(string nome) {
	this->nome = nome;
}

int Pessoa::getProfundidade() const {
	return profundidade;
}

void Pessoa::setProfundidade(int profundidade) {
	this->profundidade = profundidade;
}

int Pessoa::getId() const {
	return ID;
}

void Pessoa::setId(int id) {
	ID = id;
}

bool Pessoa::operator==(const Pessoa& p1){
    if(p1.getId() == ID)
    	return true;
    else return false;
 }

void loadPessoas(string filename,Graph<Pessoa*> &graph, list<Pessoa*> &pessoas){
	ifstream file;
	file.open(filename.c_str());
	string nome;
	int prof, id;

	while(!file.eof()){
		getline(file, nome);
		file >> prof;
		file >> id;
		file.ignore();
		vector<string> amigos;

		while(!file.eof() && (char) file.peek() != '\n'){
			string amigo;
			getline(file, amigo);
			amigos.push_back(amigo);
		}

		Pessoa * pessoa = new Pessoa(nome, prof, id, amigos);
		pessoas.push_back(pessoa);
		graph.addVertex(pessoa);

		while(!file.eof() && file.peek() == '\n')
			file.ignore();

	}
	file.close();

	list<Pessoa*>::iterator it = pessoas.begin();
		for(;it != pessoas.end(); it++){
			vector<string> amigos = (*it)->amigos;
			for(unsigned int i = 0; i < amigos.size(); i++){
				list<Pessoa*>::iterator adj = pessoas.begin();
				bool success = false;
				for(;adj != pessoas.end(); adj++){
					if( (*adj)->getNome() == amigos[i]){
						success = true;
						graph.addEdge(*it, *adj, 1);
						break;
					}
				}
				if ( ! success){
					cout << (*it)->getNome() << endl;
					cout << amigos[i] << endl;
					//usleep(pow(2,6));
					throw ExceptionPersontNotFound();
				}
			}
		}
}

