#include <iostream>
#include <fstream>
#include <cmath>

#include "Ranking.h"
#include "Leitor.h"


Ranking::Ranking(){
    qtdd_palavras = 0;
    qtdd_documentos = 0;
}


Ranking::Ranking(Texto d1):Ranking(){
    qtdd_documentos++;
    Arquivos.push_back(d1);
    Texto aux = d1;
    std::list<std::string> indice_palavra;
    indice_palavra.push_back(d1.arquivo_fonte());
    for(int i = 0; i < d1.palavras_total(); i++){
        if( !presente (aux.ultima_palavra())){
            vocabulario.insert(make_pair(aux.ultima_palavra(), indice_palavra));
            qtdd_palavras++;
            vetor_vocabulario.push_front(aux.ultima_palavra());
        }
        aux.retira_ultima();
    }
}


Ranking::Ranking(std::string arquivo):Ranking(){
    std::fstream entrada;
    entrada.open(arquivo);
    std::string texto;
    
    while(entrada >> texto){
        Texto d(texto);
        acrescentar(d);
    }
    entrada.close();
}


bool Ranking::presente(std::string texto) const{
    if(vocabulario.count(texto)>0)
        return true;
    else
        return false;
}


int Ranking::tamanho_indice(){
    return qtdd_palavras;
}


void Ranking::acrescentar(Texto const d2){
    Ranking aux(d2);
    qtdd_documentos ++;
    Arquivos.push_back(d2);
    std::list<std::string> vetor_palavras;
    vetor_palavras.push_back(d2.arquivo_fonte());
    int tamanho = aux.tamanho_indice();
    for(int i=0; i<tamanho; i++){
        if(presente(aux.ultima_chave())){
            vocabulario[aux.ultima_chave()].push_back(d2.arquivo_fonte());
        }else {
            vocabulario.insert(make_pair(aux.ultima_chave(),vetor_palavras));
            qtdd_palavras++;
            vetor_vocabulario.push_front(aux.ultima_chave());
        }
        aux.remove_ultimo();
    }
}


int Ranking::arquivo_documentos(){
    return qtdd_documentos;
}


void Ranking::remove_ultimo(){
    qtdd_palavras = qtdd_palavras-1;
    vocabulario.erase(vetor_vocabulario.back());
    vetor_vocabulario.pop_back();
}


std::string Ranking::ultima_chave(){
    return vetor_vocabulario.back();
}

//estas variaves e formulas são nomeadas de acordo com o arquivo pdf do trabalho

double Ranking::importancia(std::string texto){
    double N = arquivo_documentos(), nx = arquivos_palavra(texto);
    if(nx == 0)
        return 0;
    return std::log(N/nx);
}


double Ranking::coordenada(Texto d,std::string texto){
    int tf = d.presente(texto);
    double imp = importancia(texto);
    return tf*imp;
}


double Ranking::similaridade_cosseno(Texto D,Texto q){
    double soma_numerador = 0, somatorio1_denom= 0, somatorio2_denom = 0, sim_dq = 0;
    Texto aux = q;
    for(int i = 0; i < q.palavras_total(); i++){
        soma_numerador = soma_numerador + coordenada(D, aux.ultima_palavra()) * coordenada(q, aux.ultima_palavra());
        somatorio1_denom = somatorio1_denom + pow(coordenada(D, aux.ultima_palavra()), 2);
        somatorio2_denom = somatorio2_denom + pow(coordenada(q, aux.ultima_palavra()), 2);
        aux.ultima_palavra();
    }
    sim_dq = soma_numerador/(sqrt(somatorio1_denom)*sqrt(somatorio2_denom));
    return sim_dq;
}


std::list<double> Ranking::similaridade_documentos(Texto q){
    std::list<double> sim_total;
    std::list<Texto> aux = Arquivos;
    for(int i = 0; i < Arquivos.size(); i++){
        Texto d = aux.front();
        sim_total.push_back(similaridade_cosseno(d,q));
        aux.pop_front();
    }
    return sim_total;
}

