#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "MemSim.h"
using namespace std;

#define FRAME_SIZE 4096


	int main(int argc, char* argv[]){
	    if(argc < 6){
	        printf("**ERROR** Invalid input. You must give the following: \n");
	        printf(" - Replacement Algorithm[LRU or WS]\n");
	        printf(" - Number of frames in memory[>0]\n");
	        printf(" - Number of references to be executed per step[>0]\n");
	        printf(" - Size of working set window[>0 if using WS algorithm]\n");
	        printf(" - Number of references in total, to be read from each file[>0]\n");
	        return -1;
	    }
      int frameSize=FRAME_SIZE;
	    char* algorithm = argv[1];
	    int FramesNum = atoi(argv[2]); // number of frames in memory
	    int q = atoi(argv[3]); // number of sets to read each step
	    int wsSize = atoi(argv[4]); // size of working set
	    int totalRefs = atoi(argv[5]); // total reference to be read from each file

	    if(strcmp(algorithm, "lru") && strcmp(algorithm, "ws")){
	        printf("**ERROR** Invalid input. Choose between LRU and WS algorithm! Abort.\n");
	        return -1;
	    }

	    if(FramesNum <= 0 || q <= 0 || (wsSize <= 0 && (!strcmp(algorithm, "ws"))) || totalRefs <= 0){
	        printf("**ERROR** Invalid input. Choose between LRU and WS algorithm! Abort.\n");
	        return -1;
	    }
	    else{
	        printf("**Program executed succesfully.**\n");
	        printf(" Given Parameters:\n");
	        if(!strcmp(algorithm, "ws"))
	            printf("  Replacement algorithm: %s with %d size of Working set\n",algorithm, wsSize);
	        else
	            printf("  Replacement algorithm: %s\n",algorithm);
	        printf("  Number Of memory frames: %d\n",FramesNum);
	        printf("  Number Of total references to read from each file: %d\n",totalRefs);
	        printf("\n--------------------------------------------------------------------\n\n");
	    }
	MemSim Mymem(algorithm,FramesNum , frameSize, q, wsSize, totalRefs );
	Mymem.StartSimulation();
}
