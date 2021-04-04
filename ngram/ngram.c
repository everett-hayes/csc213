#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* back;
    int size;
    int capacity;
} queue;

//function index
void initializeQueue(queue *q, int capacity);
void moveQueue(queue *q, char c);
void destroyQueue();
void printQueue();

int main(int argc, char** argv) {

  //Make sure the program is run with an N parameter
  if (argc != 2) {
    fprintf(stderr, "Usage: %s N (N must be >= 1)\n", argv[0]);
    exit(1);
  }

  // Convert the N parameter to an integer hello
  int N = atoi(argv[1]);

  // Make sure N is >= 1
  if (N < 1) {
    fprintf(stderr, "Invalid N value %d\n", N);
    exit(1);
  }

  //initialize our queue
  queue *q;
  q = malloc(sizeof(queue));
  initializeQueue(q, N);

  int count = 0;
  char ch = fgetc(stdin);
  //loop through stdin moving along our queue window
  while (ch != EOF) {
    count++;
    moveQueue(q, ch);
    ch = fgetc(stdin);
  }

  //print the final queue if size requirements are met
  if (count >= N) printQueue(q->front);

  //free all memory associated with queue 
  destroyQueue(q);

  return 0;
}

void initializeQueue(queue *q, int capacity) {
  q->size = 0;
  q->capacity = capacity;
  q->front = NULL;
  q->back = NULL;
}

void printQueue(node *front) {

  if (front == NULL) {
    printf("\n");
  } else {
    printf("%c", front->data);
    printQueue(front->next);
  }

}

void destroyQueue(queue *q) {
  
  while (q->front != NULL) {
      node* temp = q->front;
      q->front = q->front->next;
      free(temp);
  }

  free(q);

}

/*
This function moves our queue window along the stdin

if the queue is empty 
  add a new node to the back
if the queue is not empty
  if the queue is not yet full 
    add a new node to the back
  if the queue is full it will do the following
    print the queue
    make a new node
    add that node to the back
    remove & free the front 
*/
void moveQueue(queue *q, char c) {

  //empty queue case
  if (q->size == 0) {

    //add the node on
    node* newNode;
    newNode = malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;

    q->front = newNode;
    q->back = newNode;
    q->size++;

    return;
  }

  //non-empty queue case
  if (q->size < q->capacity) {

    //create a new node
    node* newNode;
    newNode = malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;

    //stick the new node at the back
    q->back->next = newNode;
    q->back = newNode;
    q->size++;

  } else {

    //print the current queue
    printQueue(q->front);
    
    //create the new last element
    node* newNode;
    newNode = malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;

    //stick the new node at the back
    q->back->next = newNode;
    q->back = newNode;

    //remove & free the front element
    node *tmp;
    tmp = q->front;
    q->front = q->front->next;
    free(tmp);

  }

}
