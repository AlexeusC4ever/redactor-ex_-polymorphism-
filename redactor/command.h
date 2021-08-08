#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>

class Command {
protected:
	size_t cursor_pos;
	std::string& text;

public:
	Command(std::string& text_) : text(text_) {}
	virtual ~Command() {}

	virtual void execute();
	virtual void unexecute();
	void set_cursor(size_t pos) { cursor_pos = pos; }
	size_t get_cursor() { return cursor_pos; }
};

class Move : public Command {
private:
	size_t* cursor_current;
	size_t cursor_previous;
	size_t cursor_new;

public:
	Move(size_t* current_pos, size_t new_pos, std::string& text) : 
		Command(text), cursor_current(current_pos), cursor_new(new_pos) {}
	void execute() override;
	void unexecute() override;

	size_t get_previous_cursor(){ return cursor_previous; }
};


class Insert : public Command {
private:
	char sym;

public:
	Insert(char sym_, std::string& text) :Command(text), sym(sym_) {}

	void execute() override;
	void unexecute() override;
};

class Sym_erase : public Command {
private:
	char sym;

public:
	Sym_erase(std::string& text) : Command(text) {}
	void execute() override;
	void unexecute() override;
};

class Word_erase : public Command {
private:
	std::string word;
	size_t new_cursor_pos;

public:
	Word_erase(std::string& text) : Command(text) {}
	void execute() override;
	void unexecute() override;
};

class Replase : public Command {
private:
	std::string from;
	std::string to;

public:
	Replase(std::string& from_, std::string& to_, std::string& text) : 
		from(from_), to(to_), Command(text) {}

	void execute() override;
	void unexecute() override;
};


class SetupBIU : public Command {
private:
	char sym;
	size_t start;
	size_t end;

public:
	SetupBIU(size_t start_, size_t end_, char sym_, std::string& text) :
		start(start_), end(end_), sym(sym_), Command(text) {}
	void execute() override;
	void unexecute() override;
};

class DeleteBIU : public Command {
private:
	char sym;
	size_t start;
	size_t end;

public:
	DeleteBIU(size_t start_, size_t end_, char sym_, std::string& text) :
		start(start_), end(end_), sym(sym_), Command(text) {}
	void execute() override;
	void unexecute() override;
};

#endif  //_COMMAND_H_