#include<iostream>
#include<fstream>
#include<string>
#include<math.h>

/*
 * ebx = 1 - add ebx+1,ebx+2 and store ebx+3
 * ebx = 2 - multiplie ebx+1,ebx+2 and store ebx+3
 * 99 - progam end
*/

int main(void) {

   std::string line,raw;
   
   //load file into array
   
   std::ifstream programfile_file;
   programfile_file.open("../program");
   while(std::getline(programfile_file,line)) {
      raw += line;
   }
   
   std::cout << raw << std::endl;
   
   for(int i = 0; i >= 100; i+=4) {
	
   }
   
}



int* test(std::string data) {
   std::cout << data << std::endl;
   int arr[2] = {1,2};
   
   
   return arr;
}
