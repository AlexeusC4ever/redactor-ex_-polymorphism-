#ifndef _REDACTOR_H_
#define _REDACTOR_H_

#include "command_holder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

static unsigned redactor_call_counter = 0;

class Redactor {
private:
	std::string filename;
	Command_holder commands;
	std::string text;
	size_t cursor_position;

public:
	Redactor(std::string& file): cursor_position(0), filename(file) {
		++redactor_call_counter;
		std::cout << redactor_call_counter << "\n";
		Sleep(1000);
		try {
			std::string buf;
			std::ifstream fin;
			fin.open(filename);
			if (!fin) throw "file error\n";

			while (!fin.eof()) {
				std::getline(fin, buf);
				text += buf + "\n";
			}
			fin.close();
		}
		catch (const char* a) {
			std::cout << a;
			throw;
		}
	}

	void print() { 
		size_t size = text.length();
		for (size_t i = 0; i < size; ++i) {
			if (i == cursor_position) std::cout << "|";
			std::cout << text[i];
		}
		std::cout << "\n";
	}

	void execute();
};

#endif  //_REDACTOR_H_