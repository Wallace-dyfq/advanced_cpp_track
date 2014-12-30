#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

// function generator to generate integer between 5 to 10
int randomeNumber() {
  return rand() % 11 + 5;
  
}

// function generator
string RandomString() {
  //  srand(time(NULL));
  //return (std::rand()%100+1); }
  int num = randomeNumber();
  //cout << "random number is "<< num<<endl;
  // string s; // this does not work. 
  char s[num];
  static const char alphanum[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  int size_alpha = sizeof(alphanum);
  //cout<<"num = "<< num<<endl;
  for(int i = 0; i < num; ++i){
    
    s[i] = alphanum[rand() % (size_alpha - 1)];
    // cout<<"s["<<i<<"]= " <<s[i]<<endl;
    
  }
  s[num] = 0;
  
  string ss = s;
  // cout<<"string is " << ss <<endl;
  return ss;
}
  

// binary function
bool myCompare(string s1, string s2) {
  return s1.length() < s2.length();
}

int main()
{
  vector<string> myvector(100);
  generate(myvector.begin(), myvector.end(), RandomString);
  cout << "\n================sorted by default================\n"<<endl;
  sort(myvector.begin(), myvector.end());
  copy(myvector.begin(), myvector.end(), ostream_iterator<string>(cout, ", "));

  std::cout << std::endl;
  cout << "\n===================sorted by size===============\n"<<endl;
  sort(myvector.begin(), myvector.end(), myCompare);
  copy(myvector.begin(), myvector.end(), ostream_iterator<string>(cout, ", "));
}
