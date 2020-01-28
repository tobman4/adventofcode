#include "computer.h"

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>

int phase = 0; // 0-4
float last;

bool side = false;

float IO::get_data(void) {
   side = !side;
   return side ? phase : last;
}

void IO::out_data(float data, int addr) {
   std::cout << "the best has changed from " << out << " to " << data << ". using "<< A << "-" << B << std::endl;
   last = data;
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
   

   


   std::cout << "best thrust is: " << out << std::endl;
   return 0;

}
