#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define ENCRYPTFILE "Encrypted.cfd"
#define INPUTFILE "FileToEncrypt.txt"

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
  unsigned int length;
  BYTE salt = 0b01100010;

  std::cin.unsetf(std::ios::dec);
  std::cin.unsetf(std::ios::hex);
  std::cin.unsetf(std::ios::oct);

  //std::cout << "input salt in hex with a prefix 0x so for example. 0xA2" << std::endl;
  //std::cin >> std::hex >> salt;
  
  inputFile.seekg(0, inputFile.end);
  length = inputFile.tellg();
  inputFile.seekg(0, inputFile.beg);

  
  char* fileBuffer = new char[length];
  char* encryptFileBuffer = new char[length];
  memset(fileBuffer, 0, length);
  memset(encryptFileBuffer, 0, length);

  while (inputFile.good()) { // just get file length in bytes.
    static int i = 0;
    fileBuffer[i] = inputFile.get();
    i++;
  }

  std::cout << "file size: " << length << std::endl;

  for(int i = 0; i < length; i++) {
    encryptFileBuffer[i] = saltFunc(salt, fileBuffer[i]);
    encryptFile << encryptFileBuffer[i];
  }

  inputFile.close();
  encryptFile.close();
  delete[] encryptFileBuffer;
  delete[] fileBuffer;
  return 0;
}