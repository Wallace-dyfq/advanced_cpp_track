#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include<ext/functional>

/* this code intended to remove even numbers in a vector of int numbers.
   The author of the code forgot to use the __gnu_cxx namespace in front of
   compose1, which is not in std namespace.

   The code is broken because when printint out the vector after removing the
   even numbers, the author failed to use the new_end.

   We can fix it by using the new_end iterator.

 */
using namespace std;

int main(){

vector<int> v;
      v.push_back(1);
      v.push_back(4);
      v.push_back(2);
      v.push_back(8);
      v.push_back(5);
      v.push_back(7);

      copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
      cout << endl;

      vector<int>::iterator new_end = 
          remove_if(v.begin(), v.end(), 
                    __gnu_cxx::compose1(bind2nd(equal_to<int>(), 0),
                             bind2nd(modulus<int>(), 2)));

      //      copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

      // fix the problem by using new_end
       copy(v.begin(), new_end, ostream_iterator<int>(cout, " "));
      cout << endl;
      
}
