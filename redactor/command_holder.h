#ifndef _COMMAND_HOLDER_H_
#define _COMMAND_HOLDER_H_

#include "command.h"
#include <stack>
#include <list>

const unsigned overflow = 10;

class Command_holder {
private:
	std::list<Command*> back;
	std::stack<Command*> forward;
	bool IsEmpty;

public:
	Command_holder() : IsEmpty(true) {}
	~Command_holder() {
		auto it = back.begin();
		while (it != back.end()) {
			delete *it;
			back.erase(it++);
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

//class Command_holder {
//private:
//	std::list<Command*> holder;
//	std::list<Command*>::iterator command_pointer;
//
//public:
//	Command_holder() :
//		holder() {
//		command_pointer = holder.end();
//	}
//	~Command_holder() {
//		holder.clear();
//	}
//
//	void push_back(Command* a);
//
//	Command* get_back();
//
//	Command* get_forward();
//
//	void clear_forward();
//};