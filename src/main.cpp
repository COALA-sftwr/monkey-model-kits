//
// Created by galbert on 17/06/23.
//

#include "../include/Models.hpp"
#include <iostream>
#include <ctime>
#include <csignal>
#include <cstring>

using namespace std;

#define TOKENSIZE 100

void StrTokenizer(char *input, char **argv)
{
    char *stringTokenized;
    stringTokenized = strtok(input, " ");
    while(stringTokenized != nullptr)
    {
        *argv++  = stringTokenized;
        stringTokenized = strtok(nullptr, " ");
    }

    *argv = nullptr;
}

int main() {
    char *path2;
    char *arr [250];
    char *Tokenized ;
    char input[250];
    char *argv[TOKENSIZE];
    Collection collec;

    while(true)
    {
        cout<< "cwushell-> ";
        cin.getline(input,250);
        StrTokenizer(input, argv);
        if (strcmp(input, "exit") == 0)

        {
            break;
        }
        else if (strcmp(input, "\n") == 0){
            continue;
        }
        collec.collec_launcher(input);
    }
    return 0;
}
