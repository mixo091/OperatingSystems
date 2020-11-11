#ifndef LRU_H_
#define LRU_H_

#include <list>
#include "InvPgT.h"


class LRU {

private:
	/* Keep most recent page requests at the front of the list.
	 * Last element is the least recently used. */
	std::list<Pgentry*> lruList;

public:
	LRU() {}
	~LRU() {}
	std::list<Pgentry*>& getLRUList() {return lruList;}
  //make it most recently used
	void makeItML(Pgentry*pgentry);
	Pgentry *getVictim();
	void printLIST() const;
};

#endif
