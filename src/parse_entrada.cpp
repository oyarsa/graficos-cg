#include "parse_entrada.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "json/json.h"

/// Função auxiliar que recebe um objeto Json e instancia um
/// Servidor a partir dele
/// @param servidor_json Um objeto Json
/// @return um Servidor carregado a partir do objeto
Servidor carregar_servidor(const Json::Value& servidor_json)
{
    auto nome = servidor_json["name"].asString();
    auto populacao_horda = servidor_json["counts"]["Horde"].asInt();
    auto populacao_alianca = servidor_json["counts"]["Alliance"].asInt();
    auto tipo = servidor_json["stats"]["pvp"].asString();
    auto regiao = servidor_json["stats"]["region"].asString();

    return {nome, populacao_horda, populacao_alianca, tipo, regiao};
}

std::vector<Servidor> carregar_servidores(const std::string& caminho)
{
    std::ifstream arquivo{caminho};
    if (!arquivo) {
        throw std::runtime_error{"Arquivo não de entrada não foi encontrado"};
    }

    // Carrega o Json inteiro para a memória a partir do arquivo.
    // Se o Json estiver mal formatado, uma exceção será lançada
    Json::Value raiz;
    arquivo >> raiz;

    const auto& servidores_json = raiz["realms"];
    // Percorre os objetos da propriedade "realms", convertendo para Servidores
    std::vector<Servidor> servidores;
    std::transform(std::begin(servidores_json), std::end(servidores_json),
                   std::back_inserter(servidores), carregar_servidor);

    return servidores;
}
