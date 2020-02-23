
#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace chrono;


struct node {
	int buffer;
	node* next = nullptr;
};


double benchmark(int N, int iters) {

	vector<node> linked_list(N);
  vector<node*> list_order(N); //stores pointers to nodes in linked_list

	for (int i = 0; i < N; i++) {  //
		list_order[i] = &linked_list[i];
	}

	random_shuffle(begin(list_order), end(list_order)); //shuffles the order in which nodes are linked, hindering the prefetcher.

	for (int i = 0; i < N-1; i++) {  //links nodes based on the order found in list_order
		list_order[i]->next = list_order[i+1];
	}
	node* head = list_order[0]; //close the loop such that the linked_list points in a circle.

	auto start = chrono::steady_clock::now();
	for (int i = 0; i < iters; i++) {

		node* current = head;
		while (current) {
			current = current->next;
		}
	}

  auto end = chrono::steady_clock::now();
	auto elapsed =  end - start;
	auto ns = duration_cast<nanoseconds>(elapsed).count();

	return ns / double(N * iters); //calculates average ns per operation
}


int main(){
  cout << "# Bytes    Time(ns)" << endl;

	int start = 10; //iterates from 2^min to 2^max.
	int stop = 26;

	for (int i = start; i <= stop; i++) {

		int N = int(pow(2, double(i)));
		int reps = int(2e10 / pow(N, 1.5)); //scales the repetitions inversely to the size of the list.

		if (reps<1){ //makes sure to round up
      reps = 1;
    }

		auto result = benchmark(N, reps);
		cout << (N*sizeof(node)) << "   " << result << "   # (N=" << N << ", reps=" << reps << ") " << endl;

  }
}
