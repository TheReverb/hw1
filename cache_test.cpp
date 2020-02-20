

#include <iostream>

const int prefetch_buffer = 4; // using getconf I determined a page size of 4 kb for my machine.
const int cache_line = 64; // and a cache line size of 64 bytes.

struct node {

  node *next;
  char empty_space[prefetch_buffer];

};


std::vector<node> initialize_list(int buffer_size) {

  const auto num_nodes = buffer_size / cache_line;
  std::vector<node> linked_list(num_nodes);

  for (int i = 0; i < linked_list.size() - 1; i++){
    linked_list[i].next = &linked_list[i + 1];
  }

  linked_list[list.size() - 1].next = &linked_list[0];
  return *linked_list

}


static void traverse_list(node *current, int reps) {

  for (int i = 0; i < reps; i++){
    current = *current.next;
  }
}


static void main{

  // create list of buffer size intervals
  // create




}
