
#ifndef MEMSIM_H_
#define MEMSIM_H_

#include <string>
#include <iostream>
#include <fstream>
#include "InvPgT.h"
#include "LRU.h"
#include "WS.h"


class MemSim{

private:
	std::string replacementAlgorithm;
	//results
  int pageRequests;
  int pageFaults;
  int diskWrites;

	int frames_num;
	int frameSize;
	int q;
	int workingSetSize;
	int maxRef;
	InvPgT table;
	LRU *lru;

	WS_Handler *wsHandler;

public:
	MemSim(const std::string& replacementAlgorithm, const int& frames_num, const int& frameSize,
			const int& q, const int& workingSetSize, const int& maxRef);
	~MemSim();
	std::string Results() const;
	void StartSimulation();
	void LRUalgo(Pgentry *pgentry);


	void runWorkingSet(Pgentry *pgentry, bool& streamSwitch);
	void UpdatePg(Pgentry *pgentry, Pgentry *citedentry);
	Pgentry *getRef(std::ifstream& file1, std::ifstream& file2, bool& streamSwitch);
	void SetBackToMem(std::list<Pgentry>& workingSet, bool& restore);
	void static changeProcess(int& processId);
	void static changeRefStream(std::istream **traceFile, std::ifstream& file1, std::ifstream& file2);
};

#endif
