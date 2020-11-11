
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/sem.h>
#include <math.h>
#include <time.h>

//#define NUMBER_OF_REPETITIONS 100
//#define PEERS 50
//#define ENTRIES 8



//the struct of the entry
struct entry{
int readings;
int writings;
};


int main(int argc ,char * argv[]){
int ENTRIES;
int PEERS;
int NUMBER_OF_REPETITIONS;
int percentOFreaders;
if(argc==5){
ENTRIES=atoi(argv[1]);
PEERS=atoi(argv[2]);
NUMBER_OF_REPETITIONS=atoi(argv[3]);
percentOFreaders=atoi(argv[4]);
//printf("%d  %d %d %d \n ", ENTRIES,PEERS,NUMBER_OF_REPETITIONS,percentOFreaders);
}else{
  printf("you are not giving the right number of arguments,try again\n");
  return 0;
}
//the array that keeps the pids of PEERS
int pid[PEERS];
int i;
int value;
//SHARED MEMORY
//INITIALIZING CREATING AND ATTACHING SHARED MEMORY SEGMENTS

//1) THE DATA BASE WITH THE ENTRIES
key_t entries_key;
entries_key = 567;
int  entries_id;
int  size=ENTRIES*sizeof(struct entry);
struct entry * entries;
//create the shared memory
if((entries_id = shmget(entries_key,size, IPC_CREAT|0600)) == -1){
              perror("shmget()");
              exit(EXIT_FAILURE);  }
if((entries= (struct entry *)shmat(entries_id, 0, 0)) == (struct entry *) -1){
              perror("shmat()");
              exit(EXIT_FAILURE);  }

//2)ARRAY OF COUNTERS THAT KEEP THE READERS CYRRENTLY AT AN ENTRY

key_t counters_key;
counters_key=123;
int  counters_id;
int* counters;


if((counters_id = shmget(counters_key,ENTRIES, IPC_CREAT|0600)) == -1){
                            perror("shmget()");
                            exit(EXIT_FAILURE);  }
if((counters = (int *)shmat(counters_id, 0, 0)) == (int *) -1){
                            perror("shmat()");
                            exit(EXIT_FAILURE);  }


//IN THIS PROGRAMM I USE POSIX UNANMED SEMAPHORES
//SO ARRAY OF SEMAPHORES WRT SHARED MEMORY SEGMENTS

key_t wrt_key;
wrt_key=155;
int  wrt_id;
int  size1=ENTRIES*sizeof(sem_t);
sem_t* wrt;
int retval;

if((wrt_id = shmget(wrt_key,size1, IPC_CREAT|0600)) == -1){
              perror("shmget()");
              exit(EXIT_FAILURE);  }
if((wrt = (sem_t *)shmat(wrt_id, 0, 0)) == (sem_t *) -1){
              perror("shmat()");
              exit(EXIT_FAILURE);  }






// ARRAY OF SEMAPHORES MUTEX SHARED MEMORY SEGMENTS

key_t mutex_key;
mutex_key=208;
int  mutex_id;
sem_t* mutex;
int retval2;

if((mutex_id = shmget(mutex_key,size1, IPC_CREAT|0600)) == -1){
                            perror("shmget()");
                            exit(EXIT_FAILURE);  }
if((mutex= (sem_t *)shmat(mutex_id, 0, 0)) == (sem_t *) -1){
                            perror("shmat()");
                            exit(EXIT_FAILURE);  }



//INITIALIZING VALUES OF COUNTERS AND SEMAPHORES

for(i = 0; i < ENTRIES; i++){
      entries[i].readings = 0;
      entries[i].writings = 0;
      counters[i] = 0;
      /*  Initialize  the  semaphore . */
      retval = sem_init (&wrt[i] ,1,1);

      if(retval != 0) {perror("Couldn’t initialize .");exit (3);}
      sem_getvalue(&wrt[i], &value);
    //  printf(" wrt %d is %d\n",i,value);
      retval2 = sem_init (&mutex[i] ,1,1);
      if(retval2 != 0) {perror("Couldn’t initialize .");exit (3);}
    }


//CREATING THE CHILDS THAT WILL EXEC THE PEER RROGRAMM
for(i = 0; i < PEERS; i++){
          pid[i] = fork();
          if(pid[i] < 0){
            printf("Error!\n");
            exit(1);
                      }
          //IF IT IS A CHILD
          if(pid[i] == 0){
        //  printf("PEER procces with process id : %d \n",getpid());

         char *args[]={"./peer",argv[1],argv[3],argv[4], NULL};
          execvp("./peer",args);

         exit(0);
                      }
                  }









//coordinator waiting the peers to finish and collect the data
for(i = 0; i < PEERS; i++){
waitpid(pid[i], NULL, 0);
                        }

//DESTROY THE SEMAPHORES

for(i = 0; i < ENTRIES; i++){
    // printf("%d  and and %d and  %d\n ",entries[i].readings ,entries[i].writings, counters[i]);
       sem_destroy (&wrt[i]);
       sem_destroy (&mutex[i]);
    }


    int Total_readings=0;
    int Total_writings=0;

    //scanning shared memory to print total reasults
     for(i = 0; i < ENTRIES; i++){
       Total_readings=Total_readings+entries[i].readings;
       Total_writings=Total_writings+entries[i].writings;
     }


     printf(" Coordinator scanned the shared memory and the results are :\n" );
     printf (" Total_readings-->>> %d \n Total_writings -->>> %d \n ",Total_readings,Total_writings);


    shmdt(counters);
    shmctl(counters_id, IPC_RMID, 0);

    shmdt(entries);
    shmctl(entries_id, IPC_RMID, 0);

    shmdt(mutex);
    shmctl(mutex_id, IPC_RMID, 0);


    shmdt(wrt);
    shmctl(wrt_id, IPC_RMID, 0);





















  return 0;
}
