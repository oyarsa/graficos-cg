#Projeto de criação de gráficos

Dados de entrada: população das facções em servidores de World of Warcraft

Fonte de dados: https://realmpop.com/

Gráficos implementados: barras, pizza e estrela

##Estrutura do projeto:
-lib/ : pasta das bibliotecas

    -json/ : biblioteca JsonCpp, utilizada para ler o Json de entrada

-src/ : arquivos de implementação

    -parse_entrada.cpp: função de leitura
    -servidor.cpp: métodos da classe Servidor
    -grafico.cpp: métodos da classe abstrata Grafico
    -grafico_barras.cpp: métodos concretos da classe Grafico_barras
    -util.cpp: funções de utilidade

-include/ : arquivos de cabeçalho

    -parse_entrada.h: expõe a função carregar_servidores
    -servidor.h: define a classe Servidor
    -grafico.h: define a classe abstrata Grafico
    -grafico_barras: define a classe concreta Grafico_barras, filha de Grafico
    -util.h: define funções de utilidade 

-data/ : arquivos de entrada

    -data_us.json: arquivo com dados completos sobre os servidores da reigão US
