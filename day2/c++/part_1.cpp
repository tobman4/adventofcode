#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>

/*
 * ebx = 1 - add ebx+1,ebx+2 and store ebx+3
 * ebx = 2 - multiplie ebx+1,ebx+2 and store ebx+3
 * 99 - progam end
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
   //out.push_back(stoi(nr));
   return out;
}

void memmory_dump(std::vector<int> data) {
   std::cout << "=====================================================================" << std::endl;
   /*for(int i = 0; i < data.size(); i++) {
      std::cout << data[i] << std::endl;
   }
   std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;*/
   for(int i = 0; i < data.size(); i++) {
      switch(data[i]) {
       case 1:
	 std::cout << i << ": " << data[i]  << " " << data[i+1] << " "  << data[i+2] << " " << data[i+3]  << std::endl;
	 i+= 3;
	 break;
       case 2:
	 std::cout << i << ": " << data[i]  << " " << data[i+1] << " "  << data[i+2] << " " << data[i+3]  << std::endl;
	 i += 3;
	 break;
       default:
	 std::cout << i << ": " << data[i] << std::endl;
	 break;
      }
   }
   std::cout << "=====================================================================" << std::endl;
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
   std::cout << raw << std::endl;
   
   std::vector<int> program = test(raw);
   
   memmory_dump(program);
   
   int a,b,tar,opcode;
   bool break_mark = false;
   
   for(int i = 0; i < program.size(); i+=4) {
      opcode = program[i];
      if(opcode != 99) {
	 a = program[i+1];
	 b = program[i+2];
	 tar = program[i+3];
      }
      switch(opcode) {
       case 1:
	 /*std::cout << "program[" << i+1  << "]:" << a << " + "; //a
	 std::cout << "program[" << i+2  << "]:" << b; //b
	 std::cout << " > program[" << i+3 << "]:" << tar; //tar*/
	 program[tar] = program[a] + program[b];
	 break;
       case 2:
	 /*std::cout << "program[" << i+1  << "]:" << a << " * "; //a
	 std::cout << "program[" << i+2  << "]:" << b; //b
	 std::cout << " > program[" << i+3 << "]:" << tar; //tar*/
	 program[tar] = program[a] * program[b];
	 break;
       default:
	 std::cout << "ERROR: got opcode: " << opcode << std::endl;
       case 99:
	 std::cout << "EXIT" << std::endl;
	 break_mark = true;
	 break;
      }
      
      if(break_mark) {
	 break;
      }
      
      //std::cout << std::endl;
   }
   memmory_dump(program);
}
