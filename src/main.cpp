﻿#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include "redactor.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try {

        std::string filename;
        std::cout << "Введите название файла\n";
        std::cin >> filename;

        Redactor* a = new Redactor(filename);
        a->execute();

        delete a;
    }
    catch (...) {
        std::cout << "Error has occured";
    }

    return 0;
}
