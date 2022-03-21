#ifndef COMMAND_HOLDER_H_
#define COMMAND_HOLDER_H_

#include <stack>
#include <list>
#include "command.h"

const unsigned overflow = 100;

class Command_holder {
private:
	std::list<Command*> back;
	std::stack<Command*> forward;
	bool IsEmpty;

public:
	Command_holder() : IsEmpty(true) {}
	~Command_holder();

	void push_back(Command* a);

	Command* get_back();

	Command* get_forward();

	void clear_forward();

	bool isEmpty() const;
};

#endif  // COMMAND_HOLDER_H_
