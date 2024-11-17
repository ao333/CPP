#include "helper.h"
#include <string>

void* producer (void* id);
void* consumer (void* id);

int sem_id, queue_size, consume_index = 0, produce_index = 0;
JobStruct* queue;

int main (int argc, char** argv) {
  int cmd_input[4], empty_or_full = 0;

  // validate command line input
  for (int i = 1; i < argc; i++) {
    int int_input = check_arg(argv[i]);
    if (int_input == -1) {
      cout << "parameters not integers\n";
      return int_input;
    }
    cmd_input[i-1] = int_input;
  }

  // create and initialize the semaphore set
  sem_id = sem_create(SEM_KEY, 3);
  if(sem_id == -1) {
    cout << "semaphore not created\n";
    return -1;
  }

  queue_size = cmd_input[0];
  empty_or_full += sem_init(sem_id, 0, 1) + sem_init(sem_id, 1, 0) + sem_init(sem_id, 2, queue_size);

  if (empty_or_full < 0) {
    cout << "semaphore not initialized\n";
    return -1;
  }

  // initialize queue with an array size and all indicies with -1
  queue = new JobStruct[queue_size];
  for (int i = 0; i < queue_size; i++)
    queue[i].id = -1;

  int job_num = cmd_input[1], producer_num = cmd_input[2], consumer_num = cmd_input[3];

  // create threads for each producer and consumer
  pthread_t* producer_id = new pthread_t[producer_num];
  ProducerStruct* producer_attr = new ProducerStruct[producer_num];

  pthread_t* consumer_id = new pthread_t[consumer_num];
  int* consumer_attr = new int[consumer_num];

  // fill producer attributes
  for (int i = 0; i < producer_num; i++) {
    producer_attr[i].id = i + 1;
    producer_attr[i].capacity = job_num;
    pthread_create(producer_id + i, NULL, producer, (void *) (producer_attr + i));
  }

  for (int i = 0; i < consumer_num; i++) {
    consumer_attr[i] = i + 1;
    pthread_create(consumer_id + i, NULL, consumer, (void *) (consumer_attr + i));
  }

  // join threads after finishing
  for (int i = 0; i < producer_num; i++) {
    pthread_join (producer_id[i], NULL);
  }

  for (int i = 0; i < consumer_num; i++) {
    pthread_join (consumer_id[i], NULL);
  }

  sem_close(sem_id);

  delete[] queue;
  delete[] producer_id;
  delete[] producer_attr;
  delete[] consumer_id;
  delete[] consumer_attr;
  return 0;
}

void* producer (void* parameter) {
  ProducerStruct* producer_attr2 = (ProducerStruct*) parameter;
  int id = producer_attr2->id, produced_num = 0;

  while (produced_num < producer_attr2->capacity) {
    JobStruct job1;

    // set Job duration to 1 to 10 seconds
    job1.duration = rand() % 10 + 1;

    // wait if queue is full
    if (sem_wait(sem_id, 2) == -1) {
	  printf("Producer(%d): No more Job to generate\n", id);
	  pthread_exit (0);
  }
    // enter critical section
    sem_wait(sem_id, 0);
    for (int i = 0; i < queue_size; i++) {
      if (queue[(produce_index + i) % queue_size].id == -1) {
        produce_index = (produce_index + i) % queue_size;
        job1.id = produce_index;
        queue[produce_index] = job1;
        produce_index = (produce_index + 1) % queue_size;
        printf("Producer(%d): Job id %d duration %d\n", id, job1.id, job1.duration);
        break;
      }
    }
    // exit critical section

    sem_signal(sem_id, 0);
    sem_signal(sem_id, 1);

    // sleep for 1-5 seconds
    int sleep_duration = rand() % 5 + 1;
    sleep(sleep_duration);
    produced_num++;
  }
  printf("Producer(%d): No more Job to generate.\n", id);
  pthread_exit(0);
}

void* consumer (void* id) {
  int* consumer_id = (int*) id;

  while(1) {
    JobStruct job1;

    // set mutex to 1 if full
    if (sem_wait(sem_id, 1) == -1) {
    printf("Comsumer(%d): No more Job left.\n",*consumer_id);
	  pthread_exit (0);
	}
    // enter critical section
    sem_wait(sem_id, 0);
    for (int i = 0; i <queue_size; i++) {
      if (queue[(consume_index + i) % queue_size].id != -1) {
      consume_index = (consume_index + i) % queue_size;
      job1 = queue[consume_index];
      queue[consume_index].id = -1;
      consume_index = (consume_index + 1) % queue_size;
      break;
    }
	}
    // enter critical section
    sem_signal(sem_id, 0);
    sem_signal(sem_id, 2);
    printf("Comsumer(%d): Job id %d executing sleep duration %d\n", *consumer_id, job1.id, job1.duration);
    sleep(job1.duration);
    printf("Comsumer(%d): Job id %d completed\n", *consumer_id, job1.id);
  }
}
