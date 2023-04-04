//Matthew Moore
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

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

    time_t randVar;
    srand((unsigned) time(&randVar));
    // Allocate shared memory
    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    struct table *sh = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    // Semaphores
    sem_t *full = sem_open(sFull, O_CREAT, 0666, 0);
    sem_t *empty = sem_open(sEmpty, O_CREAT, 0666, bSize); // bSize = 2
    sem_t *mutex = sem_open(sMutex, O_CREAT, 0666, 1);

    int i = 9; // Consumer should consume i times
    while(i--) {
        sem_wait(full); // Check table is full and check critical section
        sleep(rand()% 2 + 1);
        sem_wait(mutex);
        printf("consumed %d [%d]\n", sh->buffer[sh->out], sh->out);
        sh->out = (sh->out + 1) % bSize;
        
        sem_post(mutex);
        sem_post(empty);
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
    printf("Finished, enter to exit.");
    return 0;

}