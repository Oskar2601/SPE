#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <windows.h>
#include <iomanip>

#define DEFAULTFILE "default.spe"


typedef unsigned char BYTE;

using std::cout;
using std::cin;
using std::endl;

char saltFunc(BYTE salt, char chr) {
   for(int i = 0; i < 8; i++) {
      if((salt >> i) & 1U) {
         chr ^= 1UL << i;
      }
   }

   return chr;
}

void outputLogo() {
   cout << "  /$$$$$$  /$$$$$$$  /$$$$$$$$" << endl;
   cout << " /$$__  $$| $$__  $$| $$_____/" << endl;
   cout << "| $$  \\__/| $$  \\ $$| $$      " << endl;
   cout << "|  $$$$$$ | $$$$$$$/| $$$$$   " << endl;
   cout << " \\____  $$| $$____/ | $$__/   " << endl;
   cout << " /$$  \\ $$| $$      | $$      " << endl;
   cout << "|  $$$$$$/| $$      | $$$$$$$$" << endl;
   cout << " \\______/ |__/      |________/" << endl << endl << endl;
}

int main () {
   unsigned int length;
   BYTE salt = 0x00;
   std::ifstream inputFile;
   std::ofstream encryptFile;
   std::string fileName;

   cin.unsetf(std::ios::dec);
   cin.unsetf(std::ios::hex);
   cin.unsetf(std::ios::oct);

   system("Color 0A");
   outputLogo();

   while(true) {
      cout << "input file name: ";
      cin >> fileName;

      if(fileName == "e") {
         inputFile = std::ifstream(DEFAULTFILE, std::ifstream::in | std::ios::binary);
         if(inputFile.fail()) {
            cout << "unable to open 'default.spe' are you sure that's a file?" << std::endl;
            continue;
         }

         encryptFile = std::ofstream(DEFAULTFILE, std::ifstream::in | std::ios::binary);
         break;
      }

      inputFile = std::ifstream(fileName, std::ifstream::in | std::ios::binary);
      if(inputFile.fail()){
         cout << "failed to access file. are you sure you entered the correct file name?" << std::endl << std::endl;
      }
      else
      {
         encryptFile = std::ofstream(fileName, std::ifstream::in | std::ios::binary);
         break;
      }
   }

   unsigned int hex = 0;
   cout << "enter salt (one byte hexadecimal with prefix (0x). i.e. 0xA2): ";
   cin >> std::hex >> hex;
   salt = hex;
   cout << endl << "Picked: " << (int)salt << endl;

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