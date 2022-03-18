#include <string>

typedef unsigned char BYTE;

class SPE {
public:
   bool singleBitFlip = true;
   
   BYTE SaltByte(BYTE salt, BYTE chr);
   void SetKey(std::string newKey);
   void SpeEncryptFile(std::string fileName);

private:
   std::string shaKey = "1f5998b5f01949b961b0189099f8af47a73da3cce4521fd7d932d3ae518106f1";
};