#ifndef REDE_H_
#define REDE_H_

#include<vector>

using namespace std;
#include "PostoServico.h"
#include "Utilizador.h"


class Rede
{
public:
	vector <Empresa> Empresas;
	vector<PostoServico*> PostoServico;
	vector<Utilizador*> Utilizadores;
}


#endif /* REDE_H_ */
