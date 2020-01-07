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





std::vector<int> test(std::string data) {
   
   
   std::vector<int> out;
   std::string nr = "0";
   
   for(int i = 0; i <= data.length(); i++) {
      if(data[i] == ',') {
	      out.push_back(stoi(nr));
	      nr = "0";
      } else {
	      nr += data[i];
      }
   }
   out.push_back(stoi(nr));
   return out;
}

int main(void) {
   std::string line,raw;
   
   //load file into array
   
   std::ifstream programfile_file;
   programfile_file.open("../program_test");
   //programfile_file.open("../dbg");
   while(std::getline(programfile_file,line)) {
      raw += line;
   }
   std::vector<int> program = test(raw);
   
   computer cpu = computer(program);
   
	cpu.dump_memory();
   cpu.start();
	while(cpu.active()) {
	    cpu.step();
   }
   cpu.dump_memory();

   return 0;
}