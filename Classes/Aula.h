//
// Created by du on 13-10-2022.
//

#ifndef PROJ_AULA_H
#define PROJ_AULA_H
#include <string>
#include <iostream>
#include <map>
class Aula {
public:
    typedef std::map<std::string, int> OpMap;
    static OpMap dias;
    typedef std::map<std::string, std::string> OpMap1;
    static OpMap1 pt;
    //construtor
    Aula(std::string codigo_turma, std::string codigo_uc,std::string dia_semana,double hora_inicio,double duracao,std::string tipo);

    //getters
    std::string get_codigo_turma() const;
    std::string get_codigo_uc() const;
    std::string get_dia_semana() const;
    double get_hora_inicio() const;
    double get_duracao() const;
    std::string get_tipo() const;

    //compare

    static bool cmp(Aula* aula, Aula* aula2);
    struct cmp_nome{bool operator()(Aula* aula, Aula* aula2) const;};
    //show
    void show();
    bool overload(Aula* aula);

private:
    static OpMap init_map() {
        std::map<std::string,int> days = {
                std::pair<std::string,int> ("Monday",1),
                std::pair<std::string,int> ("Tuesday",2),
                std::pair<std::string,int> ("Wednesday",3),
                std::pair<std::string,int> ("Thursday",4),
                std::pair<std::string,int> ("Friday",5),
        };
        return days;
    }
    static OpMap1 init_map1() {
        std::map<std::string,std::string> pt = {
                std::pair<std::string,std::string> ("Monday","Segunda-feira"),
                std::pair<std::string,std::string> ("Tuesday","Terça-feira"),
                std::pair<std::string,std::string> ("Wednesday","Quarta-feira"),
                std::pair<std::string,std::string> ("Thursday","Quinta-feira"),
                std::pair<std::string,std::string> ("Friday","Sexta-feira"),
        };
        return pt;
    }
    std::string codigo_turma;
    std::string codigo_uc;
    std::string dia_semana;
    double hora_inicio;
    double duracao;
    std::string tipo;
    //Lista de turmas a que a aula pertence???
};



#endif //PROJ_AULA_H
