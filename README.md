# OS-Assignment-1
## Explanation
This code implements a producer-consumer problem using shared memory and semaphores. There are two C programs, producer.c and consumer.c, which use a shared buffer of size 2 to pass integer data between them. The producer produces random integers and adds them to the buffer, while the consumer consumes data from the buffer. The programs use semaphores to synchronize the access to the shared buffer and ensure that the buffer is not overfilled or empty. The code demonstrates the use of shared memory and semaphores for interprocess communication.
## How to compile in Linux
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &
