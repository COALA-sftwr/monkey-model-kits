//
// Created by galbert on 17/06/23.
//

#include "Collection.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    
    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void help()
{
    cout << "-Monkey Model Kits-\n"
            "\tCommands\n"
            "\t  -help:\t\tShows this message.\n"
            "\t  -open [path]:\tOpens a save file.\n"
            "\t  -exit:\t\tExits MMK" << endl;
}

int main() {
    string input;
    vector<string> command;
    Collection collection;

    cout << "Monkey Model Kits launched - input a command or \"help\"." << endl;
    while (input != "exit") {
        cout << "> ";
        getline(cin, input);
        command = split(input, ' ');
        if (command[0] == "help")
            help();
        collection.collec_launcher(command);
    }
    return 0;
}
