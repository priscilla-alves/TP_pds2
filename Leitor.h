#ifndef LEITOR_H
#define LEITOR_H

#include <string>
#include <list>

class Texto{
public:
    //Cria arquivo de texto vazio
    Texto();
    
    //recebe arquivos de textos (nome como parametro)
    Texto(std::string arquivo);
    
    //padronizar o texto em minusculas sem sinais graficos(localiza e deleta caracteres que nao sejam alfabeticos
    std::string NormalizaTexto(std::string trecho_normalizado);
    
    //Numero de palavras
    int palavras_total() const;
    
    //Quantidade de palavras distintas (nao conta palavras repetidas)
    int palavras_distintas(std::string texto);
    
    //Retorna a ultima palavra do documento
    std::string ultima_palavra() const;
    
    //apaga a ultima palavra do documento
    void retira_ultima();
    
    //verifica se a palavra esta presente no texto normalizado
    bool presente(std::string trecho_normalizado);
    
    //Copia os elementos de um documento para outro
    void operator=(Texto d1);
    
    //Deleta todas as palavras do arquivo (da ultima p primeira)
    void deletar();
    
    //Retorna de qual arquivo foi retirado o trecho
    std::string arquivo_fonte() const;
    
private:
    //Nome do arquivo
    std::string arquivo;
    
    //Numero de palavras na lista
    int palavras;
    
    //guarda todas as palavras numa lista
    std::list<std::string> texto_completo;
};


#endif // LEITOR_H
