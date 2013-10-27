#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class BackTrackNode
{
public:
  BackTrackNode(T value) : value_(value), result_(0) {}
  BackTrackNode(T value, T result) : value_(value), result_(result) {}

  void setValue(T value) { value_ = value; }
  T getValue() const { return value_; }

  void setResult(T result) { result_ = result; }
  T getResult() const { return result_; }

  void push_back(BackTrackNode<T> &child) { children_.push_back(child); }

  // Allows the internal container to be iterated
  typedef typename list<BackTrackNode<T> >::iterator BackTrackNodeIterType;
  BackTrackNodeIterType begin() { return children_.begin(); }
  BackTrackNodeIterType end()   { return children_.end();   }

private:
  T value_;
  T result_;
  list<BackTrackNode<T> > children_;
};


typedef list<list<int> >    AnswerT;
typedef BackTrackNode<int>  BackTrackNodeT;

void findComboSumsRecursive(BackTrackNodeT &root, int index, int N, list<int> &l, AnswerT &answers)
{
  for(int i = index; i > 0; --i)
  {
    BackTrackNodeT node(i, i+root.getResult());
    root.push_back(node);
    l.push_back(i);

    if(node.getResult() == N)
    {
      // Found an answer
      //   This will put a copy of the list on answers
      answers.push_back(l);
    }
    else
    {
      int nextIndex = (i > N/2) ? (N-i) : (i-1);
      // could check for nextIndex==0 to avoid another level of unecessary recursion
      findComboSumsRecursive(node, nextIndex, N, l, answers);
    }

    l.pop_back();
  }
}

//
// Intermediate method to setup the recursion
//
void findComboSums(int N, AnswerT &answers)
{
  BackTrackNodeT root(0);
  list<int> l;

  findComboSumsRecursive(root, N, N, l, answers);
}

//
// Functions to print the answers
//
void printListEntry(int n)
{
  cout << n << " ";
}

void printList(list<int> &l)
{
  cout << "\nList: ";
  for_each(l.begin(), l.end(), printListEntry);
}

//
//
int main(int argc, char **argv)
{
  int N;

  cout << "Enter the integer N: ";
  cin >> N; // TODO make sure its an int

  AnswerT answers;
  
  findComboSums(N, answers);

  cout << "Found [" << answers.size() << "] Answers for N=" << N;
  for_each(answers.begin(), answers.end(), printList);
  cout << endl;
}
