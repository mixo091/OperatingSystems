#include "InvPgT.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

Pgentry::Pgentry(const int& pid, const int& pageNum, const bool& dirty) {
	this->pid = pid;
	this->pageNum = pageNum;
	this->dirty = dirty;
}

bool Pgentry::equals(const Pgentry& pgentry) const {
	return pageNum == pgentry.pageNum && pid == pgentry.pid;
}
//operator overloading
bool Pgentry::operator == (const Pgentry& pgentry) const {
	return this->equals(pgentry);
}

string Pgentry::toString() const {
	return to_string(pid)+" "+to_string(pageNum)+" "+to_string(dirty);
}

void Pgentry::print() const {
	cout << "Process:" << pid << ": requests page " << pageNum << " to "
		 << (dirty ? "W." : "R.") << endl;
}



//--------------------------------------------------------------------------------

//functions for InvPgT



InvPgT::InvPgT(const int& frames) {
	Size = frames;
	table = new Pgentry*[frames];
	for (int frame = 0 ; frame < frames ; frame++) {
		   table[frame] = NULL;
	}
}

InvPgT::~InvPgT() {
	for (int frame = 0 ; frame < Size ; frame++ ) {
		if (table[frame] != NULL) {
			delete table[frame];
		}
	}
	delete[] table;
}

//given a page return the frsme in which this page is
Pgentry **InvPgT::getFrame(const Pgentry & pgentry ) {
	for (int frame = 0 ; frame <Size ; frame++ ) {
		if (table[frame] != NULL && table[frame]->equals(pgentry)) {
			return &table[frame];
		}
	}
	return NULL;
}

//reutn first free frame 
Pgentry **InvPgT::getFreeFrame() {
	for (int frame = 0 ; frame < Size ; frame++ ) {
		if (table[frame] == NULL) {
			return &table[frame];
		}
	}
	return NULL;
}

void InvPgT::FillFrame(Pgentry **frame, Pgentry *pg) {
	*frame = pg;
}




void InvPgT::PrintTable() const {
	cout << "\n||InvertedPageTable||\n";
	for (int frame = 0 ; frame < Size ; frame++ ) {
		if (table[frame] == NULL) {
			cout << "NULL" << endl;
		}
		else {
			cout << table[frame]->toString() << endl;
		}
	}
}



Pgentry **InvPgT::getVictimFrameNotInSet(const list<Pgentry>& workingSet) {
	for (int frame = 0 ; frame < Size ; frame++) {
		if (find(workingSet.begin(), workingSet.end(), *table[frame]) == workingSet.end()) {
			return &table[frame];
		}
	}
	return NULL;
}
