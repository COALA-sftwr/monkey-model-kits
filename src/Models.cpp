//
// Created by galbert on 17/06/23.
//

#include <iostream>
#include <ctime>
#include <csignal>
#include <cstring>
#include <sys/stat.h>
#include "Models.hpp"

using namespace std;

// COLLECTION TODO: implement save and retrieve functionality


// MODELS TODO: add chronometer functions to finish model kit creation

Models::Models()
{}

void Models::generate()
{
    string input;

    cout << "Input model kit name:" << endl;
    getline(cin, input);
    setName(input);

    cout << "Input model grade:" << endl;
    getline(cin, input);
    setGrade(input);

    cout << "Input model price:" << endl;
    getline(cin, input);
    setPrice(input);
}

void Models::setName(string name)
{
    _name = name;
}

void Models::setGrade(string input)
{
    _grade = stGrade(input);
}

void Models::setPrice(const string& input)
{
    _price = stod(input, nullptr);
}

string Models::getName()
{
    return _name;
}

Models::Grade Models::getGrade()
{
    return _grade;
}

double Models::getPrice()
{
    return _price;
}

Models::Grade Models::stGrade(string input)
{
    static const size_t nb_couleurs = sizeof(GRADE) / sizeof(GRADE[0]);

    for (size_t i = 0; i < nb_couleurs; ++i) {
        if (input == GRADE[i]) {
            return static_cast<Grade>(i);
        }
    }

    // Gérer le cas où la chaîne ne correspond à aucune valeur de l'énumérateur
    throw std::invalid_argument("Chaîne invalide pour Couleur");
}
