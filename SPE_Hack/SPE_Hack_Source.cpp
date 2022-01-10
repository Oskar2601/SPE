#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define ENCRYPTFILE "Encrypted.spe"

typedef unsigned char BYTE; 

char saltFunc(BYTE salt, char chr) {
   for(int i = 0; i < 8; i++) {
      if((salt >> i) & 1U) {
         chr ^= 1UL << i;
         std::cout << "bit swapped: " << i << std::endl;
      }
   }
   return chr;
}

int main () {
   std::ofstream encryptFile(ENCRYPTFILE, std::ifstream::in);
   std::ifstream inputFile(ENCRYPTFILE, std::ifstream::in);
   char abcArray[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
   unsigned int length;
   BYTE salt = 0b00000000;

   inputFile.seekg(0, inputFile.end);
   length = inputFile.tellg();
   inputFile.seekg(0, inputFile.beg);


   char* fileBuffer = new char[length];
   char* decryptFileBuffer = new char[length];
   memset(fileBuffer, 0, length);
   memset(decryptFileBuffer, 0, length);

   while (inputFile.good()) { // just get file length in bytes.
      static int i = 0;
      fileBuffer[i] = inputFile.get();
      i++;
   }

   std::cout << "file size: " << length << std::endl;

   bool decrypted = false;
   salt = -127;
   while(salt < 255 && !decrypted) {
      salt++;
      for(int i = 0; i < length; i++) {
         decryptFileBuffer[i] = saltFunc(salt, fileBuffer[i]);
         for(int j = 0; j < 25; j++) {
            if(decryptFileBuffer[i] == abcArray[j]) {
               for(int i = 0; i < length; i++) {
                  decryptFileBuffer[i] = saltFunc(salt, fileBuffer[i]);
                  encryptFile << decryptFileBuffer[i];
                  decrypted = true;
                  break;
               }
            }
            else
            {
               break;
            }
         }
         encryptFile << decryptFileBuffer[i];
      }
   }

   inputFile.close();
   encryptFile.close();
   delete[] decryptFileBuffer;
   delete[] fileBuffer;
   return 0;
}