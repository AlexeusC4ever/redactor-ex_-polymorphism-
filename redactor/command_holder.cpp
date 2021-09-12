#include "command_holder.h"

void Command_holder::push_back(Command* a) {
	back.push_back(a);
	if (IsEmpty) {
		IsEmpty = false;
	}
	else if (back.size() > overflow) {
		delete *back.begin();
		back.erase(back.begin());
	}
}

Command* Command_holder::get_forward() {
	if (forward.empty()) { 
		return nullptr;
	}
	Command* a = forward.top();
	back.push_back(a);
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
	Command* a = back.back();
	forward.push(a);
	back.erase(std::prev(back.end()));
	return a;
}

bool Command_holder::isEmpty() const
{
	return IsEmpty;
};

Command_holder::~Command_holder() {
	auto it = back.begin();
	while (it != back.end()) {
		delete* it;
		back.erase(it++);
	}
	while (!forward.empty()) {
		delete forward.top();
		forward.pop();
	}
}