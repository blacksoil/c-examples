#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

pthread_mutex_t lock;
pthread_cond_t cond;

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

    pthread_mutex_lock(&lock);
    int err;
    if ((err = pthread_cond_timedwait(&cond, &lock, &ts)) != 0) {
      printf("timedwait return error=%d\n", err);
    } else {
      printf("cond wait signale.\n");
    }
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char** argv) {
  printf("Hello World!\n");
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_t thread;
  pthread_create(&thread, NULL, threadFunc1, NULL);

  while (1) {
    printf("hello!");
    getchar();
    pthread_cond_signal(&cond);
  }

  pthread_join(thread, NULL);
  return 0;
}
