#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <chrono>

using namespace std;


void line_to_intvec(const string &str, vector<int> &vec){
    vec.clear();

    std::stringstream ss(str);
    int num;
    while(ss >> num){
        vec.push_back(num);
    }
}

int main(int argc, char** argv)
{
   auto start = std::chrono::high_resolution_clock::now();

   if(argc!=2) return 1;

   ifstream inputfile(argv[1]);

   string line;
   vector<int> numbers_line;
   int min, max, result = 0, c = 0;
   int min2, max2, result2 = 0;
   int lower, higher;

   while(getline(inputfile, line)){
       c++;
       min = numeric_limits<int>::max();
       min2 = numeric_limits<int>::max();
       max = 0;
       max2 = 0;

       line_to_intvec(line, numbers_line);

       for(int const& num : numbers_line){

           if(num<min)min=num;
           if(num>max)max=num;

           for(int const& num_other : numbers_line){
                if(num==num_other)continue;
                if(num<num_other){
                    lower=num;
                    higher=num_other;
                } else {
                    lower=num_other;
                    higher=num;
                }
                if((higher%lower)==0){
                    max2 = higher;
                    min2 = lower;
                    break;
                }
           }

       }

       result+=max-min;
       result2+=max2/min2;

   }

   cout << "checksum 1: " << result << endl;
   cout << "checksum 2: " << result2 << endl;
   auto elapsed = std::chrono::high_resolution_clock::now() - start;
   auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

   cout << "took " << microseconds << " microseconds." << endl;
   return 0;
}
