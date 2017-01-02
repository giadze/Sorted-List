#include	<string.h>
#include	"sorted-list.h"

/*fun begins*/
int compareInts(void *p1, void *p2)
{

	int int1 = *(int*)p1;
	int int2 = *(int*)p2;

	return int1 - int2;
}


int compareDoubles(void *p1, void *p2)
{

	double double1 = *(double*)p1;
	double double2 = *(double*)p2;

	return (double1 < double2) ? -1 : ((double1 > double2) ? 1 : 0);

}


int compareStrings(void *p1, void *p2)
{

	char *char1 = p1;
	char *char2 = p2;

	return strcmp(char1, char2);

}



void destroyBasic(void *p)
{
	return;
}




int main()
{

/*create*/
  SortedListPtr sorted_list_ptr = SLCreate(&compareInts, destroyBasic);

/*allocate space for the numbers*/
  int * bar;
  int * int1 = malloc (sizeof(int*));
  int * int2 = malloc (sizeof(int*));
  int * int3 = malloc (sizeof(int*));
  int * int4 = malloc (sizeof(int*));
  int * int5 = malloc (sizeof(int*));

/*declare some integers*/
  * int1 = 7;  
  * int2 = 15; 
  * int3 = 5;  
  * int4 = 10; 
  * int5 = 16;


  printf("Case 1: Building List\n");

/*inserting declared integers*/
  SLInsert(sorted_list_ptr, int1);
  SLInsert(sorted_list_ptr, int2);
  SLInsert(sorted_list_ptr, int3);
  SLInsert(sorted_list_ptr, int4);

  SortedListIteratorPtr sorted_iterator_ptr = SLCreateIterator(sorted_list_ptr);
  

/*start a bunch of do statements get items until null is encountered*/  
  do
  {

    bar = SLNextItem(sorted_iterator_ptr);

    if (bar == NULL) 
	 {
      break;

    }

    printf("%d\n", *bar);

  } while (bar != NULL);

/*lets try removing and testing if the list remains sorted*/
  printf("\n");
  printf("Case 2: Removing from list\n");

  SortedListIteratorPtr sorted_iterator_ptr2 = SLCreateIterator(sorted_list_ptr);

  SLRemove(sorted_list_ptr, int4);
  


  do
  {

    bar = SLNextItem(sorted_iterator_ptr2);
	
    if (bar == NULL) 
	 {
      break;
    }

    printf("%d\n", *bar);

  } while (bar != NULL);



  printf("\n");
  printf("Case 3: Adjusting middle\n");

/*compare and insert appropriately after either removing or adding the middle*/ 
  SortedListPtr sorted_list_ptr2 = SLCreate(&compareInts, destroyBasic);

/*inserting*/
  SLInsert(sorted_list_ptr2, int1);
  SLInsert(sorted_list_ptr2, int2);
  SLInsert(sorted_list_ptr2, int3);
  SLInsert(sorted_list_ptr2, int4);


  SortedListIteratorPtr sorted_iterator_ptr3 = SLCreateIterator(sorted_list_ptr2);

  bar = SLNextItem(sorted_iterator_ptr3);

  printf("%d\n", *bar);

  printf("\n");
  printf("Removed 10\n");


  SLRemove(sorted_list_ptr2, int4);
  printf("\n");
  printf("Added 16\n");

  SLInsert(sorted_list_ptr2, int5);



  do
  {

    bar = SLNextItem(sorted_iterator_ptr3);

    if (bar == NULL) 
	 {
      break;
    }

    printf("%d\n", *bar);

  } while (bar != NULL);


  printf("\n");
  printf("Iterate the entire list\n");

  SortedListIteratorPtr sorted_iterator_ptr4 = SLCreateIterator(sorted_list_ptr2);


/*now iterate the entire list*/
  do
  {

    bar = SLNextItem(sorted_iterator_ptr4);

    if (bar == NULL) 
	 {
      break;
    }

    printf("%d\n", *bar);

  } while (bar != NULL);


  printf("\n");
  printf("Case 4: Empty list iteration after removing\n");

  SortedListPtr sorted_list_ptr3  = SLCreate(&compareInts, destroyBasic);
  SLRemove(sorted_list_ptr3, int1);

  SortedListIteratorPtr sorted_iterator_ptr5 = SLCreateIterator(sorted_list_ptr3);



  do
  {

    bar = SLNextItem(sorted_iterator_ptr5);

    if (bar == NULL) 
	 {
      break;
    }

    printf("%d\n", *bar);

  } while (bar != NULL);
  

/*testing some strings*/
  printf("\n");
  printf("Case 5: Testing strings\n");

/*allocate memory for them*/
  char * string1 = malloc(sizeof(char) * 5);
  char * string2 = malloc(sizeof(char) * 5);
  char * string3 = malloc(sizeof(char) * 5);

/*create them*/
  strcpy(string1, "hello\0"); 
  strcpy(string2, "mr/ms\0");  
  strcpy(string3, "grader\0"); 



  printf("%s\n", string1);

/*compare and insert strings*/
  SortedListPtr sorted_list_ptr4 = SLCreate(&compareStrings, destroyBasic);

  SLInsert(sorted_list_ptr4, string1);

  SortedListIteratorPtr sorted_iterator_ptr6 = SLCreateIterator(sorted_list_ptr4);




  char *pointer = SLNextItem(sorted_iterator_ptr6);

  printf("%s\n", pointer);


/*get rid of junk*/ 
  SLDestroy(sorted_list_ptr);
  SLDestroy(sorted_list_ptr2);
  SLDestroy(sorted_list_ptr3);
  SLDestroyIterator(sorted_iterator_ptr5);
  SLDestroyIterator(sorted_iterator_ptr3); 
  SLDestroyIterator(sorted_iterator_ptr4); 
  SLDestroyIterator(sorted_iterator_ptr2);
  SLDestroyIterator(sorted_iterator_ptr);
  free(int1);
  free(int2);
  free(int3);
  free(int4);
  free(int5);
}
