#include "sorted-list.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Initialize a sorted list.
 *
 * \param lst This is a pointer to space that should be initialized as a sorted list. The caller of
 * this function retains ownership of the pointed-to memory.
 */
void sorted_list_init(sorted_list_t *lst) {
  lst->front = NULL;
}

/**
 * Destroy a sorted list.
 *
 * \param lst This is a pointer to the space that holds the list being destroyred. This function
 * should free any memory used to represent the list, but the caller retains ownership of the lst
 * pointer itself.
 */
void sorted_list_destroy(sorted_list_t *lst) {

  while (lst->front != NULL) {
      node* temp = lst->front;
      lst->front = lst->front->next;
      free(temp);
  }

}

/**
 * Add an element to a sorted list, maintaining the lowest-to-highest sorted value.
 *
 * \param lst   The list that is being inserted to
 * \param value The value being inserted
 */
void sorted_list_insert(sorted_list_t *lst, int value) {

  node* newNode = malloc(sizeof(node));
  newNode->data = value;
  newNode->next = NULL;
  
  //if the lst is empty or I am smaller than front node
  if (lst->front == NULL || lst->front->data >= value) {
    newNode->next = lst->front;
    lst->front = newNode;
  } else { 
    //iterate through the list until I find the node before the designated location

    node* curr = lst->front;

    while (curr->next != NULL && curr->next->data < value) {
      curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
  }

}

/**
 * Count how many times a value appears in a sorted list.
 *
 * \param lst The list being searched
 * \param value The value being counted
 * \returns the number of times value appears in lst
 */
size_t sorted_list_count(sorted_list_t *lst, int value) {
  int count = 0;

  node* curr = lst->front;

  while (curr != NULL && value >= curr->data) {

    if (curr->data == value) {
      count++;
    }
    
    curr = curr->next;
  }

  return count;
}

/**
 * Print the values in a sorted list in ascending order, separated by spaces and followed by a
 * newline.
 *
 * \param lst The list to print
 */
void sorted_list_print(sorted_list_t* lst) {
  node* curr = lst->front;

  while (curr != NULL) {
    printf("%d", curr->data);
    curr = curr->next;

    if(curr != NULL) printf(" ");
  }

  printf("\n");

}
