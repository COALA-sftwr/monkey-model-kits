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

void Collection::collec_launcher(vector<string> command)
{
    if (command[0] == "open") {
        open(command[1]);
    }
    if (command[0] == "add") {
        add();
    }
}

void Collection::open(const string& file)
{
    int status = mkdir(_path.c_str(), 0777);
    _path.append("/MMK");

    if (status != 0 && errno != EEXIST) { // S'il y a eu une erreur lors de la création du dossier, on affiche un message d'erreur
        std::cerr << "Erreur lors de la création du dossier" << std::endl;
        return;
    }

    // On ouvre le fichier en mode écriture, ce qui le crée s'il n'existe pas déjà
    _file.open(_path + "/" + file, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

    if (!_file.is_open()) { // Si le fichier n'a pas pu être ouvert, il y a eu une erreur
        std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
        return;
    }

    // Le fichier a été ouvert avec succès
    std::cout << "Le fichier a été ouvert avec succès" << std::endl;
}

void Collection::add() // TODO: finish to implement add function
{
    Models temp;
}


// MODELS TODO: add chronometer functions to finish model kit creation

Models::Models()
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
    cout << _price << endl;
}

Models::Grade Models::stGrade(string input)
{
    static const char* const grade[] = {"EG", "SD", "HG", "RG", "MG", "PG", "MZ", "OG", "ST"};
    static const size_t nb_couleurs = sizeof(grade) / sizeof(grade[0]);

    for (size_t i = 0; i < nb_couleurs; ++i) {
        if (input == grade[i]) {
            return static_cast<Grade>(i);
        }
    }

    // Gérer le cas où la chaîne ne correspond à aucune valeur de l'énumérateur
    throw std::invalid_argument("Chaîne invalide pour Couleur");
}
