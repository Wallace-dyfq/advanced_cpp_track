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

int main()
{
  vector<int> myvector(100);
  generate(myvector.begin(), myvector.end(), RandomNumber);
  copy(myvector.begin(), myvector.end(), ostream_iterator<int>(cout, ", "));
}
