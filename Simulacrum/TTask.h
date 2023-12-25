#pragma once

#include <string>
#include <ctime>

using std::string;

static const string availableChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
static const size_t lengthAlphabet = availableChar.length();

class TTask {
private:
	string RandName(size_t length) {
		string name = "";

		for (int i = 0; i < length; ++i) {
			name += availableChar[rand() % lengthAlphabet];
		}

		return name;
	}
public:
	int id = 0;
	string name;

	TTask(int _length = 10) : name(RandName(_length)) {}
	TTask(const string& str) :name(str) {}
};