#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>  // swap
#include <ctime>
#include <cstdlib>  // random
#include <utility>  // swap

using namespace std;

template <typename BidirectionalIterator>
void my_reverse(BidirectionalIterator first, BidirectionalIterator last) {
    // Your implementation here!
  while((first != last) && (first != --last) ){
      swap(*first, *last);
      ++first;
    }
}


// function generator
int RandomNumber() {
  //  srand(time(NULL));
  return (std::rand()%100+1); }


void test(int size)
{
  cout<< "Size: "<<size<<endl;
  vector<int> values(size);

  cout <<" generate random numbers: "<<endl;
  generate(values.begin(), values.end(), RandomNumber);

   // this does not work
  //  generate(values.begin(), values.end(), RandomNumber()); 
  copy(values.begin(), values.end(), ostream_iterator<int>(cout, ", "));

  cout<<endl<<"reverse the vector using my_reverse: "<<endl;
  my_reverse(values.begin(), values.end());
  copy(values.begin(), values.end(), ostream_iterator<int>(cout, ", "));
}

int main()
{
  int size = 20;
  cout<< "\ntest with "<<size<<" elements"<<endl;
  test(size);

  size++;
  cout<< "\ntest with "<<size<<" elements"<<endl;
  test(size);

  return 0;
}


       
  
