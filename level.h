#pragma once
class level
{
private:
	int Plevel;
	int exp;
	int statpoints;

public: 
	level();
	void gainexp(int amt);
	int getlevel();
	int getexp();
	int getstatpoints();
	bool levelup();
};

