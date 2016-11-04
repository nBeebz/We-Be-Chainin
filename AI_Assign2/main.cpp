#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

void addRule(const string &cause, const string &affect);
void split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
bool satisfied(vector<string> conditions);

map<string, vector<string>> rules;
vector<string> facts;


int main() {
	ifstream ifs;
	ifs.open("input.txt");
	string str;
	vector<string> line;

	if (ifs.is_open())
	{
		while ( getline(ifs, str) )
		{
			line = split(str, '>');
			if (line.size() == 1) {
				facts.push_back(line[0]);
			}
			else if (line.size() > 1) {
				addRule(line[0], line[1]);
			}
		}
	}

	bool finished = false;

	do {
		for (auto const& it : rules) {
			if (satisfied(it.second)) {
				if (std::find(facts.begin(), facts.end(), it.first) == facts.end()) {
					facts.push_back(it.first);
					finished = false;
				}
			}
		}
		finished = true;
	} while (!finished);

	vector<string> strings;
	cout << "RULES\n" << "=========\n";
	for(auto const& it : rules)
	{
	strings = it.second;
	for (size_t i = 0; i < strings.size(); i++)
	{
	cout << strings[i] << (i == strings.size()-1 ? "" : ",");
	}
	cout << ">" << it.first << '\n';
	}

	cout << "\nFACTS\n" << "=========\n";
	for (size_t i = 0; i < facts.size(); i++)
	{
	cout << facts[i] << '\n';
	}
	

	// while !finished iterate through map
	// if value(s) are contained in facts
	// add char to list of facts
	// if no changes made finished = true
	while(true){}
}

bool satisfied(vector<string> conditions) {
	for (size_t i = 0; i < conditions.size(); i++)
	{
		if (std::find(facts.begin(), facts.end(), conditions[i]) == facts.end()) {
			return false;
		}
	}
	return true;
}

void addRule(const string &cause, const string &affect) {
	vector<string> r = split(cause, ',');
	vector<string> _rules;
	for (size_t i = 0; i < r.size(); i++)
	{
		_rules.push_back(r[i]);
	}
	rules.emplace(affect, _rules);
}

// Split code found on StackOverflow: http://stackoverflow.com/questions/236129/split-a-string-in-c
void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}


vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}