#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list = NULL;
  list = (List *) malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  
    return list;
}

void * firstList(List * list) {
  
  if (list->head == NULL)
  {
    return NULL;
  }
  
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {

  if (list == NULL || list->current == NULL || list->current->next == NULL)
  {
    return NULL;
  }

  list->current = list->current->next;
  
  return list->current->data;
}

void * lastList(List * list) {
  while (list->current->next != NULL)
    {
      list->current = list->current->next;
    }
  
  list->current = list->tail;
  
  return list->current->data;
}

void * prevList(List * list) {

  if (list == NULL || list->current == NULL || list->current->prev == NULL)
  {
    return NULL;
  }
  
  list->current = list->current->prev;
  
    return list->current->data;
}

void pushFront(List * list, void * data) {

  Node* nuevoNodo = createNode(data);
  
  if (list->head == NULL)
  {
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } 
  else 
  {
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
  
  return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {

  Node* nuevoNodo = createNode(data);

  if (list->current->next == NULL)
  {
    nuevoNodo->prev = list->current;
    list->current->next = nuevoNodo;
    list->tail = nuevoNodo;
  }
  else {
    nuevoNodo->prev = list->current;
    list->current->next->prev = nuevoNodo;
    list->current->next = nuevoNodo;
  }
  return;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  
  void * aux;

  if (list->current == NULL)
  {
    return NULL;
  }
  aux = list->current->data;
  
  if (list->head == list->current)
  {
    list->head = list->current->next;
    list->head->prev = NULL;
    
  } 
  else if (list->tail == list->current)
  {
    list->tail = list->current->prev;
    list->tail->next = NULL;
  } 
  else 
  {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
  }

  free(list->current);
  return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}