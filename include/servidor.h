#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include <ostream>

class Servidor
{
public:
    Servidor(const std::string& nome, int populacao_horda, int populacao_alianca,
             const std::string& tipo, const std::string& regiao);

    // Getters
    /// Retorna o nome do Servidor
    const std::string& nome() const;
    /// Retorna o número de personagens da Horda nesse servidor
    int populacao_horda() const;
    /// Retorna o número de personagens da Aliança nesse servidor
    int populacao_alianca() const;
    /// Retorna a porcentagem de persoangens da Horda nesse servidor
    double porcentagem_horda() const;
    /// Retorna a porcentagem de persoangens da Aliança nesse servidor
    double porcentagem_alianca() const;
    /// Retorna o tipo do servidor (PvE ou PvP)
    const std::string& tipo() const;
    /// Retorna a região do servidor (ex. "United States" ou "Brazil")
    const std::string& regiao() const;

private:
    // Nome do servidor
    std::string nome_;
    // Número de personagens da Horda no servidor
    int         populacao_horda_;
    // Número de personagens da Aliança no servidor
    int         populacao_alianca_;
    // Porcentagem de persoangens da Horda no servidor
    double      porcentagem_horda_;
    // Porcentagem de persoangens da Aliança no servidor
    double      porcentagem_alianca_;
    // Tipo do servidor (PvE ou PvP)
    std::string tipo_;
    // Região do servidor
    std::string regiao_;
};

/// Retorna uma representação textual do Servidor
std::string to_string(const Servidor& servidor);
/// Imprime um representação textual do Servidor na stream de saída `os`
std::ostream& operator<<(std::ostream& os, const Servidor& servidor);

#endif // SERVIDOR_H
