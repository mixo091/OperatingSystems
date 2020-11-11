#include "LRU.h"
#include <iostream>

using namespace std;

/* Remove specific Address and put at the front */
void LRU::makeItML(Pgentry *pgentry) {
	lruList.remove(pgentry);
	lruList.push_front(pgentry);
}

/* Remove and return victim Address found in the back */
Pgentry *LRU::getVictim() {
	Pgentry *victim = lruList.back();
	lruList.pop_back();
	return victim;
}

void LRU::printLIST() const {
	cout << "=== Recent List === " << endl;
	for (list<Pgentry *>::const_iterator it = lruList.begin() ; it != lruList.end() ; it++) {
		cout << (*it)->toString() << endl;
	}
}
