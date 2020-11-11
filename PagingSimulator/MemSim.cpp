#include "MemSim.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

MemSim::MemSim(const std::string& replacementAlgorithm, const int& frames_num, const int& frameSize,
		const int& q, const int& workingSetSize, const int& maxReferences) : table(frames_num) {
  this->pageRequests=0;
  this->pageFaults=0;
  this->diskWrites=0;
	this->replacementAlgorithm = replacementAlgorithm;
	this->frames_num = frames_num;
	this->frameSize = frameSize;
	this->q = q;
	this->workingSetSize = workingSetSize;
	this->maxRef = maxReferences;
	if (! replacementAlgorithm.compare("lru")) {
		lru = new LRU();
	}
	 else if (! replacementAlgorithm.compare("ws")) {
		wsHandler = new WS_Handler(workingSetSize);
	}
}

MemSim::~MemSim() {
	if (! replacementAlgorithm.compare("lru")) {
		delete lru;
	}
 else if (! replacementAlgorithm.compare("ws")) {
		delete wsHandler;
	}
}



void MemSim::StartSimulation() {
  //opening the files
  //and then start getting references
	ifstream file1;
	ifstream file2;
	file1.open("bzip.trace", ios::in);
	file2.open("gcc.trace", ios::in);

	bool  streamSwitch = false;
	//getting logical addesses
	Pgentry *pgentry;
	while ((pgentry= this->getRef(file1, file2, streamSwitch)) != NULL) {
		this->pageRequests++;
		pgentry->print();
		if (! replacementAlgorithm.compare("lru")) {
			this->LRUalgo(pgentry);
		}
		else if (! replacementAlgorithm.compare("ws")) {
			this->runWorkingSet(pgentry, streamSwitch);
		}
	}
	cout << "\nFrames: " << frames_num<< this->Results() << endl;

	//closing files
	file1.close();
	file2.close();

}

string MemSim::Results() const {
	return "\nPage requests: "+to_string(pageRequests)+"\nPage faults: "+to_string(pageFaults)
			+"\nDisk writes: "+to_string(diskWrites);
}

Pgentry *MemSim::getRef(ifstream& file1, ifstream& file2, bool& streamSwitch) {
	static int pid = 1;

	static int curQuantum = q;
	static int referenceNumber = 0;
	static istream *traceFile = &file1;
	string line;

	if (referenceNumber++ == maxRef || getline(*traceFile, line).eof()) {
		return NULL;
	}

	//getting the logical address and the indicator

	char *reference = new char[line.length()+1];
	strcpy(reference, line.c_str());
	char * logAddress = strtok(reference, " ");
	char *indicator = strtok(NULL, " \n\0");

	long decAddress = strtoul(logAddress, NULL, 16);
	int pageNumber = decAddress / frameSize;
	bool dirty = false;

  //if the indicator is 'w' the procees needs to be written to the disk when it will then
	//main memory so we mark at as dirty  in order to increase  the diskWrites


	if (*indicator == 'W') {
		dirty = true;
	}
	Pgentry *pgentry = new Pgentry(pid, pageNumber, dirty);
	delete[] reference;

	/* Mark start of a new process for working set restoration */
	if (curQuantum == q) {
		streamSwitch = true;
	}

	/* Switch trace between processes */
	if (! --curQuantum) {
    //reinitialize the  number of refs to get from a referencestream
		curQuantum = q;
    //change process and of course reference stream
		changeProcess(pid);
		changeRefStream(&traceFile, file1, file2);
	}
	return pgentry;
}










/* Update page in memory to WRITE if its current request is for WRITE */
void MemSim::UpdatePg(Pgentry *pgentry, Pgentry *citedentry) {
	if (pgentry->getDirty() == true && citedentry->getDirty() == false) {
		citedentry->setDirty(true);
		cout << "Page " << pgentry->getPageNum() << " from process " << pgentry->getPId()
		     << " changed to dirty" << endl;
	}
}












void MemSim::LRUalgo(Pgentry *pgentry){
  //find th frame of the given page
	Pgentry** Frame = table.getFrame(*pgentry);
	if (Frame != NULL) {
		/* Page already in memory */
		lru->makeItML(*Frame);
		//update page at the current frame if need be
		this->UpdatePg(pgentry, *Frame);
		delete pgentry;
	}
	else {
		/* Page not in memory */
		 this->pageFaults++;
		 Pgentry**freeFrame = table.getFreeFrame();
		if (freeFrame != NULL) {
			table.FillFrame(freeFrame, pgentry);
			lru->getLRUList().push_front(pgentry);
			cout << "Page fault on requesting page " << pgentry->getPageNum() << " from process "
					<< pgentry->getPId() << ".";
		}
		else {
			Pgentry *victim;
			victim = lru->getVictim();
			Pgentry **victimFrame = table.getFrame(*victim);
			table.FillFrame(victimFrame, pgentry);
			lru->getLRUList().push_front(pgentry);

			cout << " Memory full, replacing page " << victim->getPageNum() << " from process "
					<< victim->getPId() << ".";

			if (victim->getDirty()) {
				cout << " Saving victim to disk.";
				this->diskWrites++;
			}
			delete victim;
		}
		cout << endl;
	}

}












/* Switch process */
void MemSim::changeProcess(int& pid) {
	if (pid == 1) {
		pid = 2;
	}
	else {
		pid = 1;
	}
}

/* Switch input */
void MemSim::changeRefStream(istream **traceFile, ifstream& file1, ifstream& file2) {
	if (*traceFile == &file1) {
		*traceFile = &file2;
	}
	else {
		*traceFile = &file1;
	}
}


void MemSim::runWorkingSet(Pgentry *pgentry, bool& streamSwitch) {

	WorkingSet *workingSet = wsHandler->GivePr_TakeSet(pgentry->getPId());
	if (streamSwitch) {
		cout << "Restoring process " << pgentry->getPId() << " working set:" << endl;
		streamSwitch = false;
		bool change = false;
		this->SetBackToMem(workingSet->get_WS(), change);
		if (! change) {
			cout << "\tWorking set is already in memory" << endl;
		}
	}


	Pgentry *victimAddress = NULL;
	workingSet->WS_Update(*pgentry, &victimAddress);
	Pgentry **mappingFrame = table.getFrame(*pgentry);
	if (mappingFrame != NULL) {
		/* Page already in memory */
		this->UpdatePg(pgentry, *mappingFrame);
		delete pgentry;
	}


	else {
		/* Page not in memory */
		this->pageFaults++;
		Pgentry **freeFrame = table.getFreeFrame();
		if (freeFrame != NULL) {
			table.FillFrame(freeFrame, pgentry);
			cout << "Page fault on requesting page " << pgentry->getPageNum() << " from process "
					<< pgentry->getPId() << ".";


		}
		else {

			Pgentry **victimFrame;

			/* Remove a page not in working set, Prioritize the one just removed from working set */
			if (victimAddress != NULL) {
				victimFrame = table.getFrame(*victimAddress);
			}
			else {
				victimFrame = table.getVictimFrameNotInSet(workingSet->get_WS());
			}
			Pgentry *toDelete = *victimFrame;
			*victimFrame = pgentry;
			cout << "Page fault on requesting page " << pgentry->getPageNum() << " from process "
					<< pgentry->getPId() << ".";
			if (toDelete != NULL) {
				cout << " Memory full, replacing page " << toDelete->getPageNum() << " from process "
						<< toDelete->getPId() << ".";
      }
			if (toDelete->getDirty()) {
				cout << " Saving victim to disk.";
				this->diskWrites++;
			}
			delete toDelete;
		}
		cout << endl;
	}
	if (victimAddress != NULL) {
		delete victimAddress;
	}

}








void MemSim::SetBackToMem(std::list<Pgentry>& workingSet, bool& change) {


	for (list<Pgentry>::iterator it = workingSet.begin() ; it != workingSet.end() ; it++) {
		Pgentry **Frame = table.getFrame(*it);
		if (Frame == NULL) {
	   		this->pageFaults++;
			if (! change) {
				change = true;
			}
			Pgentry **Frame = table.getVictimFrameNotInSet(workingSet);
			Pgentry *toDelete = *Frame;
			*Frame = new Pgentry(*it);
			cout << "\t";
			cout << "Page fault on requesting page " << it->getPageNum() << " from process "
					<< it->getPId() << ".";
			if (toDelete != NULL) {
				cout << " Memory full, replacing page " << toDelete->getPageNum() << " from process "
						<< toDelete->getPId() << ".";
			}

			if (toDelete->getDirty()) {
				cout << " Saving victim to disk.";
				this->diskWrites++;
			}
			cout << endl;
			delete toDelete;
		}
	}
}
