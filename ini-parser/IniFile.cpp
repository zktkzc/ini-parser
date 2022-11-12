#include "IniFile.h"
#include<sstream>
#include<fstream>
#include<iostream>

Value::Value()
{
}

Value::Value(bool value)
{
	*this = value;
}

Value::Value(int value)
{
	*this = value;
}

Value::Value(double value)
{
	*this = value;
}

Value::Value(const char* value)
{
	*this = value;
}

Value::Value(const string& value)
{
	*this = value;
}

Value& Value::operator=(bool value)
{
	m_value = value ? "true" : "false";
	return *this;
}

Value& Value::operator=(int value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value& Value::operator=(double value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value& Value::operator=(const char* value)
{
	m_value = value;
	return *this;
}

Value& Value::operator=(const string& value)
{
	m_value = value;
	return *this;
}

Value::operator bool()
{
	return m_value == "true";
}

Value::operator int()
{
	return atoi(m_value.c_str());
}

Value::operator double()
{
	return atof(m_value.c_str());
}

Value::operator string()
{
	return m_value;
}

IniFile::IniFile()
{
}

bool IniFile::load(const string& filename)
{

	m_filename = filename;

	ifstream fin(filename);
	if (fin.fail())
	{
		return false;
	}

	string line;
	string section;

	while (getline(fin, line))
	{
		line = trim(line);
		if (line == "")
		{
			continue;
		}
		if (line[0] == '[')
		{
			int pos = line.find_first_of(']');
			section = line.substr(1, pos - 1);
			section = trim(section);
			m_section[section] = Section();
		}
		else
		{
			int pos = line.find_first_of('=');
			string key = line.substr(0, pos);
			key = trim(key);
			string value = line.substr(pos + 1, line.length() - pos);
			value = trim(value);
			m_section[section][key] = value;
		}
	}

	fin.close();
	return true;
}

void IniFile::show()
{
	cout << str();
}

bool IniFile::save(const string& filename)
{
	ofstream fout(filename);
	if (fout.fail())
	{
		return false;
	}
	fout << str();
	fout.close();
	return true;
}

string IniFile::str()
{
	stringstream ss;
	for (auto it = m_section.begin(); it != m_section.end(); it++)
	{
		ss << "[" << it->first << "]" << endl;
		for (auto iter = it->second.begin(); iter != it->second.end(); iter++)
		{
			ss << iter->first << " = " << string(iter->second) << endl;
		}
		ss << endl;
	}
	return ss.str();
}

Value& IniFile::get(const string& section, const string& key)
{
	return m_section[section][key];
}

void IniFile::set(const string& section, const string& key, const Value& value)
{
	m_section[section][key] = value;
}

// ÅÐ¶ÏkeyÊÇ·ñ´æÔÚ
bool IniFile::has(const string& section, const string& key)
{
	map<string, Section>::const_iterator it = m_section.find(section); // ÅÐ¶ÏsectionÊÇ·ñ´æÔÚ
	if (it != m_section.end())
	{
		return (it->second.find(key) != it->second.end());
	}
	return false;
}

// ÅÐ¶ÏsectionÊÇ·ñ´æÔÚ
bool IniFile::has(const string& section)
{
	return (m_section.find(section) != m_section.end());
}

// É¾³ýkey
void IniFile::remove(const string& section, const string& key)
{
	map<string, Section>::iterator it = m_section.find(section); // ÅÐ¶ÏsectionÊÇ·ñ´æÔÚ
	if (it != m_section.end())
	{
		// section´æÔÚ£¬É¾³ýkey
		it->second.erase(key);
	}
}

// É¾³ýsection
void IniFile::remove(const string& section)
{
	m_section.erase(section);
}

// Çå¿ÕiniÎÄ¼þ
void IniFile::clear()
{
	m_section.clear();
}

string IniFile::trim(string s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" \n\r"));
	s.erase(s.find_last_not_of(" \n\r") + 1);
	return s;
}
