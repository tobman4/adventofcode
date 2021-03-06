/*
 * day: 2, part: 2
 * 
*/

#include<iostream>
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
   
   
   void get_command() {
      eax = memory[ebp]; // opcode
      
      ebx = memory[ebp+1]; // A
      ecx = memory[ebp+2]; // B
      
      edx = memory[ebp+3]; // TARGET MEM cell
   }
   
   void process_command() {
      
      switch(eax) {
       case 1:
	 memory[edx] = memory[ebx] + memory[ecx];
	 break;
       case 2:
	 memory[edx] = memory[ebx] * memory[ecx];
	 break;
       default:
	 std::cout << "ERROR: got opcode: " << eax << std::endl;
	 err = true;
       case 99:
	 runing = false;
	 halt = true;
	 break;
	   
	}
      ebp+=4;
   }
   
   void step() {
      get_command();
      process_command();
   }
   
   void dump_memory() {
      for(int i = 0; i < memory.size(); i++) {      
	 switch(memory[i]) {
	  case 1:
	  case 2:
	    std::cout << i << ": " << memory[i]  << " " << memory[i+1] << " "  << memory[i+2] << " " << memory[i+3]  << std::endl;
	    i += 3;
	  default:
	    std::cout << i << ": " << memory[i] << std::endl;
	    break;
	  }
      }
   }
};
