/*
 * day: 2, part: 2
 * 
*/

#include<iostream>
#include<string> 
#include<vector>

class computer {
 private:
   std::vector<int> memory,memory_pure;
   int eax,ebx,ecx,edx,ebp;
   bool halt = false;
   bool runing = false;
   bool err = false;
   
 public:
   computer(std::vector<int> mem) {
      for(int i = 0; i < mem.size(); i++) {
	      memory.push_back(mem[i]);
	      memory_pure.push_back(mem[i]);
      }   
   }
   
   bool active() {
      return (!halt && !err) && runing;
   }
   
   int read_address(int addr,bool pure = false) {
      if(addr < 0 || addr >= memory.size()) { // test if in range of pure memory?
	   return -1; // out of range
      }
      if(pure) {
	      return memory_pure[addr];
      } else {
	      return memory[addr];
      }
   }
   
   bool write_address(int addr,int data,bool pure = false) {
      //addr = address... figth me 
      if(addr < 0 || addr >= memory.size()) {	   
	      return false; // out of range
      }
      if(pure) {
	      memory_pure[addr] = data; // need force or none safe mode??
      } else {
	      memory[addr] = data;
      }
      return true;
      
   }
   
   void start() {
      halt = false;
      err = false;
      runing = true;
   }   
   
   void reset() {
      eax = 0;
      ebx = 0;
      ecx = 0;
      edx = 0;
      ebp = 0;
      runing = false;
      halt = false;
      err = false;
      memory.clear();
      for(int i = 0; i < memory_pure.size(); i++) {
	      memory.push_back(memory_pure[i]);
      }
      
   }
   
   int _get_opcode(int code) {
      std::string str = std::to_string(code);
      while(str.length() < 5) {
            str = "0" + str;
      }
      std::string ret = "";
      ret += str.at(str.length()-2);
      ret += str.at(str.length()-1);

      return std::stoi(ret);
   }

   void get_command() {
      
      
      eax = memory[ebp]; // opcode
      
      std::string str = std::to_string(eax);
      while(str.length() < 5) {
            str = "0" + str;
      }

      bool b_mode = false;
      bool c_mode = false;
      bool adr_mode = false;
      
      std::string opcode = "";
      opcode += str.at(str.length()-2);
      opcode += str.at(str.length()-1);
      str.pop_back();
      str.pop_back();
      // std::cout << str << "-" << opcode << std::endl;

         
      for(int i = 2; i >= 0; i--) { // A0 B1 C2
         bool mode = false;
         if(i < str.length()) {
            mode = (str[i] == "1"[0]);
         } else {
            std::cout << "ERROR" << std::endl;
         }
         switch(i) {
            case 0:
               // std::cout << "A: " << mode << std::endl;
               adr_mode = mode;
               break;
            case 1:
               // std::cout << "B: " << mode << std::endl;
               c_mode = mode;
               break;
            case 2:
               // std::cout << "C: " << mode << std::endl;
               b_mode = mode;
               break;
         }
      }
      eax = std::stoi(opcode);
      
      

      /////
      
      if(b_mode) {
         ebx = memory[ebp+1]; // A
      } else {
         ebx = memory[memory[ebp+1]];
      }

      // std::cout << "ebx(" << memory[ebp+1] << ") = " << ebx << std::endl;

      if(c_mode) {
         ecx = memory[ebp+2]; // B
      } else {
         ecx = memory[memory[ebp+2]];
      }
      
      // std::cout << "ecx(" << memory[ebp+2] << ") = " << ecx << std::endl;


      if(adr_mode) {
         edx = ebp+3; // TARGET MEM cell
      } else {
         edx = memory[ebp+3];
      }

      // std::cout << "edx(" << memory[ebp+3] << ") = " << edx << std::endl;

   }

   void stop() {
      halt = true;
      runing = false;
   }
   
   void process_command() {
      /*
       * x86 reg
       * 
       * eax - opcode
       * 
       * 1  - add ebx to ecx and write to edx
       * 2  - multiply ebx to ecx and write to edx
       * 99 - halt
      */

      if(halt) {
         //TODO: show error
         return;
      }

      int steps = 4; // 4 is default
      
      switch(eax) {
       case 1:

	      memory[edx] = ebx+ecx;
         //memory[edx] = memory[ebx] + memory[ecx];
	      break;
       case 2:
         memory[edx] = ebx*ecx;
	      //memory[edx] = memory[ebx] * memory[ecx];
	      break;
      case 3:
         int in;
         std::cout << "enter a int: ";
         std::cin >> in;
         memory[ebx] = in;
         steps = 2;
         break;
      case 4:
         std::cout << "out: " << memory[ebx] << std::endl;
         steps = 2;
         break;
       default:
         dump_memory();
	      std::cout << "ERROR: got opcode: " << eax << std::endl;
	      err = true;
       case 99:
	      runing = false;
	      halt = true;
	      break;
	   
	   }
      ebp+=steps;
   }
   
   void step() {
      get_command();
      process_command();
   }
   
   void dump_memory() {
      std::cout << "=============memory dump============" << std::endl;
      for(int i = 0; i < memory.size(); i++) {      
	   switch(_get_opcode(memory[i])) {
	      case 1:
	      case 2:
	         std::cout << i << ": " << memory[i]  << " " << memory[i+1] << " "  << memory[i+2] << " " << memory[i+3]  << std::endl;
	         i += 3;
            break;
         case 3:
         case 4:
            std::cout << i << ": " << memory[i]  << " " << memory[i+1] << std::endl;
            i += 1;
            break;
	      default:
	         std::cout << i << ": " << memory[i] << std::endl;
	         break;
	      }
      }
   std::cout << "====================================" << std::endl;
   }
};
