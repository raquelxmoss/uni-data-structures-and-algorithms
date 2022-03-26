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
      length--;
      if (isEmpty()) { return; }

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

  input_file.open(argv[1]);
  if(input_file.is_open()==false) {cout << "Could not read file: " << endl << argv[1] << endl; exit(0);}
  string token;
  while(!input_file.eof()){
     getline(input_file,expression);
     stringstream line(expression);
     if(input_file.eof()) break;
     if(expression[0] =='#') continue;//jump line, this is a line of comments
     if(expression[0] =='P') {
       getline(line, token,' ');
       getline(line, token,' ');
       number_of_ports=atoi(token.c_str());
       continue;
     }

     // * very chaotic as to whether we're dealing with port numbers (starting at 1)
     // * or array indexes in the array of ports (starting at 0). Who fucking knows.
     portnumber++;

     cout << "Port " << portnumber + 1 << ": " << endl;//DEBUG, comment for final version

     while(getline(line, token,' ')){
       int destination;
       destination = atoi(token.c_str());//use this one if your compiler is not C++11
       if (destination < 0 || destination > number_of_ports || number_of_ports<portnumber) {cout << "ERROR in the format of the text file" << endl; exit(0);}

       // * hey look finally some code I wrote. Just adding an item to the input queue.
       InputQueues[portnumber - 1].Join(destination);
     }
     int sumofinputpackets=0;
     // * And checking the length of the queues, this is just for debugging I think,
     // * Idk, this skeleton is dumb
     sumofinputpackets += InputQueues[portnumber - 1].Length();
     cout<< "Input packets at input queue for port "<< portnumber << " = " << sumofinputpackets << endl;//DEBUG, comment for final version
     cout<< "if this value is still zero, it is because you did not implement the queues yet..." << endl;//DEBUG, comment for final version
  }

  //now carry on with the simulation
  cout << endl << "Start of the simulation, press a key " << endl << endl;//DEBUG, comment for final version
  getline(cin, geninput);// pause //DEBUG, comment for final version
  init_simulation();
  unsigned long int clock=0;
  unsigned long int currentsum=99999999; //sum_array(OutputQueuesCurrentTotals);
  portnumber=0;

  while (currentsum > 0) {
    // cout << "Input portnumber " << portnumber+1 << endl;//DEBUG, comment for final version
    portnumber++;
    if(portnumber > (number_of_ports-1)) portnumber=0;

    // * here's some code from me
    if (!InputQueues[portnumber - 1].isEmpty()){
      // * The trouble that I'm running into is that even after I add
      // * something to the queue with Join() in this while loop,
      // * it doesn't seem to add properly/the length doesn't increment
      // * and I don't know why.
      // * I've tried various access by value/reference/assigning to a variable
      // * and I'm lost.

      // join the output queue
      OutputQueues[InputQueues[portnumber - 1].Front() - 1].Join(InputQueues[portnumber - 1].Front() - 1);

      // * update the current total for the output queue. OutputQueuesCurrentTotals is terribly named.
      OutputQueuesCurrentTotals[InputQueues[portnumber - 1].Front() - 1] = OutputQueues[InputQueues[portnumber - 1].Front() - 1].Length();
      // * leave the input queue
      InputQueues[portnumber - 1].Leave();
      InputQueues_lengths[portnumber - 1] = InputQueues[portnumber - 1].Length();
    }


    clock++;

    if(clock % (TIMEDELAY*number_of_ports) == 0 && clock!=0) { //DO NOT MODIFY THIS LINE!
      // cout << "Packets can leave the output queues at " << clock << " microsec " << endl;//DEBUG, comment for final version
      for(int a = 0; a < number_of_ports; a++){
        //Delete 1 packet from each queue
        OutputQueues[a].Leave();

        /* and count number of packets again */
        MaximumCongestionTotals[a] = OutputQueues[a].Length();
      }
    }
    //
    // include the queue updates for the simulation
    //
    // As there are no more packets in the input queues, this is the point of maximum congestion.
    //compute the current state of the output queues
    // cout << "Current sum: " << currentsum << endl;//DEBUG, comment for final version

    currentsum = sum_array(InputQueues_lengths);

    if(currentsum > sum_array(MaximumCongestionTotals)){
      for(int a=0;a<number_of_ports;a++){
        MaximumCongestionTotals[a]=OutputQueuesCurrentTotals[a];
      }
    }
  }
  //FINAL PRINTOUT, remember to comment out all the other debugging printouts above
  for(int a=0;a<number_of_ports;a++){
    cout << "output port " << a+1 << ": " << MaximumCongestionTotals[a] << " packets" << endl;
  }
}
