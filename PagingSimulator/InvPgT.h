#ifndef INVPGT_H_
#define INVPGT_H_
#include "list"
#include <string>


//implementation of inverted page table

//------------------------------------------------------------------------------

//implenemtation of an address

class Pgentry {
private:
	int pid;
	int pageNum;
	bool dirty;

public:
	Pgentry(const int& pid, const int& pageNum, const bool& dirty);
	~Pgentry() {}
	bool getDirty() const {return dirty;}
	int getPId() const {return pid;}
	int getPageNum() const {return pageNum;}
	void setDirty(const bool& dirty) {this->dirty = dirty;}
	bool equals(const Pgentry& pgentry) const;
	bool operator == (const Pgentry& pgentry) const;
	std::string toString() const;
	void print() const;
};

//inverted page table
class InvPgT{

private:
	Pgentry** table;
	int Size;

public:
	InvPgT(const int& frames);
	~InvPgT();
	Pgentry **getFrame(const Pgentry& pgentry);
	Pgentry **getFreeFrame();
	Pgentry **getVictimFrameNotInSet(const std::list<Pgentry>& workingSet);
	void FillFrame(Pgentry **frame, Pgentry *content);
	void PrintTable() const;
};


#endif
