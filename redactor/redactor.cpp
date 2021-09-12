#include <iostream>
#include <fstream>
#include <string>
#include "redactor.h"
#include "command.h"

Redactor::Redactor(std::string& file) : cursor_position(0), filename(file) {
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

void Redactor::print() const {
	size_t size = text.length();
	for (size_t i = 0; i < size; ++i) {
		if (i == cursor_position) std::cout << "|";
		std::cout << text[i];
	}
	std::cout << "\n";
}

void Redactor::execute()
{
	int choise = 1;

	std::ofstream fout;

	while (choise) {

		system("cls");

		print();

		std::cout << "Действия:\n"
			<< "0.Закрыть редактор\n"
			<< "1.Переместить курсор в указанную позицию\n"
			<< "2.Вставить символ в текст\n"
			<< "3.Удаление символа из заданной позиции\n"
			<< "4.Удаление текущего слова\n"
			<< "5.Замена всех вхождений одной подстроки в тексте на другую строку\n"
			<< "6.Установка признаков b, i, u для заданного диапазона символов\n"
			<< "7.Сброс признаков b, i, u для заданного диапазона символов\n"
			<< "8.Отмена действия\n"
			<< "9.Возврат отмененного действия\n"
			<< "10.Сохранить документ\n";

		std::cin >> choise;
		Command* a = 0;

		std::string from;
		std::string to;

		switch (choise) {
		case(0):
			break;
		case(1):
			size_t new_cursor_pos;
			std::cin >> new_cursor_pos;
			if (new_cursor_pos >= text.size()) 
				new_cursor_pos = text.size() - 1;
			a = new Move(&cursor_position, new_cursor_pos, text);
			break;
		case(2):
			std::cout << "Введите символ\n";
			char sym;
			std::cin >> sym;
			a = new Insert(sym, text);
			break;
		case(3):
			a = new Sym_erase(text);
			break;
		case(4):
			a = new Word_erase(text);
			break;
		case(5):
			std::cout << "Введите подстроку, которую нужно заменить\n";
			std::cin >> from;
			std::cout << "Введите подстроку, на которую нужно заменить\n";
			std::cin >> to;
			a = new Replase(from, to, text);
			break;
		case(6):
			size_t start;
			size_t end;
			std::cout << "Введите начало диапазона\n";
			std::cin >> start;
			std::cout << "Введите конец диапазона\n";
			std::cin >> end;
			std::cout << "Введите признак (b, i, u)\n";
			std::cin >> sym;
			a = new SetupBIU(start, end, sym, text);
			break;
		case(7):
			std::cout << "Введите начало диапазона\n";
			std::cin >> start;
			std::cout << "Введите конец диапазона\n";
			std::cin >> end;
			std::cout << "Введите признак (b, i, u)\n";
			std::cin >> sym;
			a = new DeleteBIU(start, end, sym, text);
			break;
		case(8):
			a = commands.get_back();
			if (a) a->unexecute();
			break;
		case(9):
			a = commands.get_forward();
			if (a) a->execute();
			break;
		case(10):
			fout.open(filename);
			fout << text;
			fout.close();
			break;
		default:
			std::cout << "Неправильный ввод\n";
			continue;
		}

		if (choise < 8 && choise) {
			a->set_cursor(cursor_position);
			commands.push_back(a);
			commands.clear_forward();
			a->execute();
		}

	}
}
