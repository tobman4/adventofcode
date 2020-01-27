/*
 * day: 2, part: 2
 * 
*/

#include<iostream>
#include<string> 
#include<vector>

class IO {
   private:

      float last_ret;

      void send_data(void);
      float out_data(float data,int addr);
   public:

      void out_data(float data, int addr = -1) {
         // out_data(data,addr);
         return;
      }

      float get_input() {
         float ret;
         ret = get_data();
         return ret;
      };
};

void IO::send_data(float data,int addr) {
   std::cout << std::fixed << "out[" << addr << "]: " << data << std::defaultfloat << std::endl;
}

// float input::get_data(void) {
//    float in;
//    std::cout << "enter float: ";
//    std::cin >> in;
//    return in;
// }



class computer {
 private:
   std::vector<float> memory,memory_pure;
   float eax,ebx,ecx,edx;
   int   ebp;
   bool  halt = false;
   bool  runing = false;
   bool  err = false;

   IO interface;

   void jmp(int adr) {
      // std::cout << "jumping to " << adr << std::endl;
      ebp = adr;
   }

   int get_opcode(int code) { // no opcode < 0 i think... hope
      std::string str = std::to_string(code);
      while(str.length() < 5) {
            str = "0" + str;
      }
      std::string ret = "";
      ret += str.at(str.length()-2);
      ret += str.at(str.length()-1);

      return std::stoi(ret);
   }
   
 public:

   int DBG = 0;

   computer(std::vector<float> mem) {
      for(int i = 0; i < mem.size(); i++) {
	      memory.push_back(mem[i]);
	      memory_pure.push_back(mem[i]);
      }

      interface = IO();
   }
   
   bool active() {
      return (!halt && !err) && runing;
   }
   
   float read_address(int addr,bool pure = false) {
      if(addr < 0 || addr >= memory.size()) { // test if in range of pure memory?
	   return -1; // out of range
      }
      if(pure) {
	      return memory_pure[addr];
      } else {
	      return memory[addr];
      }
   }
   
   bool write_address(int addr,float data,bool pure = false) {
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
      eax = 0.0F;
      ebx = 0.0F;
      ecx = 0.0F;
      edx = 0.0F;
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
      if(DBG >= 1) {
         std::cout << "============" << std::endl;
      }
      eax = memory[ebp]; // opcode
      
      std::string str = std::to_string(int(eax));
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
      if(DBG >= 1) {
         std::cout << str << "-" << opcode << std::endl;
      }
      if(std::stof(opcode) == 3) { // only 3 and 4 is singel for now
         str = "011";
      }

      for(int i = 2; i >= 0; i--) { // A0 B1 C2
         bool mode = false;
         if(i < str.length()) {
            mode = (str[i] == "1"[0]);
         } else {
            std::cout << "ERROR" << std::endl;
         }
         switch(i) {
            case 0:
               if(DBG){
                  std::cout << "A: " << mode;
               }
               adr_mode = mode;
               break;
            case 1:
               if(DBG){
                  std::cout << "B: " << mode;
               }
               c_mode = mode;
               break;
            case 2:
               if(DBG){
                  std::cout << "C: " << mode;
               }
               b_mode = mode;
               break;
         }
         if(DBG >= 1) {
            std::cout << " | ";
         }
      }
      if(DBG >= 1) {
         std::cout << std::endl;
      }
      eax = std::stoi(opcode);
      
      

      /////
      
      if(b_mode) {
         ebx = memory[ebp+1]; // A
      } else {
         ebx = memory[memory[ebp+1]];
      }


      if(c_mode) {
         ecx = memory[ebp+2]; // B
      } else {
         ecx = memory[memory[ebp+2]];
      }
      


      if(adr_mode) {
         edx = ebp+3; // TARGET MEM cell
      } else {
         edx = memory[ebp+3];
      }
      // add debug var
      if(DBG >= 1) {
         std::cout << "ebx(" << memory[ebp+1] << ") = " << ebx << std::endl;
         std::cout << "ecx(" << memory[ebp+2] << ") = " << ecx << std::endl;
         std::cout << "edx(" << memory[ebp+3] << ") = " << edx << std::endl;
      }
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
       * 3  - user input
       * 4  - output
       * 5  - jmp if true
       * 6  - jmp if false
       * 7  - less than
       * 8  - ==
       * 
       * 98 - fake user input (not from challeng)
       * 
       * 99 - halt
      */

      if(halt) {
         //TODO: show error
         return;
      }

      int steps = 4; // 4 is default
      
      switch(int(eax)) {
       case 1:

	      memory[edx] = ebx+ecx;
         //memory[edx] = memory[ebx] + memory[ecx];
	      break;
       case 2:
         memory[edx] = ebx*ecx;
	      //memory[edx] = memory[ebx] * memory[ecx];
	      break;
      case 3:
         float in;

         in = interface.get_input();
         memory[ebx] = in;
         steps = 2;
         break;
      case 4:
         interface.out_data(ebx,ebp);
         steps = 2;
         break;
      case 5:
      case 6:
         if(ebx != 0 && int(eax) == 5) {
            jmp(ecx);
            steps = 0;
         } else if(ebx == 0 && int(eax) == 6) {
            jmp(ecx);
            steps = 0;
         } else {
            steps = 3;
         }
         
         break;
      case 7:
         memory[edx] = (int(ebx < ecx)) ? 1 : 0;
         break;
      case 8:
         memory[edx] = (int(ebx == ecx)) ? 1 : 0;
         break;
      default:
         dump_memory();
	      std::cout << "ERROR: got opcode(" << ebp << "): " << eax << std::endl;
	      err = true;
       case 99:
	      runing = false;
	      halt = true;
	      break;
	   
	   }

      if(DBG >= 2 && eax != 4) {
         std::cout << "after comand: " << memory[edx] << std::endl;
      }

      ebp+=steps;
   }
   
   void step() {
      get_command();
      if(DBG >= 3) {
         system("read");
      }
      process_command();
      if(DBG >= 2) {
         system("read");
      }
   }
   
   void dump_memory() {
      std::cout << "=============memory dump============" << std::endl;
      for(int i = 0; i < memory.size(); i++) {      
	   
      std::cout << i;
      if(i <= ebp + 1 && i >= ebp - 1) {
         std::cout << ">: ";
      } else {
         std::cout << " : ";
      }

      switch(get_opcode(memory[i])) {
	      case 1:
	      case 2:
	         std::cout << memory[i]  << " " << memory[i+1] << " "  << memory[i+2] << " " << memory[i+3]  << std::endl;
	         i += 3;
            break;
         case 3:
         case 4:
            std::cout << memory[i]  << " " << memory[i+1] << std::endl;
            i += 1;
            break;
	      default:
	         std::cout << memory[i] << std::endl;
	         break;
	      }
      }
   std::cout << "====================================" << std::endl;
   }
};


