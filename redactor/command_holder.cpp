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



//void Command_holder::push_back(Command* a) {
//	holder.push_back(a);
//	if (command_pointer != holder.end()) {
//		++command_pointer;
//	}
//	else command_pointer = holder.begin();
//}
//
//Command* Command_holder::get_forward() {
//	return *(++command_pointer);
//}
//
//void Command_holder::clear_forward() {
//	auto buf = command_pointer;
//	++buf;
//	while (buf != holder.end()) {
//		holder.erase(buf++);
//	}
//}
//
//Command* Command_holder::get_back() {
//	if (command_pointer != holder.begin())
//		return *(command_pointer--);
//	else
//		return*(command_pointer);
//}