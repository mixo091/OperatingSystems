#ifndef WS_H_
#define WS_H_
#define PROCESSES_NUM 2
#include <list>
#include "InvPgT.h"

class WorkingSet {

private:
	std::list<Pgentry> recentList;
	// Unique elements of recentList
	std::list<Pgentry> workingSet; 
	int SetSize;

public:
  //create working set
	WorkingSet(const int& Size) : SetSize(Size) {}
  //destructor
	~WorkingSet() {}
  //update workingSET

	void WS_Update(const Pgentry& pgentry, Pgentry **victim);
  //getting all the working set
	std::list<Pgentry>& get_WS();
	bool recentListIsFull() const;

};


/* Working set for each process */
class WS_Handler{
	friend class WorkingSet;

private:
	WorkingSet **workingSet;

public:
	WS_Handler(const int& SetSize);
	~WS_Handler();
  //given the pid of process retuRn the wotking set
	WorkingSet *GivePr_TakeSet(const int& pid);
};


#endif
