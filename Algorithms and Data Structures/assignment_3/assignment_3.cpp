// Raquel Moss
// ID: 22001105
// Hello!
// Thank you for marking my assignment.
// You might notice some changes to the skeleton code, and a few quirks in how I write things.
// In my day job, I'm a software developer working with higher-level languages (mostly Ruby
// and JavaScript). I'm accustomed to some naming and style conventions through my work, so
// you might see them here.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

// Queues are FIFO

struct Node {
  float data;
  Node *next;
};

class Queue {
  private:
    Node *front, *rear;
    int length;
  public:
    Queue() {
      front = NULL;
      rear = NULL;
    };

    ~Queue() { };

    // place a new item at the rear of the queue
    void Join(float new_item) {
      Node *temp;
      temp = new Node;
      temp->data = new_item;
      temp->next = NULL;

      if (rear != NULL) { rear->next = temp; }
      rear = temp;
      if (front == NULL) { front = temp; }

      length++;
    };

    // remove an item from the front of the queue
    void Leave() {
      if (isEmpty()) { return; }

      Node * temp;
      if (front == NULL) { return; }
      temp = front;
      front = front->next;
      if (front == NULL) { rear = NULL; }
      delete temp;

      length--;
    };

    // view the item's data at the front of the queue
    float Front() {
      return front->data;
    };

    int Length() {
      return length;
    }

    // check if the queue is empty
    bool isEmpty() {
      if (front == NULL) { return true; }
      return false;
    };
};

#define TIMEDELAY 3 // DO NOT CHANGE THIS VALUE!!!
#define N 128 // DO NOT CHANGE THIS VALUE!!!
int OutQueues_current[N];
int Congestion_Size[N];
int Input_Size[N];

Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation () {
  for(int a = 0; a < N; a++) {
    OutQueues_current[a] = 0; Congestion_Size[a] = 0;
  }
}

int sum_elements_array(int array[]) {
  int sum = 0;
  for(int a = 0; a < N; a++) {
    sum = sum + array[a];
  }
  return sum;
}

int number_of_ports = 0;

int main(int argc, char** argv){ //get arguments from command line, the name of the simulation text file
  ifstream input_file;

  if (argc != 2) {
    cout<< "Type a file name. " << endl << argv[1] << endl;
    exit(0);
  }

  input_file.open(argv[1]);

  if (input_file.is_open() == false) {
    cout << "Could not read file: " << endl << argv[1] << endl;
    exit(0);
  }

  //read the file, print the input ports contents
  int portnumber = 0;

  string expression; // the entire line
  string geninput;
  string token; // the single char of the line

  while (!input_file.eof()) {
     getline(input_file, expression);
     stringstream line(expression);

     if (input_file.eof()) break;
     if (expression[0] == '#') continue; // skip commented lines

     if (expression[0] == 'P') {
       getline(line, token, ' ');
       getline(line, token, ' ');
       number_of_ports = atoi(token.c_str());
       continue;
     }

     portnumber++;

     while (getline(line, token, ' ')) {
       int input_char;
       input_char = atoi(token.c_str());

       if (input_char < 0 || input_char > number_of_ports || number_of_ports < portnumber) {
         cout << "ERROR in the format of the text file" << endl;
         exit(0);
       }

       // add the current char to the right queue
       InputQueues[portnumber - 1].Join(input_char);
       Input_Size[portnumber - 1] = InputQueues[portnumber].Length();
     }

     int sumofinputpackets = 0;
     sumofinputpackets = sum_elements_array(Input_Size);

     cout<< "Input packets at input queue for port "<< portnumber << " = " << sumofinputpackets << endl; //DEBUG, comment for final version
     cout<< "if this value is still zero, it is because you did not implement the queues yet..." << endl; //DEBUG, comment for final version
  }

  // we have finished reading in our data. Now carry on with the simulation

  cout << endl << "Start of the simulation, press a key " << endl << endl; //DEBUG, comment for final version
  getline(cin, geninput);
  init_simulation();
  unsigned long int clock = 0;
  unsigned long int currentsum = 99999999; //sum_elements_array(OutQueues_current);
  portnumber = 0;

  // we're not looping through portnumbers correctly
  while (currentsum > 0) {
    // this portnumber shit is buggy af
    if (portnumber > (number_of_ports - 1)) {
      portnumber = 1;
    } else {
      portnumber++;
    }

    cout << "portnumber: " << portnumber << endl;

    clock++;

    Queue input_queue = InputQueues[portnumber];

    // this is working, I'm managing to transfer the item from one queue to another
    // The problem is that the output totals are 0 and I break the loop.
    // That's what I need to tackle next.
    if (!input_queue.isEmpty()) {
      int destination = input_queue.Front() - 1;
      Queue output_queue = OutputQueues[destination];

      // join the output queue
      output_queue.Join(destination);
      // update the current total for the output queue. OutQueues_current is terribly named.
      OutQueues_current[destination] = output_queue.Length();
      // leave the input queue
      input_queue.Leave();
    }

    if((clock % (TIMEDELAY*number_of_ports) == 0) && (clock != 0)) { //DO NOT MODIFY THIS LINE!
      cout << "Packets can leave the output queues at " << clock << " microsec " << endl;//DEBUG, comment for final version

      for(int a = 0; a < number_of_ports; a++){
        // Delete 1 packet from the queue
        cout << "leaving\n";
        OutputQueues[a].Leave();

        /* and count number of packets again */
        int length = OutputQueues[a].Length();
        cout << "length: " << length << endl;
        Congestion_Size[a] = length;
      }
    }
    //
    // include the queue updates for the simulation
    //
    // compute the current state of the output queues
    cout << "Current sum: " << currentsum << endl; //DEBUG, comment for final version
    currentsum = sum_elements_array(OutQueues_current);

    if (currentsum > sum_elements_array(Congestion_Size)) {
      for(int a = 0; a < number_of_ports; a++) {
        Congestion_Size[a] = OutQueues_current[a];
      }
    }
  }

  //FINAL PRINTOUT, remember to comment out all the other debugging printouts above
  for(int a = 0; a < number_of_ports; a++){
    cout << "output port " << a+1 << ": " << Congestion_Size[a] << " packets" << endl;
  }
}
