#ifndef REDACTOR_H_
#define REDACTOR_H_

#include "command_holder.h"

class Redactor {
private:
	std::string filename;
	Command_holder commands;
	std::string text;
	size_t cursor_position;

public:
	Redactor(std::string& file);

	void print() const;

	void execute();
};

#endif  // REDACTOR_H_
