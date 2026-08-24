#pragma once
class level
{
private:
	int Plevel;
	int exp;

public: 
	level();
	void gainexp(int amt);
	int getlevel();
	int getexp();
	int getstatpoints();
	bool checklevelup();
};

