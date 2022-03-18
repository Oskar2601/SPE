#include <HashLib/sha256.h>
#include <SPE_Lib/SPE_Lib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>

typedef unsigned char BYTE;

BYTE SPE::SaltByte(BYTE salt, BYTE chr) {
   for(int i = 0; i < 8; i++) {
      if((salt >> i) & 1U) {
         chr ^= 1UL << i;
      }
   }

   return chr;
}

void SPE::SetKey(std::string newKey) {
   SHA256 sha256;
   shaKey = sha256(newKey);
}

void SPE::SpeEncryptFile(std::string fileName) {
   std::ifstream inputFile;
   std::ofstream encryptFile;

   inputFile = std::ifstream(fileName, std::ifstream::in | std::ios::binary);
   encryptFile = std::ofstream(fileName, std::ifstream::in | std::ios::binary);

   unsigned int fileLength = 0;

   inputFile.seekg(0, inputFile.end);
   fileLength = inputFile.tellg();
   inputFile.seekg(0, inputFile.beg);

   char* fileBuffer = new char[fileLength];
   char* encryptFileBuffer = new char[fileLength];
   memset(fileBuffer, 0, fileLength);
   memset(encryptFileBuffer, 0, fileLength);

   while(inputFile.good()) { // just get file length in bytes.
      static int i = 0;
      fileBuffer[i] = inputFile.get();
      i++; 
   }

   unsigned int index = 0;
   std::stringstream stream;
   std::cout << "File length: " << fileLength << "bytes" << std::endl;
   for(int i = 0; i < fileLength; i++) {
      BYTE hexBuffer = 0;
      stream << shaKey[index] << shaKey[index + 1];
      stream >> std::hex >> hexBuffer;
      encryptFileBuffer[i] = SaltByte(hexBuffer, fileBuffer[i]);
      encryptFile << encryptFileBuffer[i];
      index += 2;
      if(index >= 63)
         index = 0;
   }

   inputFile.close();
   encryptFile.close();
   delete[] encryptFileBuffer;
   delete[] fileBuffer;
}