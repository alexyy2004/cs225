/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  // while (head_ != nullptr) {
  //   ListNode* temp = head_ -> next;
  //   delete head_;
  //   head_ = temp;
  // }
  // tail_ = nullptr;
  // length_ = 0;
  ListNode* cur = head_;
  while (cur != NULL) {
    ListNode* next = cur->next;
    delete cur;
    cur = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  head_ = newNode;
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  if (tail_->prev == NULL) {
    tail_->prev = newNode;
  }
  length_ += 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if (tail_ == nullptr) {
    head_ = tail_ = newNode;
    newNode->next = nullptr;
    newNode->prev = nullptr;
  } else {
    tail_ -> next = newNode;
    newNode->next = nullptr;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  length_ += 1;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
  if (start == nullptr) {
    return start;
  }
  
  if (length_ < splitPoint || splitPoint < 1) {
    return start;
  }

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  
  if (curr != nullptr) {
      tail_ = curr->prev;
      curr->prev->next = nullptr;
      curr->prev = nullptr;
      return curr;
  }
  
  return nullptr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (head_ == nullptr) {
    return;
  }
  ListNode* cur = head_;
  ListNode* temp;
  while (cur->next != tail_) {
    temp = cur->next;
    cur->next = temp->next;
    cur = cur->next;
    insertBack(temp->data);
    //delete temp;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  ListNode* cur = startPoint;
  ListNode* cur_tail = endPoint;
  while (cur != endPoint) {
    ListNode* temp = cur->next;
    ListNode* cur_prev = cur->prev;
    ListNode* cur_tail_next = cur_tail->next;
    if (cur_prev == nullptr) {

    } else {
      cur_prev->next = cur->next;
    }
    cur->next->prev = cur_prev;
    cur->next = cur_tail_next;
    if (cur_tail_next == nullptr) {

    } else {
      cur_tail_next->prev = cur;
    }
    cur->prev = cur_tail;
    cur_tail->next = cur;
    cur = temp;
  }
  if (head_ == startPoint) {
    head_ = endPoint;
  }
  if (tail_ == endPoint) {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  ListNode* cur = head_;
  ListNode* start;
  ListNode* end;
  while (cur != nullptr) {
    start = cur;
    int count = 1;
    while (count <= n && cur != nullptr) {
      end = cur;
      count += 1;
      cur = cur->next;
    }
    reverse(start, end);
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  if (first == nullptr && second != nullptr) {
    return second;
  }
  if (second == nullptr && first != nullptr) {
    return first;
  }
  ListNode* result = nullptr;
  ListNode* result_head;
  ListNode* cur_first = first;
  ListNode* cur_second = second;
  while (cur_first != nullptr && cur_second != nullptr) {
    if (cur_first->data < cur_second->data) {
      if (result == nullptr) {
        result = cur_first;
        result_head = cur_first;
        cur_first = cur_first->next;
      } else {
        result->next = cur_first;
        cur_first->prev = result;
        cur_first = cur_first->next;
        result = result->next;
      }
    } else {
      if (result == nullptr) {
        result = cur_second;
        result_head = cur_second;
        cur_second = cur_second->next;
      } else {
        result->next = cur_second;
        cur_second->prev = result;
        cur_second = cur_second->next;
        result = result->next;
      }
    }
  }
  if (cur_first == nullptr) {
    result->next = cur_second;
    cur_second->prev = result;
  }
  if (cur_second == nullptr) {
    result->next = cur_first;
    cur_first->prev = result;
  }
  return result_head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if (chainLength == 1) {
    return start;
  }
  int length = (int)(chainLength/2);
  ListNode* right = split(start, length);
  start = mergesort(start, length);
  right = mergesort(right, chainLength - length);
  return merge(start, right);
}
