//
// Created by galbert on 17/06/23.
//

#include <sys/stat.h>
#include <iostream>
#include "Collection.hpp"

void Collection::collec_launcher(vector<string> command)
{
    if (command[0] == "open")
        open(command[1]);
    if (command[0] == "add")
        add();
    if (command[0] == "work")
        work_on(getKit(command[1]));
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

    temp.generate();
    _builds.push_back(temp);
    cout << "Model kit has been added to collection, you can work on it using \"work [name]\"." << endl;
}

void Collection::show()
{
    for (int i = 0; i < _builds.size(); i++)
        cout << _builds[i].getName() << endl;
}

void Collection::work_on(Models model)
{
    string input;

    while (true) {
        cout << GRADE[model.getGrade()] << " " << model.getName() << " > ";
        getline(cin, input);
        if (input == "exit")
            break;
    }
}

Models Collection::getKit(string name)
{
    for (auto& maquette : _builds) {

        if (maquette.getName() == name) {
            return maquette;
        }
    }
    // Si la maquette n'a pas été trouvée, on renvoie une maquette vide
    return Models();
}
