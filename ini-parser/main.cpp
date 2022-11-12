#include<iostream>
#include"IniFile.h"
using namespace std;

int main()
{
	IniFile ini;
	ini.load("./main.ini");

	const string ip = ini["server"]["ip"];
	int port = ini["server"]["port"];

	ini.set("server", "timeout", 1000);
	ini.set("server", "flag", true);

	ini.show();
	ini.save("./temp.ini");

	system("pause");
	return 0;
}