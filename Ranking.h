#ifndef RANKING_H
#define RANKING_H

#include <map>
#include <vector>
#include "Leitor.h"

class Ranking{
public:
    //Inicia um indice vazio
    Ranking();
    
    //indexa as palavras do texto
    Ranking(Texto const d1);
    
    //Constroi um indice invertido com os arquivos de entrada
    Ranking(std::string arquivo);
    
    //avalia se o elemnto esta presente no vetor
    bool presente(std::string texto) const;
    
    //acresenta elementos ao vetor
    void acrescentar(Texto const d2);
    
    //Retorna o numero de palavras do indice
    int tamanho_indice();
    
    //Retorna a quantidade de arquivos relacionados ao indice
    int arquivo_documentos();
    
    //Retorna a quantidade de arquivos relacionados a palavra
    int arquivos_palavra(std::string texto);
    
    //Remove o ultimo elemento do indice
    void remove_ultimo();
    
    //Retorna ultimo elemento das chaves do indice
    std::string ultima_chave();
    
    //determina a importancia de uma palavra de acordo com sua frequencia idf(x)=log(N/n(x))
    double importancia(std::string texto);
    
    //determina a coordenada de uma palavra W(dj,Px) = tf(dj,Px) × idf(Px)
    double coordenada(Texto const d,std::string texto);
    
    //determina a similaridade para cada palavra em uma pesquisa por meio do cosseno da coordenada
    double similaridade_cosseno(Texto const D,Texto const q);
    
    //retorna a similaridade dos documentos com a pesquisa por meio da soma dos cossenos
    std::list<double> similaridade_documentos(Texto q);
    
    //cria o ranking com os nomes dos documentos baseado na similaridade dos documentos
    std::list<std::list<std::string>> ranking(Texto k);
    
    //imprime ranking
    void imprimir(std::ostream& out,Texto k);

private:
    //Quantidade de palavras no vocabulario
    int qtdd_palavras;
    
    //Quantidade de documentos total de entrada
    int qtdd_documentos;
    
    //Documentos que formam o indice
    std::list<Texto> Arquivos;
    
    //Dicionario que associa palavras a documentos
    std::map<std::string,std::list<std::string>> vocabulario;
    
    //vetor de vocabulario
    std::list<std::string> vetor_vocabulario;
    
};

#endif // INDICE_INVERTIDO_H_
