#ifndef PARSE_ENTRADA_H
#define PARSE_ENTRADA_H

#include <vector>
#include <string>
#include "servidor.h"

/// Carrega uma coleção de Servidores a partir de um arquivo Json do
/// formato apropriado em `caminho`. Se o `caminho` não contiver um
/// arquivo, a função lança std::runtime_error
/// @param caminho Caminho do arquivo de dados
/// @return vector de Servidores
std::vector<Servidor> carregar_servidores(const std::string& caminho);

#endif // PARSE_ENTRADA_H_INCLUDED
