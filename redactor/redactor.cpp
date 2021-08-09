#include "redactor.h"
#include "command.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>

void Redactor::execute()
{
	int choise = 1;

	std::ofstream fout;

	while (choise) {

		system("cls");

		print();

		std::cout << "��������:\n"
			<< "0.������� ��������\n"
			<< "1.����������� ������ � ��������� �������\n"
			<< "2.�������� ������ � �����\n"
			<< "3.�������� ������� �� �������� �������\n"
			<< "4.�������� �������� �����\n"
			<< "5.������ ���� ��������� ����� ��������� � ������ �� ������ ������\n"
			<< "6.��������� ��������� b, i, u ��� ��������� ��������� ��������\n"
			<< "7.����� ��������� b, i, u ��� ��������� ��������� ��������\n"
			<< "8.������ ��������\n"
			<< "9.������� ����������� ��������\n"
			<< "10.��������� ��������\n";

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
			std::cout << "������� ������\n";
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
			std::cout << "������� ���������, ������� ����� ��������\n";
			std::cin >> from;
			std::cout << "������� ���������, �� ������� ����� ��������\n";
			std::cin >> to;
			a = new Replase(from, to, text);
			break;
		case(6):
			size_t start;
			size_t end;
			std::cout << "������� ������ ���������\n";
			std::cin >> start;
			std::cout << "������� ����� ���������\n";
			std::cin >> end;
			std::cout << "������� ������� (b, i, u)\n";
			std::cin >> sym;
			a = new SetupBIU(start, end, sym, text);
			break;
		case(7):
			std::cout << "������� ������ ���������\n";
			std::cin >> start;
			std::cout << "������� ����� ���������\n";
			std::cin >> end;
			std::cout << "������� ������� (b, i, u)\n";
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
			std::cout << "������������ ����\n";
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
