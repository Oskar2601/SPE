#include <SPE_Lib/SPE_Lib.h>
#include <filesystem>
#include <windows.h>
#include <iostream>
#include <string>

#define DEFAULTFILE "default.spe"


typedef unsigned char BYTE;

using std::cout;
using std::cin;
using std::endl;

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
   std::string fileName;

   SPE spe;

   system("Color 0A");
   outputLogo();

   while(true) {
      cout << "input file name: ";
      cin >> fileName;

      if(fileName == "e") {
         fileName = DEFAULTFILE;
         if(!std::filesystem::exists(fileName)) {
            cout << "unable to open 'default.spe' are you sure that's a file?" << std::endl;
            continue;
         }

         break;
      }

      if(!std::filesystem::exists(fileName)){
         cout << "failed to access file. are you sure you entered the correct file name?" << std::endl;
      }
      else
      {
         break;
      }
   }

   std::string newKey;
   cout << "enter a key (will be converted to sha256): ";
   cin >> newKey;
   spe.SetKey(newKey);
   newKey.clear();

   spe.SpeEncryptFile(fileName);

   system("pause");
   return 0;
}