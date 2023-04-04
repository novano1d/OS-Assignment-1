//Matthew Moore
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

static const char* sEmpty = "empty";
static const char* sMutex = "mutex";
static const char* sFull = "full";
static const char* NAME = "PC";

static const int bSize = 2;
struct table {   // Table is size 2
    int buffer[2];
    int in;
    int out;
};

static const int SIZE = sizeof(struct table);

int main() {
    int num = 0;
    time_t randVar;
    srand((unsigned) time(&randVar));
	int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666); //allocate the shared memory
    ftruncate(fd, SIZE);
    struct table *sh = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    // Semaphores
    sem_t *full = sem_open(sFull, O_CREAT, 0666, 0);
    sem_t *empty = sem_open(sEmpty, O_CREAT, 0666, bSize);
    sem_t *mutex = sem_open(sMutex, O_CREAT, 0666, 1);
    int i = 9; // Producer should produces i times
    while(i--) {
        sem_wait(empty);
        sleep(rand()% 2 + 1);
        sem_wait(mutex);
        //random number put in buffer
        num = rand() % 50;
        sh->buffer[sh->in] = num;
        printf("produced %d [%d]\n", sh->buffer[sh->in], sh->in);
        sh->in = (sh->in + 1) % bSize; // 0 when max size
        sem_post(mutex); // Lock
        sem_post(full);  // Decrement full s
    }
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);
    sem_unlink(sFull);
    sem_unlink(sEmpty);
    sem_unlink(sMutex);
    munmap(sh, SIZE);
    close(fd);
    shm_unlink(NAME);
    return 0;
}