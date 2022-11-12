#pragma once
#include<string>
#include<map>
using namespace std;

class Value
{
public:
	Value();
	Value(bool value);
	Value(int value);
	Value(double value);
	Value(const char* value);
	Value(const string& value);

	Value& operator = (bool value);
	Value& operator = (int value);
	Value& operator = (double value);
	Value& operator = (const char* value);
	Value& operator = (const string& value);

	operator bool();
	operator int();
	operator double();
	operator string();

private:
	string m_value;
};

typedef map<string, Value> Section;

class IniFile {
public:
	IniFile();
	bool load(const string& filename);
	void show();
	bool save(const string& filename);
	string str();

	Value& get(const string& section, const string& key);
	void set(const string& section, const string& key, const Value& value);
	// ÅÐ¶ÏkeyÊÇ·ñ´æÔÚ
	bool has(const string& section, const string& key);
	// ÅÐ¶ÏsectionÊÇ·ñ´æÔÚ
	bool has(const string& section);
	// É¾³ýkey
	void remove(const string& section, const string& key);
	// É¾³ýsection
	void remove(const string& section);
	// Çå¿ÕiniÎÄ¼þ
	void clear();

	Section& operator [] (const string& section)
	{
		return m_section[section];
	}

private:
	string trim(string s);

private:
	string m_filename;
	map<string, Section> m_section;
};