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
//the struct of the entry
struct entry{
int readings;
int writings;
};

//GENERATING RANDOM EXP NUMBERS
double ran_expo(double lambda){
    double u;

    u = rand() / (RAND_MAX + 1.0);

    return -log(1- u) / lambda;
}

//#define NUMBER_OF_REPETITIONS 100
//#define ENTRIES 8
int RAND_R_W(int c, int w,int px, int py)
{
        // Generate a number from 1 to 100
        int r = rand() % 100 + 1;

        // r is smaller than px with probability px/100
        if (r <= px){
            return c;
        }
         // r is greater than px and smaller than or equal to px+py
         // with probability py/100
        else if  (r <= (px+py))
            {return w;}

        else{
          return 0;
        }


}

int main (int argc ,char * argv[]){
srand(time(NULL) * getpid());
double x;
int ENTRIES=atoi(argv[1]);
int NUMBER_OF_REPETITIONS=atoi(argv[2]);
int per_readers=atoi(argv[3]);
int per_writers=100-per_readers;
int i ,value;


double waiting_for_writing;
double waiting_for_reading;
double total_waiting_for_writing=0;
double total_waiting_for_reading=0;
//ATTACHING THE MEMORY SEGMENTS
key_t entries_key;
entries_key = 567;
int  entries_id;
int  size=ENTRIES*sizeof(struct entry);
struct entry * entries;
//create the shared memory
if((entries_id = shmget(entries_key,size, 0666)) == -1){
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


if((counters_id = shmget(counters_key,ENTRIES, 0666)) == -1){
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

if((wrt_id = shmget(wrt_key,size1, 0666)) == -1){
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

if((mutex_id = shmget(mutex_key,size1, 0666)) == -1){
                            perror("shmget()");
                            exit(EXIT_FAILURE);  }
if((mutex= (sem_t *)shmat(mutex_id, 0, 0)) == (sem_t *) -1){
                            perror("shmat()");
                            exit(EXIT_FAILURE);  }

//printf("procces %d  performing peer\n",getpid() );


      int times_to_read,times_to_write;
      times_to_read=0;
      times_to_write=0;
      for(i = 0; i < NUMBER_OF_REPETITIONS; i++){

            int random_selection=rand()%ENTRIES;
          //  printf("random_selection %d \n" ,random_selection);
            if(RAND_R_W(0,1,per_writers,per_readers)==0){
             clock_t begin = clock();

             times_to_write++;
             //printf("  and wrt  %d is %d\n",random_selection,value);
             sem_wait(&wrt[random_selection]);
             clock_t end = clock();
             //printf("peer:%d  is a writing on  for entry :%d \n",getpid(),random_selection );
          //   printf("Peer #%d acquired. Sleeping afte writing Entry %d \n", getpid(),random_selection);
             x=1000*ran_expo(0.5);
             usleep(x);
            // sem_getvalue(&wrt[random_selection], &value);
            // printf("  and wrt  %d is %d\n",random_selection,value);
             entries[random_selection].writings++;
             sem_post(&wrt[random_selection]);
            // printf("peer:%d  is out they can write now in entry:%d  \n",getpid(),random_selection );

            waiting_for_writing = (double)(end - begin)/ CLOCKS_PER_SEC;
            total_waiting_for_writing=total_waiting_for_writing+waiting_for_writing;


            }else{
            times_to_read++;
            clock_t begin = clock();
            sem_wait(&mutex[random_selection]);

            counters[random_selection]++;
            if(counters[random_selection]==1){
              sem_wait(&wrt[random_selection]);
               sem_getvalue(&wrt[random_selection], &value);
               //printf("  and wrt  %d is %d\n",random_selection,value);
             }

               sem_post(&mutex[random_selection]);


            //critical section
            //printf("peer %d  is a reading on repetition number %d  for entry %d \n",getpid(),i,random_selection );
          //  printf("Peer #%d acquired. Sleeping after reading at Entry %d\n", getpid(),random_selection);
            //sleep(1);
            clock_t end = clock();
            x=1000*ran_expo(0.5);
            usleep(x);
            entries[random_selection].readings++;


            sem_wait(&mutex[random_selection]);
            //printf("reader in entry %d  so --\n",random_selection );
              counters[random_selection]--;
              if (counters[random_selection]==0){
                  //printf(" no readers in entry %d so  writes allowed \n",random_selection );
                sem_post(&wrt[random_selection]);

              }

                 sem_post(&mutex[random_selection]);

            waiting_for_reading=(double)(end - begin)/ CLOCKS_PER_SEC;
            total_waiting_for_reading=total_waiting_for_reading+waiting_for_reading;

            }

          }


double average_waiting_for_reading=total_waiting_for_reading/times_to_read;
double average_waiting_for_writing=total_waiting_for_writing/times_to_write;


printf("Peer with process id->%d total readings -> %d\n",getpid(),times_to_read );
printf("Peer with process id ->%d total writings-> %d\n",getpid(),times_to_write );
printf("Peer with process id ->%d average_waiting_for_reading -> %f sec\n",getpid(),average_waiting_for_reading );
printf("Peer with process id ->%d average_waiting_for_writing-> %f sec \n",getpid(),average_waiting_for_writing );




//DETACHING THE MEMORY SEGMENTS
shmdt(counters);
shmdt(entries);
shmdt(mutex);
shmdt(wrt);





  return 0;
}
