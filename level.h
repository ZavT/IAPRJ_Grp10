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
	int getexpneeded();
	bool checklevelup();

	//for restart
	void setlevel(int l);
	void setexp(int e);
};

