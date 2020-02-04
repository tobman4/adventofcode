#include "computer.h"

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>

int phase[5] = {0,1,2,3,4}; // 0-4
int phase_index = 0;
float last = 0;
float best = -1;

bool side = false;

float IO::get_data(void) {
   side = !side;
   return side ? phase[phase_index] : last;
}

void IO::out_data(float data, int addr) {
   std::cout << "out form " << phase_index << " = " << data << std::endl;
   last = data;
}

void swap(int *arr,int arr_length) {

   int dump[arr_length][arr_length];



   for(int i = 0; i < arr_length; i++) {
      int hold = arr[0];
      arr[0] = arr[i];
      arr[i] = hold;
      for(int j = 0; j < arr_length; j++) {
         dump[i][j] = arr[j];
      }
      hold = arr[0];
      arr[0] = arr[i];
      arr[i] = hold;
   }





   //////////////////////////////////////////////////
   //BLACK BOX                                     //
   for(int i = 0; i < arr_length; i++) {           //
      for(int j = 0; j < arr_length; j++) {        //
         std::cout << dump[i][j];                  //
      }                                            //
      std::cout << std::endl;                      //
   }                                               //
   //                                              //
   /////////////////////////////////////////////////
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
   programfile_file.open("../program_test");
   //programfile_file.open("../dbg");
   while(std::getline(programfile_file,line)) {
      raw += line;
   }
   std::vector<float> program = test(raw);
   int size = sizeof(phase)/sizeof(phase[0]);

   swap(phase,sizeof(phase)/sizeof(phase[0]));

   // computer cpu = computer(program);
   // for(int i = 0; i < sizeof(phase)/sizeof(phase[0]); i++) {
   //    phase_index = i;

   //    cpu.reset();
   //    cpu.start();
   //    while(cpu.active()) {
   //       cpu.step();
   //    }
   // }
   return 0;

}
