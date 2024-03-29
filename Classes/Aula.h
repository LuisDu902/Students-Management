#ifndef PROJ_AULA_H
#define PROJ_AULA_H

#include <string>
#include <iostream>
#include <utility>
#include <map>

class Aula {
public:
    Aula(std::string, std::string,std::string, double, double, std::string);

    std::string get_tipo()const;
    std::string get_codigo_turma() const;
    std::string get_codigo_uc() const;
    std::string get_dia_semana() const;
    double get_hora_inicio() const;

    static bool cmp(Aula*, Aula*);
    bool sobrepoe(Aula*) const;
    void show() const;

    typedef std::map<std::string, int> Days;  static Days dias;
    typedef std::map<std::string, std::string> Conversion; static Conversion portugues;

private:
    std::string codigo_turma;
    std::string codigo_uc;
    std::string dia_semana;
    double hora_inicio;
    double duracao;
    std::string tipo;

    static Days dias_semana() {
        std::map<std::string,int> dias1 = {
                std::pair<std::string,int> ("Monday",1),
                std::pair<std::string,int> ("Tuesday",2),
                std::pair<std::string,int> ("Wednesday",3),
                std::pair<std::string,int> ("Thursday",4),
                std::pair<std::string,int> ("Friday",5),
        };
        return dias1;
    }
    static Conversion para_portugues() {
        std::map<std::string,std::string> pt = {
                std::pair<std::string,std::string> ("Monday","Segunda-feira"),
                std::pair<std::string,std::string> ("Tuesday","Terça-feira"),
                std::pair<std::string,std::string> ("Wednesday","Quarta-feira"),
                std::pair<std::string,std::string> ("Thursday","Quinta-feira"),
                std::pair<std::string,std::string> ("Friday","Sexta-feira"),
        };
        return pt;
    }
};
#endif //PROJ_AULA_H
