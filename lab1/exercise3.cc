#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// function generator
int RandomNumber() {
  //  srand(time(NULL));
  return (std::rand()%100+1); }

struct countOdd : public unary_function<int, void>
{
  int oddNumber, evenNumber;
  countOdd(): oddNumber(0), evenNumber(0) {}

  void operator() (int x) {
    if (x%2 == 0) evenNumber++;
    else oddNumber++;
  }
};
int main()
{
  vector<int> myvector(100);
  generate(myvector.begin(), myvector.end(), RandomNumber);
  copy(myvector.begin(), myvector.end(), ostream_iterator<int>(cout, ", "));
  countOdd mycount = 
      for_each(myvector.begin(), myvector.end(), countOdd());
  
  cout<< "\n\nOdd number is: "<< mycount.oddNumber<<"\nEven number is: "<<mycount.evenNumber<<endl;
  
}
