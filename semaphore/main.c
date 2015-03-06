#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <semaphore.h>

sem_t sem_obj;
// 
void *threadFunc1(void* args) {
  printf("inside thread func1\n");
  struct timespec ts;
  struct timeval now;

  while(1) {
    printf("in the loop!\n");
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec +=3;

    //gettimeofday(&now, NULL);
    //ts.tv_sec = now.tv_sec +5;
    //ts.tv_nsec = now.tv_usec;

    
    int err;
    if ((err = sem_timedwait(&sem_obj, &ts)) != 0) {
      printf("timedwait return error=%d\n", err);
    } else {
      printf("semaphore signaled.\n");
    }
  }
}

int main(int argc, char** argv) {
  printf("Hello World!\n");
  sem_init(&sem_obj, 0, 0);

  pthread_t thread;
  pthread_create(&thread, NULL, threadFunc1, NULL);

  while (1) {
    printf("hello!\n");
    getchar();
    sem_post(&sem_obj);
  }

  return 0;
}
