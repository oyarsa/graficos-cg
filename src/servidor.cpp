#include "servidor.h"

#include <sstream>

Servidor::Servidor(const std::string& nome, int populacao_horda, int populacao_alianca,
                   const std::string& tipo, const std::string& regiao)
    : nome_{nome},
      populacao_horda_{populacao_horda},
      populacao_alianca_{populacao_alianca},
      porcentagem_horda_{},
      porcentagem_alianca_{},
      tipo_{tipo},
      regiao_{regiao}
{
    double total = populacao_horda_ + populacao_alianca;
    if (total == 0.0) {
        total = 1.0;
    }

    porcentagem_horda_ = (populacao_horda_ / total);
    porcentagem_alianca_ = (populacao_alianca_ / total);
}

const std::string& Servidor::nome() const
{
    return nome_;
}

double Servidor::porcentagem_horda() const
{
    return porcentagem_horda_;
}

double Servidor::porcentagem_alianca() const
{
    return porcentagem_alianca_;
}

int Servidor::populacao_horda() const
{
    return populacao_horda_;
}

int Servidor::populacao_alianca() const
{
    return populacao_alianca_;
}

const std::string& Servidor::tipo() const
{
    return tipo_;
}

const std::string& Servidor::regiao() const
{
    return regiao_;
}

std::string to_string(const Servidor& servidor)
{
    std::ostringstream oss;
    oss << servidor.nome() << ", "
        << servidor.populacao_horda() << "(" << servidor.porcentagem_horda() << "%)" << ", "
        << servidor.populacao_alianca() << "(" << servidor.porcentagem_alianca() << "%)";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Servidor& servidor)
{
    return os << to_string(servidor);
}
