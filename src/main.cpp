/*
*	File:			main.cpp
*	Created:		GAlbert 21.01.24
*	Description:	File for the strategy pattern applied to recognise different commands given to the shell
*/

#include <string>
#include <iostream>
#include "MonkeyShell.hpp"

int main() {
    MonkeyShell shell;

    if (__argc == 2) {
        shell.preload(__argv[1]);
    }
    shell.start();

    return 0;
}
