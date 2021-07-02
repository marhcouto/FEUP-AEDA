#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli){}
unsigned int ParqueEstacionamento::getNumLugares() const {return lotacao;}
unsigned int ParqueEstacionamento::getNumMaximoClientes() const {return numMaximoClientes;}




