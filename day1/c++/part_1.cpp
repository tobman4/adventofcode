#include<iostream>
#include<fstream>
#include<string>
#include<math.h>

int main(void) {
   std::cout << "<START>" << std::endl;

   std::string line;
   int weigth_tot_1 = 0;
   int weigth_tot_2 = 0;

   std::cout << "opening file" << std::endl;
   
   std::ifstream module_file;
   module_file.open("../modules");
   
   while(std::getline(module_file,line)) {
      int curr = std::stoi(line);
      int fule_req = floor(curr/3) - 2;
      weigth_tot_1 += fule_req;
      while(fule_req > 0) {	 
	 weigth_tot_2 += fule_req;
	 fule_req = floor(fule_req/3) - 2;
      }
   }
   std::cout << "Part 1: " << weigth_tot_1 << std::endl;
   std::cout << "Part 2: " << weigth_tot_2 << std::endl;
}
