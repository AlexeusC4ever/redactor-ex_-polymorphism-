#include "command_holder.h"

void Command_holder::push_back(Command* a) {
	IsEmpty = false;
	back.push(a);
}

Command* Command_holder::get_forward() {
	if (forward.empty()) { 
		return nullptr;
	}
	Command* a = forward.top();
	back.push(a);
	forward.pop();
	return a;
}

void Command_holder::clear_forward() {
	while (!forward.empty()) { 
		delete forward.top();
		forward.pop();
	}
}

Command* Command_holder::get_back() {
	if (back.empty()) { 
		return nullptr;
	}
	Command* a = back.top();
	forward.push(a);
	back.pop();
	return a;
}