#ifndef PARSE_ENTRADA_H
#define PARSE_ENTRADA_H

#include <vector>
#include <string>
#include "servidor.h"

/// Carrega uma cole��o de Servidores a partir de um arquivo Json do
/// formato apropriado em `caminho`. Se o `caminho` n�o contiver um
/// arquivo, a fun��o lan�a std::runtime_error
/// @param caminho Caminho do arquivo de dados
/// @return vector de Servidores
std::vector<Servidor> carregar_servidores(const std::string& caminho);

#endif // PARSE_ENTRADA_H_INCLUDED
