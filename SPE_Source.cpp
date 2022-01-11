#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <windows.h>

#define DEFAULTFILE "default.spe"

typedef unsigned char BYTE; 

char saltFunc(BYTE salt, char chr) {
   for(int i = 0; i < 8; i++) {
      if((salt >> i) & 1U) {
         chr ^= 1UL << i;
      }
   }

   return chr;
}

void outputLogo() {
   std::cout << "  /$$$$$$  /$$$$$$$  /$$$$$$$$" << std::endl;
   std::cout << " /$$__  $$| $$__  $$| $$_____/" << std::endl;
   std::cout << "| $$  \\__/| $$  \\ $$| $$      " << std::endl;
   std::cout << "|  $$$$$$ | $$$$$$$/| $$$$$   " << std::endl;
   std::cout << " \\____  $$| $$____/ | $$__/   " << std::endl;
   std::cout << " /$$  \\ $$| $$      | $$      " << std::endl;
   std::cout << "|  $$$$$$/| $$      | $$$$$$$$" << std::endl;
   std::cout << " \\______/ |__/      |________/" << std::endl << std::endl << std::endl;
}

int main () {
   unsigned int length;
   BYTE salt = 0b00000000;
   std::ifstream inputFile;
   std::ofstream encryptFile;
   std::string fileName;

   system("Color 05");
   outputLogo();

   while(true) {
      std::cout << "input file name: ";
      std::cin >> fileName;

      if(fileName == "e") {
         inputFile = std::ifstream(DEFAULTFILE, std::ifstream::in | std::ios::binary);
         if(inputFile.fail()) {
            std::cout << "unable to open 'default.spe' are you sure that's a file?" << std::endl;
            continue;
         }

         encryptFile = std::ofstream(DEFAULTFILE, std::ifstream::in | std::ios::binary);
         break;
      }

      inputFile = std::ifstream(fileName, std::ifstream::in | std::ios::binary);
      if(inputFile.fail()){
         std::cout << "failed to access file. are you sure you entered the correct file name?" << std::endl << std::endl;
      }
      else
      {
         encryptFile = std::ofstream(fileName, std::ifstream::in | std::ios::binary);
         break;
      }
   }

   std::cout << "enter salt (one byte hexadecimal or binary i.e. 0xA2 or 0b10100010): ";
   int input;
   std::cin >> std::hex >> input;
   salt = input;
   std::cout << std::endl;

   std::cin.unsetf(std::ios::dec);
   std::cin.unsetf(std::ios::hex);
   std::cin.unsetf(std::ios::oct);

   //std::cout << "input salt in hex with a prefix 0x so for example. 0xA2" << std::endl;
   //std::cin >> std::hex >> salt;

   inputFile.seekg(0, inputFile.end);
   length = inputFile.tellg();
   inputFile.seekg(0, inputFile.beg);

   std::string* names = new std::string[length];

   char* fileBuffer = new char[length];
   char* encryptFileBuffer = new char[length];
   memset(fileBuffer, 0, length);
   memset(encryptFileBuffer, 0, length);

   while (inputFile.good()) { // just get file length in bytes.
      static int i = 0;
      fileBuffer[i] = inputFile.get();
      i++;
   }

   for(int i = 0; i < length; i++) {
      encryptFileBuffer[i] = saltFunc(salt, fileBuffer[i]);
      encryptFile << encryptFileBuffer[i];
   }

   inputFile.close();
   encryptFile.close();
   delete[] encryptFileBuffer;
   delete[] fileBuffer;
   system("pause");
   return 0;
}