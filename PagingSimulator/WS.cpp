#include "WS.h"
#include <iostream>
#include <algorithm>
using namespace std;



void WorkingSet::WS_Update(const Pgentry& pgentry, Pgentry **victim) {
	if (this->recentListIsFull()) {
		*victim = new Pgentry(recentList.front());
		recentList.pop_front();
		if (find(recentList.begin(), recentList.end(), **victim) == recentList.end()) {
			workingSet.remove(**victim);
		}
		else {
			delete *victim;
			*victim = NULL;
		}
	}
	recentList.push_back(pgentry);
	if (find(workingSet.begin(), workingSet.end(), pgentry) == workingSet.end()) {
		/* No duplicates in working SET */
		workingSet.push_back(pgentry);
	}
}

list<Pgentry>& WorkingSet::get_WS() {
	return workingSet;
}

bool WorkingSet::recentListIsFull() const {
	return SetSize == recentList.size();
}



//initalizing working set for each process
WS_Handler::WS_Handler(const int& SetSize) {
	workingSet = new WorkingSet *[PROCESSES_NUM];
	for (int i = 0 ; i < PROCESSES_NUM ; i++) {
		workingSet[i] = new WorkingSet(SetSize);
	}
}

WS_Handler::~WS_Handler() {
	for (int i = 0 ; i < PROCESSES_NUM ; i++) {
		delete workingSet[i];
	}
	delete[] workingSet;
}
//given the pid of process retun the wotking set
WorkingSet *WS_Handler::GivePr_TakeSet(const int& pid) {
	return workingSet[pid-1];
}
