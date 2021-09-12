#include "command.h"

void Move::execute()
{
	cursor_previous = *cursor_current;
	*cursor_current = cursor_new;
}

void Move::unexecute()
{
	*cursor_current = cursor_previous;
}


void Insert::execute()
{
	auto it = text.begin() + cursor_pos;
	text.insert(it, sym);
}

void Insert::unexecute()
{
	Sym_erase a(text);
	a.set_cursor(cursor_pos);
	a.execute();
}

void Sym_erase::execute()
{
	sym = text[cursor_pos];
	auto it = text.begin() + cursor_pos;
	text.erase(it);
}

void Sym_erase::unexecute()
{
	Insert a(sym, text);
	a.set_cursor(cursor_pos);
	a.execute();
}

void Word_erase::execute()
{
	auto buf = text.begin() + cursor_pos;
	size_t counter = 0;
	while (buf != text.begin() && *std::prev(buf) != ' ' && *std::prev(buf) != '>') { 
		--buf;
		++counter;
	}

	if (buf == text.begin() + cursor_pos) return;
	if (*std::next(buf) == '<') return;

	word.clear();

	while (buf != text.end()  && *buf != ' ' && *buf != '<') {
		word.push_back(*buf);
		buf = text.erase(buf);
	}
	if (buf != text.end() && *buf == ' ') { 
		text.erase(buf);
		word.push_back(' ');
	}

	new_cursor_pos = cursor_pos - counter;
	if (cursor_pos >= text.size()) cursor_pos = text.size() - 1;
}

void Word_erase::unexecute()
{
	if (word.empty()) return;
	auto it = text.begin() + new_cursor_pos;
	for (char a : word) {
		text.insert(it, a);
		++it;
	}
}

void Replase::execute()
{
	size_t from_size = from.size();
	size_t buf = text.find(from);
	while (buf != -1) {
		text.replace(buf, from_size, to);
		buf = text.find(from);
	}
}

void Replase::unexecute()
{
	size_t to_size = to.size();
	size_t buf = text.find(to);
	while (buf != -1) {
		text.replace(buf, to_size, from);
		buf = text.find(to);
	}
}

void SetupBIU::execute()
{
	std::string buf;
	auto it = text.begin() + start;
	if (sym == 'u') buf = "<u>";
	else if (sym == 'i') buf = "<i>";
	else if (sym == 'b') buf = "<b>";

	for (char a : buf) {
		text.insert(it, a);
		++it;
	}

	buf.insert(std::next(buf.begin()), '/');
	
	it = text.begin() + end;
	for (char a : buf) {
		text.insert(it, a);
		++it;
	}
}

void SetupBIU::unexecute()
{
	DeleteBIU a(start, end, sym, text);
	a.execute();
}

void DeleteBIU::execute()
{
	std::string buf;
	if (sym == 'u') buf = "<u>";
	else if (sym == 'i') buf = "<i>";
	else if (sym == 'b') buf = "<b>";
	size_t check = text.find(buf, start);

	if (check == -1) return;
	start = check;
	auto it = text.begin() + check;
	for (size_t i = 0; i < buf.size(); ++i) {
		it = text.erase(it);
	}
	buf.insert(std::next(buf.begin()), '/');
	check = text.find(buf, start);
	if (check == -1) return;
	it = text.begin() + check;
	for (size_t i = 0; i < buf.size(); ++i) {
		it = text.erase(it);
	}
	end = check + buf.size();
}

void DeleteBIU::unexecute()
{
	SetupBIU a(start, end, sym, text);
	a.execute();
}
