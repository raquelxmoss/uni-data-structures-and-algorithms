#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;

class Heap {
  private:
    vector<int> data;
    int last_index;
    int insert_comparisons;
    int delete_comparisons;

  public:
    Heap() {
      last_index = -1;
      insert_comparisons = 0;
      delete_comparisons = 0;
    };

    ~Heap(){};

    int get_insert_comparisons() {
      return insert_comparisons;
    }

    int get_delete_comparisons() {
      return delete_comparisons;
    }

    int get_root() {
      return data[0];
    }

    void print_heap() {
      for (int i = 0; i < data.size(); i++) { cout << data[i] << " "; }
    }

    void insert_heap(int newthing) {
      data.push_back(newthing);
      last_index++;

      if (last_index == 0) { return; }

      int child_index = last_index;
      int parent_index = 0;
      bool swapping = true;

      while (swapping == true) {
        swapping = false;

        if (child_index % 2 == 0) {
          parent_index = child_index / 2 - 1;
        } else {
          parent_index = child_index / 2;
        }

        if (parent_index >= 0) {
          insert_comparisons++;
          if (data[child_index] > data[parent_index]) {
            swap(data[child_index], data[parent_index]);
            swapping = true;
            child_index = parent_index;
          }
        }
      }
    };

    void delete_root() {
      if (last_index < 0) { return; }

      data[0] = data[last_index];
      data[last_index] = 0;
      last_index--;

      int parent_index = 0;
      int left_index = parent_index * 2 + 1;
      int right_index = parent_index * 2 + 2;

      if (!data[left_index] && !data[right_index]) {
        // no comparison
      } else if (data[left_index] && data[right_index]) {
        // data at both left and right
        delete_comparisons += 2;
      } else {
        delete_comparisons++;
      }

      while (data[parent_index] < data[left_index] || data[parent_index] < data[right_index]) {
        if (data[right_index] < data[left_index]) {
          swap(data[left_index], data[parent_index]);
          parent_index = left_index;
        } else {
          swap(data[right_index], data[parent_index]);
          parent_index = right_index;
        }

        left_index = parent_index * 2 + 1;
        right_index = parent_index * 2 + 2;

        if (left_index > last_index) { break; }

        if (!data[left_index] && !data[right_index]) {
          // no comparison
        } else if (data[left_index] && data[right_index]) {
          // data at both left and right
          delete_comparisons += 2;
        } else {
          delete_comparisons++;
        }

        if (right_index > last_index && data[parent_index] < data[left_index]) {
          swap(data[parent_index], data[left_index]);
          break;
        }
      }
    }
};

void heapsort(vector<int> &sortingvector, int number_of_elements, char *filename) {
  Heap heap;

  for (int i = 0; i < number_of_elements; i++) { heap.insert_heap(sortingvector[i]); }

  cout << "Heap before sorting: " << filename << endl;
  heap.print_heap();
  cout << endl;

  int insert_comparisons = heap.get_insert_comparisons();
  cout << "InsertHeap: " << insert_comparisons << " comparisons" << endl;

  for (int i = (number_of_elements - 1); i >= 0; i--) {
    sortingvector[i] = heap.get_root();
    heap.delete_root();
  }

  int delete_comparisons = heap.get_delete_comparisons();
  cout << "DeleteRoot: " << delete_comparisons << " comparisons" << endl;
  cout << "Vector after sorting:" << endl;

  for (size_t i = 0; i < number_of_elements; i++) { cout << sortingvector[i] << " "; }
  cout << endl;
}

int main(int argc, char **argv) {
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
    sscanf(expression, "%d", &number);
    vector_random.push_back(number);
    number_of_elements_random++;
  }

  int number_of_elements_reversed = 0;
  while (input_file_reversed >> number) {
    sscanf(expression, "%d", &number);
    vector_reversed.push_back(number);
    number_of_elements_reversed++;
  }

  int number_of_elements_sorted = 0;
  while (input_file_sorted >> number) {
    sscanf(expression, "%d", &number);
    vector_sorted.push_back(number);
    number_of_elements_sorted++;
  }

  heapsort(vector_random, number_of_elements_random, argv[1]);
  cout << endl;
  heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
  cout << endl;
  heapsort(vector_sorted, number_of_elements_sorted, argv[3]);
}
