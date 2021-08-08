#ifndef _COMMAND_HOLDER_H_
#define _COMMAND_HOLDER_H_

#include "command.h"
#include <stack>

class Command_holder {
private:
	std::stack<Command*> back;
	std::stack<Command*> forward;
	bool IsEmpty;

public:
	Command_holder() : IsEmpty(true) {}
	~Command_holder() {
		while (!back.empty()) {
			delete back.top();
			back.pop();
		}
		while (!forward.empty()) {
			delete forward.top();
			forward.pop();
		}
	}

	void push_back(Command* a);

	Command* get_back();

	Command* get_forward();

	void clear_forward();

	bool isEmpty() { return IsEmpty; };
};

#endif  //_COMMAND_HOLDER_H_