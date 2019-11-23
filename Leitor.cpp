#include <iostream>
#include <fstream>
#include <locale>

#include "Leitor.h"

using std::string;

Texto::Texto(){
    palavras = 0;
}

Texto::Texto(std::string txt):Texto(){
    std::fstream entrada;
    entrada.open(txt);
    std::string trecho_normalizado;
    while(entrada >> trecho_normalizado){
        trecho_normalizado = NormalizaTexto(trecho_normalizado);
        if(trecho_normalizado != ""){
            texto_completo.push_back(trecho_normalizado);
            palavras++;
        }
    }
    arquivo = txt;
    entrada.close();
}


std::string NormalizaTexto(std::string trecho_normal){
    std::locale localizar;
    
    for (std::string::size_type i=0; i<trecho_normal.length(); ++i)
        trecho_normal[i] = std::tolower(trecho_normal[i],localizar);

    for(int i = 0; trecho_normal[i] != '\0'; i++){
        if ( !isdigit(trecho_normal[i],localizar) ){
            if ( !isalpha (trecho_normal[i],localizar) )
                trecho_normal.erase(i, 1);
        }
    }
    return trecho_normal;
}


int Texto::palavras_total() const{
    return palavras;
}


int Texto::palavras_distintas(std::string trecho_normal){
    int guarda_palavra = 0;
    for(std::list<std::string>::iterator i=texto_completo.begin(); i!=texto_completo.end(); i++){
        if(*i == trecho_normal){
            guarda_palavra++;
        }
    }
    return guarda_palavra;
}


bool Texto::presente(std::string trecho_normalizado){
    for(std::list<std::string>::iterator i=texto_completo.begin(); i!=texto_completo.end(); i++){
        if(*i == trecho_normalizado)
            return true;
    }
    return false;
}


std::string Texto::ultima_palavra() const{
    return texto_completo.back();
}


void Texto::retira_ultima(){
    palavras = palavras-1;
    texto_completo.pop_back();
}


void Texto::operator=(Texto d1){
    deletar();
    arquivo = d1.arquivo;
    palavras = d1.palavras;
    for(std::list<std::string>::iterator i=d1.texto_completo.begin(); i!=d1.texto_completo.end(); i++){
        texto_completo.push_back(*i);
    }
}


void Texto::deletar(){
    while(palavras != 0)
        retira_ultima();
}

    
