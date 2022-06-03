#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;

/*  Implement a Heap class here (from the slides)  */
class Heap {
  private:
    vector<int> data;
    int last_index;
  public:
    Heap() { last_index =- 1; };
   ~Heap() { };
    void InsertHeap(int newthing) {
      data.push_back(newthing);
      last_index++;

      if (last_index == 0) { return; }

      int child_index = last_index;
      int parent_index = 0;
      bool swapping = true;

      while (swapping == true) {
        swapping = false;

        if (child_index % 2 == 0) {
          // right
          parent_index = child_index / 2 - 1;
        } else {
          // left
          parent_index = child_index / 2;
        }

        if (parent_index >= 0 && data[child_index] > data[parent_index]) {
          swap(data[child_index], data[parent_index]);
          swapping = true;
          child_index = parent_index;
        }
      }
    };

    bool Delete(int item);
};

/* this is a possible prototype for the heapsort function */
/* the char* filename is just for printing the name, the file is opened and dealt with in the main() */
void heapsort(vector<int> &sortingvector,int number_of_elements, char* filename){
  use this -> "https://www.softwaretestinghelp.com/heap-sort/"

  /* Heap myHeap; .//declare a Heap instance here */
  /* Using the sortingvector, INSERT elements into the Heap */
  
  
  /* After building the heap from the file, PRINT the current state of the heap before sorting */
  /* STORE how many comparisons were made until this point */
  
  /* DELETE elements from the Heap, copying it back to the vector in a way that it is sorted */
  /* STORE how many comparisons were made for the deletion process */
  
  /* PRINT the number of comparisons for the Insert and Deletion tasks */
  
  /* Print the state of the vector after sorting */
  
}




int main(int argc, char** argv) {
	char expression[100];
	int number;
	ifstream input_file_random;
	ifstream input_file_reversed;
	ifstream input_file_sorted;
	
  if (argc == 4) {
	  input_file_random.open(argv[1]);
	  input_file_reversed.open(argv[2]);
	  input_file_sorted.open(argv[3]);
	} else {
	  printf("The program needs 3 filenames, in this order: random, reversed and sorted.\n");
    exit(0);
	}

	int number_of_elements_random = 0;

	while (input_file_random >> number) {
		sscanf(expression,"%d",&number);
		/*Comment out this printout, this is just to check that the file can be read */
    //		printf("%d ",number );	
		vector_random.push_back(number);
		number_of_elements_random++;
	}

	/*Comment out this printout, this is just to check that the array was copied */
	printf("File %s:\n", argv[1]);

	for (int count = 0; count < number_of_elements_random; count++) {
		printf("%d ",vector_random[count]);
	}
	printf("\n");
	/*end printout*/

	int number_of_elements_reversed = 0;
	while(input_file_reversed >> number) {
		sscanf(expression,"%d",&number);
		/*Comment out this printout, this is just to check that the file can be read */
//		printf("%d ",number );	
		vector_reversed.push_back(number);
		number_of_elements_reversed++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	printf("File %s:\n", argv[2]);
	for(int count=0;count<number_of_elements_reversed;count++){
		printf("%d ",vector_reversed[count]);
	}
	printf("\n");
	/*end printout*/


	int number_of_elements_sorted = 0;
	while(input_file_sorted >> number) {
		sscanf(expression,"%d",&number);
		/*Comment out this printout, this is just to check that the file can be read */
//		printf("%d ",number );	
		vector_sorted.push_back(number);
		number_of_elements_sorted++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	printf("File %s:\n", argv[3]);
	for(int count = 0; count < number_of_elements_sorted; count++){
		printf("%d ",vector_sorted[count]);
	}
	printf("\n");
	/*end printout*/


	/* Implement or call your Heap sort here, the Heap class with methods should be copied/implemented before main() */
	heapsort(vector_random, number_of_elements_random, argv[1]);
	cout << endl;
	heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
	cout << endl;
	heapsort(vector_sorted, number_of_elements_sorted, argv[3]);
	
}