#include <stdio.h>
#include <stdlib.h>

#include "LinkedListAPI.h"
#include "PQueueAPI.h"
#include "patient.h"

List *initializeList(void (*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second)) {
  List *list = malloc(sizeof(List));
  list->printNode = printFunction;
  list->deleteNode = deleteFunction;
  list->compareNode = compareFunction;
  list->head = NULL;
  list->tail = NULL;
return list;
}

Node *initializeNode(List *list, void *data) {
  Node *n = malloc(sizeof(Node));
  n->data = data;
  n->next = NULL;
  n->previous = NULL;
  return n;
}

void insertFront (List *list, void *toBeAdded) {
  Node *toAdd = initializeNode(list, toBeAdded);
  Node *temp;

  /*if head of list is NULL then there is nothing in the list yet*/
  if (list->head == NULL) {
    list->head = toAdd;
    list->tail = toAdd;
  }
  else {
    temp = list->head;
    list->head = toAdd;

    list->head->next = temp;
    temp->previous = list->head;
    list->head->previous = NULL;
  }
}

void insertBack (List *list, void *toBeAdded) {
  Node *toAdd = initializeNode(list, toBeAdded);
  Node *temp;

  if (list->head == NULL) {
    list->head = toAdd;
    list->tail = toAdd;
  } else {
    temp = list->tail;
    list->tail = toAdd;

    list->tail->previous = temp;
    temp->next = list->tail;
    list->tail->next = NULL;
  }

}

void deleteList (List *listToDelete) {
  Node *currentNode = listToDelete->head;
  Node *nextNode;

  while (currentNode != NULL) {
    nextNode = currentNode->next;
    listToDelete->deleteNode(currentNode->data);
    free(currentNode);
    currentNode = nextNode;
  }
  listToDelete->head = NULL;
  free(listToDelete);
}

void printForwards (List *list) {
  Node *itr = list->head;

  while (itr != NULL) {
    list->printNode(itr->data);
    itr = itr->next;
  }

}

void printBackwards  (List *list) {
  Node *itr = list->tail;

  while (itr != NULL) {
    list->printNode(itr->data);
    itr = itr->previous;
  }
}


void *getFromFront (List *list) {
  if (list != NULL && list->head != NULL) {
    return list->head->data;
  }
  return NULL;
}

void *getFromBack (List *list) {
  if (list != NULL && list->tail != NULL) {
    return list->tail->data;
  }
  return NULL;
}

/*Deletes a node from the front of the list*/
void removeFromFront (List *list) {
  Node *currentNode = list->head;
  Node *nextNode;

  if (currentNode != NULL) {
    nextNode = currentNode->next;
    list->deleteNode(currentNode->data);
    free(currentNode);
    list->head = nextNode;
  }
  return;
}

/*deletes a node that could be anywhere in a list*/
void deleteNodeFromList (List *list, void *toBeDeleted) {

  if (list->head != NULL) {
    if (list->head->next != NULL) {
      Node *future = list->head->next;
      Node *pres = list->head;
      Node *prev = NULL;

      while (future != NULL) {
        if (list->compareNode(pres->data, toBeDeleted) == 0) {
          list->deleteNode(pres->data);
          free(pres);
          if (prev == NULL) {
            future->previous = NULL;
          }
          else if (future == NULL) {
            prev->next = NULL;
          } else {
            future->previous = prev;
            prev->next = future;
          }
          return;
        }
        prev = pres;
        pres = future;
        future = future->next;
      }
      if (list->compareNode(pres->data, toBeDeleted) == 0) {
        list->deleteNode(pres->data);
        free(pres);
        prev->next = future;
        return;
      }
    } else {
      if (list->compareNode(list->head->data, toBeDeleted) == 0) {
        list->deleteNode(list->head->data);
        free(list->head);
        list->head = NULL;
      }
    }
  }

return;
}

void insertSorted (List *list, void *toBeAdded) {
  Node *toAdd = initializeNode(list, toBeAdded);
  Node *tempNode;

  if (list->head == NULL) {
    list->head = toAdd;
    list->tail = toAdd;
  } else {
    tempNode = list->head;
    while (tempNode != NULL) {
      if (list->compareNode(toAdd->data, tempNode->data) != 1) {
        tempNode = tempNode->next;
      } else {
        toAdd->next = tempNode;
        toAdd->previous = tempNode->previous;
        if (tempNode->previous != NULL) {
          tempNode->previous->next = toAdd;
          tempNode->previous = toAdd;
        } else {
          list->head = toAdd;
          tempNode->previous = toAdd;
        }
        return;
      }
    }
  tempNode = list->tail;
  list->tail = toAdd;
  toAdd->previous = tempNode;
  toAdd->next = NULL;
  tempNode->next = toAdd;
  }

return;
}
