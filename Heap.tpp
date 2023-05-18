#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <cmath> // for floor()

template <typename T>
class Heap
{
private:
  std::vector<T> values;
  void heapify(int);

public:
  Heap(); // constructs an empty heap

  // constructs a heap with the values from the given vector
  // the type T MUST provide comparison operators <, >, ==
  Heap(std::vector<T>);

  void insert(T);
  void remove(T);
  T getMin();
};

/*******************************/
// default constructor
/*******************************/

template <typename T>
Heap<T>::Heap() {}

/*******************************/
// constructs a heap with the values in the given vector
// the type T MUST provide comparison operators <, >, ==
/*******************************/

template <typename T>
Heap<T>::Heap(std::vector<T> start_values)
{
  // copy the values into our heap vector
  for (int i = 0; i < start_values.size(); i++)
  {
    values.push_back(start_values.at(i));
  }

  // starting from last non-leaf node (last parent), heapify each
  // of the parents
  int initial_parent_index = floor((values.size() - 1) / 2);
  for (int parent_index = initial_parent_index; parent_index >= 0;
       parent_index--)
  {
    heapify(parent_index);
  }
}

/*******************************/
// add values to the heap
/*******************************/

template <typename T>
void Heap<T>::insert(T value)
{
  // add the new value to the end
  values.push_back(value);

  // sift up to restore heap property
  int child_index = values.size() - 1;
  int parent_index = floor((child_index - 1) / 2);

  while (child_index > 0 && values[child_index] < values[parent_index])
  {
    // swap parent and child
    std::swap(values[child_index], values[parent_index]);

    // move up one level in the tree
    child_index = parent_index;
    parent_index = floor((child_index - 1) / 2);
  }
}

/*******************************/
/* delete values from the heap */
/*******************************/

template <typename T>
void Heap<T>::remove(T value)
{
 int index_to_remove = -1;

  // find the index of the value to remove
  for (int i = 0; i < values.size(); i++) {
    if (values[i] == value) {
      index_to_remove = i;
      break;
    }
  }

  // if value is not found, return
  if (index_to_remove == -1) return;

  // swap the last value in the heap with the value to remove
  std::swap(values[index_to_remove], values.back());

  // remove the last value (now the value to remove)
  values.pop_back();

  // heapify the heap to restore the heap property
  heapify(index_to_remove);
}

/*******************************/
// find the smallest value in the heap
/*******************************/

template <typename T>
T Heap<T>::getMin()
{
    // in a min heap, the smallest value is at the root
  if (!values.empty()) {
    return values[0];
  } else {
    throw std::runtime_error("Heap is empty");
  }
}

/*******************************/
// private function to heapify a given 'node'
/*******************************/

template <typename T>
void Heap<T>::heapify(int parent_index)
{
  // if we're outside the index range, return
  if (parent_index < 0 || parent_index >= values.size())
    return;

  // find children indexes
  int left_child_index = parent_index * 2 + 1;
  int right_child_index = parent_index * 2 + 2;

  // if parent is larger than child, swap with smallest child
  int index_of_smallest = parent_index;

  // check if left child exists and if exists, is smallest value there
  if (left_child_index < values.size() &&
      values.at(left_child_index) < values.at(index_of_smallest))
  {
    // make this index the current smallest
    index_of_smallest = left_child_index;
  }

  // check if left child exists and if exists, is smallest value there
  if (right_child_index < values.size() &&
      values.at(right_child_index) < values.at(index_of_smallest))
  {
    // make this index the current smallest
    index_of_smallest = right_child_index;
  }

  // if parent is not smallest, swap with smallest child
  if (index_of_smallest != parent_index)
  {
    T temp = values.at(parent_index);
    values.at(parent_index) = values.at(index_of_smallest);
    values.at(index_of_smallest) = temp;

    // heapify the swapped index - it may need to move
    // further down the 'tree'
    heapify(index_of_smallest);
  }
}

#endif