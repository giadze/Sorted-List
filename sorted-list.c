#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) 
{

  SortedListPtr sorted_list_ptr = malloc(sizeof(struct SortedList) + 1);

  sorted_list_ptr -> head = NULL;
  sorted_list_ptr -> cf = cf;
  sorted_list_ptr -> changeCount = 0;

  return sorted_list_ptr;

}



int SLInsert(SortedListPtr list, void *newObj)
{

  if (newObj == NULL) 
  {
    return 0;
  }

  list -> changeCount++;

/*if the list is empty*/
  if (list -> head == NULL) 
  {
    Node entry = malloc(sizeof(struct List) + 1); 
    entry -> data = newObj;
    entry -> next = NULL;
    list -> head = entry;

  } else {

    Node ptr = list -> head;

    if (list -> cf(list -> head -> data, newObj) < 0)
	 {
      Node entry = malloc(sizeof(struct List) + 1);  
      entry -> data = newObj;
      entry -> next = ptr;
      list -> head = entry;
      return 1;

    }

    while ((ptr -> next != NULL) && (list -> cf(ptr -> next -> data, newObj) > 0)) 
	 {
      ptr = ptr -> next;
    }

    Node entry = malloc(sizeof(struct List) + 1); 
    entry -> data = newObj;
    entry -> next = ptr -> next;
    ptr -> next = entry;

  }

  return 1;

}


int SLRemove(SortedListPtr list, void *newObj) 
{
  if (list -> head == NULL) 
  {
    return 0;
  }

/*if it gets this remove head*/
  else if ( (list -> cf(list -> head -> data, newObj)) == 0) 
  {
    Node toBeErased = list -> head;
    list -> head = list -> head -> next;
    free(toBeErased);

    list -> changeCount++;

    return 1;

  } else {

    Node prev = list -> head;
    Node curr = list -> head -> next;

    if (curr == NULL) 
	 {
      return 0;

    }

    while ((prev -> next != NULL) && (list -> cf(curr -> data, newObj) > 0))
    {
      prev = curr;
      curr = curr -> next;
    }

    if (list -> cf(curr -> data, newObj) == 0)
	 {

      prev -> next = curr -> next;
      free(curr);
      list -> changeCount++;

      return 1;

    } else {

      return 0;

    }
  }
}



void SLDestroy(SortedListPtr list) 
{

  Node ptr = list -> head;

  while (ptr != NULL) 
  {

    Node current = ptr;
    ptr = ptr -> next;
    free(current);

  }

  free(list);

  return;
}


void SLDestroyIterator(SortedListIteratorPtr iter) 
{

  free(iter);

  return;
}



/*helper*/
void adjust (SortedListIteratorPtr iter) 
{

  Node ptr = iter -> list -> head;

  if (ptr == iter -> ptr)
  {
    return;
  }


  while((ptr != NULL) && (iter -> list -> cf(ptr -> data, iter -> maxValue) >= 0))
  {
    ptr = ptr -> next;
  }

  iter -> ptr = ptr;

  return;

}



SortedListIteratorPtr SLCreateIterator(SortedListPtr list) 
{

  SortedListIteratorPtr iter = malloc(sizeof(struct SortedListIterator) + 1);
  iter -> list = list;
  iter -> ptr = list -> head;

  if (iter -> ptr == NULL)
  {
    iter -> maxValue = NULL;

  } else {

    iter -> maxValue = list -> head -> data;

  }

  iter -> changeCount = list -> changeCount;

  return iter;

}




void *SLNextItem(SortedListIteratorPtr iter) 
{

  if (iter -> changeCount != iter -> list -> changeCount) 
  {
    adjust(iter);
  }

  if(iter -> ptr == NULL)
  {
    return NULL;
  }


  void * nextItem = iter -> ptr -> data;
  iter -> ptr = iter -> ptr -> next;
  iter -> maxValue = nextItem;

  return nextItem;

}


void * SLGetItem(SortedListIteratorPtr iter)
{

	if(iter -> ptr -> data != NULL)
	{
		return iter -> ptr -> data;

	} else {
		
		return 0;

	}
}

