
#include <iostream>
using namespace std;
int main() {
  
int marks = 40;
  if ( marks < 40 ){
    cout << "Fail Good"
  }
 else if ( marks >= 40 &&  marks < 50){
    cout << "Fail" << endl;
  }
  else if ( marks >= 50 && marks < 60){
    cout << "D grade" << endl;
  }
  else if ( marks >= 60 && marks < 75){
    cout << "C Grade" << endl;
  }
  else if ( marks >= 75 && marks < 85){
    cout << "B Grade" << endl;
  }
  else if ( marks >= 85 && marks == 100){
    cout << "A" << endl;
  }
 
  else {
    cout << "Enter a valid integer number";
  }
  return 0;
}
