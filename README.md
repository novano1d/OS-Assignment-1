# OS-Assignment-1
## Explanation
This code implements a producer-consumer problem using shared memory and semaphores. There are two C programs, producer.c and consumer.c, which use a shared buffer of size 2 to pass integer data between them. The producer produces random integers and adds them to the buffer, while the consumer consumes data from the buffer. The programs use semaphores to synchronize the access to the shared buffer and ensure that the buffer is not overfilled or empty. The code demonstrates the use of shared memory and semaphores for interprocess communication.
## How to compile and run in Linux
```
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &
```
## Example output
In this example, there are 9 items produced and 9 items consumed. This could be modified in the code.
```
produced 36 [0]
produced 11 [1]
consumed 36 [0]
consumed 11 [1]
produced 42 [0]
consumed 42 [0]
produced 2 [1]
produced 9 [0]
consumed 2 [1]
produced 12 [1]
consumed 9 [0]
consumed 12 [1]
produced 41 [0]
consumed 41 [0]
produced 42 [1]
produced 38 [0]
consumed 42 [1]
consumed 38 [0]
Finished, enter to exit.
[1]-  Done                    ./producer
[2]+  Done                    ./consumer
``` 
