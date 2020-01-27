#include "computer.h"

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>

/*
 * ebx = 1 - add ebx+1,ebx+2 and store ebx+3
 * ebx = 2 - multiplie ebx+1,ebx+2 and store ebx+3
 * 99 - progam end
 * 
 * 
 * Part 2:
 * c++ is fast so i wil try brute-force
*/

int A = 0;
int B = 0;
bool side = false;

float IO::get_data(void) {
   side = !side;
   return side ? A : B;
}

std::vector<float> test(std::string data) {
   
   
   std::vector<float> out;
   std::string nr = "0";
   
   for(int i = 0; i <= data.length(); i++) {
      if(data[i] == ',') {
	      out.push_back(stof(nr));
	      nr = "";
      } else {
	      nr += data[i];
      }
   }
   out.push_back(stof(nr));
   return out;
}

int main(void) {
   std::string line,raw;
   
   //load file into array
   
   std::ifstream programfile_file;
   programfile_file.open("../program");
   //programfile_file.open("../dbg");
   while(std::getline(programfile_file,line)) {
      raw += line;
   }
   std::vector<float> program = test(raw);
   
   computer cpu = computer(program);
   
   for(int i = 0; i < 10; i++) {
      for(int j = 0; j < 10; j++) {
         A = i;
         B = j;
         cpu.start();
         while(cpu.active()) {
            cpu.step();
         }
         cpu.reset();
      }
   }
   return 0;

}
