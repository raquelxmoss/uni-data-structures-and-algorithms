#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

struct Node {
  int data;
  Node *next;
};

class Queue {
  private:
    Node *front, *rear;
    int length;
  public:
    Queue() {
      length = 0;
      front = NULL;
      rear = NULL;
    };

    ~Queue() { };

    void Join(int new_item) {
      length++;
      Node *temp;
      temp = new Node;
      temp->data = new_item;
      temp->next = NULL;

      if (rear != NULL) { rear->next = temp; }
      rear = temp;
      if (front == NULL) { front = temp; }
    };

    void Leave() {
      if (isEmpty()) { return; }
      length--;

      Node * temp;
      if (front == NULL) { return; }
      temp = front;
      front = front->next;
      if (front == NULL) { rear = NULL; }
      delete temp;
    };

    int Front() {
      return front->data;
    };

    int Length() {
      return length;
    }

    bool isEmpty() {
      if (front == NULL) { return true; }
      return false;
    };
};

#define TIMEDELAY 3 //DO NOT CHANGE THIS VALUE!!!
#define N 128 //DO NOT CHANGE THIS VALUE!!!

int MaximumCongestionTotals[N];
int OutputQueuesCurrentTotals[N];

Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation(){
  for(int a = 0; a < N; a++) {
    OutputQueuesCurrentTotals[a] = 0;
    MaximumCongestionTotals[a] = 0;
  }
}

int sum_array(int array[]) {
  int sum = 0;
  for(int a = 0; a < N; a++) {
    sum = sum + array[a];
  }
  return sum;
}

int number_of_ports = 0;

int main(int argc, char** argv) {
  int portnumber = 0;
  string expression;
  string geninput;
  ifstream input_file;

  if (argc != 2) {
    cout<< "Type a file name. " << endl << argv[1] << endl;
    exit(0);
  }

  // read input file contents
  input_file.open(argv[1]);

  if (!input_file.is_open()) {
    cout << "Could not read file: " << endl << argv[1] << endl;
    exit(0);
  }

  string token;

  while (!input_file.eof()) {
    getline(input_file, expression);
    stringstream line(expression);

    if (input_file.eof()) break;
    if (expression[0] =='#') continue;
    if (expression[0] =='P') {
      getline(line, token, ' ');
      getline(line, token, ' ');
      number_of_ports = atoi(token.c_str());
      continue;
    }

    // move this to the end of the while loop
    portnumber++;

    while (getline(line, token,' ')) {
      int input_char;
      input_char = atoi(token.c_str());

      if (input_char < 0 || input_char > number_of_ports || number_of_ports < portnumber) {
        cout << "ERROR in the format of the text file" << endl;
        exit(0);
      }

      InputQueues[portnumber - 1].Join(input_char);
    }
  }
  // end reading input file contents

  //cout << endl << "Start of the simulation, press a key " << endl << endl;
  //getline(cin, geninput);

  init_simulation();
  unsigned long int clock = 0;
  unsigned long int OutputQueuesCurrentTotalsSum = 99999999;
  portnumber = 0;

  while (OutputQueuesCurrentTotalsSum > 0) {
    // portnumber code is chaotic but I'm not changing it
    portnumber++;
    if (portnumber > (number_of_ports-1)) portnumber = 0;

    Queue & input_queue = InputQueues[portnumber - 1];

    if (!input_queue.isEmpty()){
      int output_queue_index = input_queue.Front() - 1;
      int value_to_move = input_queue.Front();

      Queue & output_queue = OutputQueues[output_queue_index];
      
      // join the output queue
      output_queue.Join(value_to_move);

      // update the current total for the output queue.
      OutputQueuesCurrentTotals[output_queue_index] = output_queue.Length();

      // leave the input queue
      input_queue.Leave();
    }

    clock++;

    if (clock % (TIMEDELAY*number_of_ports) == 0 && clock != 0) { //DO NOT MODIFY THIS LINE!
      for(int a = 0; a < number_of_ports; a++) {
        // Delete 1 packet from each queue
        OutputQueues[a].Leave();
        // Update the queue's current total
        OutputQueuesCurrentTotals[a] = OutputQueues[a].Length();
      }
    }

    // update the current totals of the output queues
    OutputQueuesCurrentTotalsSum = sum_array(OutputQueuesCurrentTotals);

    // are the current totals larger than what we currently have recorded?
    // if so, let's update the maximum totals
    if (OutputQueuesCurrentTotalsSum > sum_array(MaximumCongestionTotals)) {
      for (int a = 0; a < number_of_ports; a++) {
        cout << "clock" << clock << endl;
        cout << "updading maximum congestion" << endl;
        cout << "output queue (0 index): " << a << endl;
        cout << "total: " << OutputQueuesCurrentTotals[a] << endl;
        
        MaximumCongestionTotals[a] = OutputQueuesCurrentTotals[a];
      }
    }
  }

  for (int a = 0; a < number_of_ports; a++) {
    cout << "output port " << a+1 << ": " << MaximumCongestionTotals[a] << " packets" << endl;
  }
}
