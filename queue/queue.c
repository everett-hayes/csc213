#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int val;
  struct node* next;
} node;

typedef struct queue_t {
  node* head;
  node* tail;
  int size;
} queue_t;

//function index
void initializeQueue(queue_t *q);
void add(queue_t *q, node* newNode);
node* poll(queue_t *q);
void printQueue(queue_t *q);

int main(int argc, char** argv) {

    //initialize our queue
    queue_t *q;
    q = malloc(sizeof(queue_t));
    initializeQueue(q);

    node* node1 = malloc(sizeof(node));
    node1->val = 1;

    node* node2 = malloc(sizeof(node));
    node2->val = 2;

    node* node3 = malloc(sizeof(node));
    node3->val = 3;

    node* node4 = malloc(sizeof(node));
    node4->val = 4;

    node* node5 = malloc(sizeof(node));
    node5->val = 5;

    add(q, node1);
    add(q, node2);
    add(q, node3);
    printQueue(q); // 1 2 3
    poll(q);    
    add(q, node4);
    add(q, node5);
    printQueue(q); // 2 3 4 5
    poll(q);
    poll(q);
     printQueue(q); // 4 5

    return 0;
}

void initializeQueue(queue_t *q) {
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

void add(queue_t *q, node* newNode) {

    q->size++; // we are adding a node increase the size

    // if the list is empty
    if (q->head == NULL && q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
        return;
    }

    // if the list has a single element
    if (q->head == q->tail) {
        q->tail = newNode;
        q->head->next = q->tail;
        return;
    }

    // if the list has many elements
    q->tail->next = newNode;
    q->tail = newNode;
}

node* poll(queue_t *q) {
    
    // if the list is empty
    if (q->head == NULL && q->tail == NULL) {
        return NULL;
    }

    // we are going to remove something, so decrement size
    q->size--;

    // if the list has a single element
    if (q->head == q->tail) {
        node* res = q->head;
        q->head = NULL;
        q->tail = NULL;
        return res;
    }

    // if the list has many elements
    node* res = q->head;
    q->head = q->head->next;
    return res;
}

void printQueue(queue_t *q) {

    node* curr = q->head;

    while (curr != NULL) {
        printf("%d", curr->val);
        curr = curr->next;
    }
    printf("\n");
}



