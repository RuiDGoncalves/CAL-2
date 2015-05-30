#include "Pessoa.h"
using namespace std;

Pessoa::Pessoa(int ID, string nome){
	this->ID = ID;
	this->nome = nome;
}

string Pessoa::getNome() const {
	return nome;
}

void Pessoa::setNome(string nome) {
	this->nome = nome;
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

void loadPessoas(string filename,Graph<Pessoa> &graph, vector<Pessoa> &pessoas){
	ifstream file;
	file.open(filename.c_str());
	int id;
	string nome, lixo;

	while(!file.eof()){
		file >> id;
		file.ignore();
		getline(file, nome);

		while(!file.eof() && (char) file.peek() == '\n'){
			getline(file, lixo);
		}
		Pessoa pessoa = Pessoa(id, nome);
		graph.addVertex(pessoa);
		pessoas.push_back(pessoa);

	}
	file.close();
}

void loadAmizades(string filename,Graph<Pessoa> &graph, vector<Pessoa> &pessoas){
	ifstream file;
	file.open(filename.c_str());
	int id, id_amigo;
	string lixo;

	while(!file.eof()){
		file >> id;
		file.ignore();
		if(id > pessoas.size()){
//			cout << "ID - " << id << endl;
//			return;
			throw ExceptionPersontNotFound();
		}

		while(!file.eof() && (char) file.peek() != '\n'){
			file >> id_amigo;
			file.ignore();
			if(id_amigo > pessoas.size()){
				throw ExceptionPersontNotFound();
//				cout << "ID " << id << ", IDamigo - " << id_amigo << endl;
//				return;
			}
			graph.addEdge(pessoas[id], pessoas[id_amigo], 1);
		}

		while(!file.eof() && file.peek() == '\n')
			file.ignore();

	}

file.close();

}


