# SPE
**S**trong **P**rotected **E**ncryption.

SPE is a small project I'm working on that let's you encrypt any of your files. Including Videos, executables, plain text, any file types.

## Installation

Just download the repository and compile with these flags or you could just run the SPE.exe file.
```bash
g++ -std=c++17 -o SPE.exe main.cpp include/HashLib/sha256.cpp include/SPE_Lib/SPE_Lib.cpp -I include/
```

## Usage

Run the executable (SPE.exe), type in the file name. (File must be in the same directory as the exe file can also be any type i.e. .jpg, .png, .exe), pick a salt. (just type in any characters or numbers but make sure to write them down so you dont forget them!) If you want to decrypt the file just run SPE.exe again pick the file and write in the salt that you have written down. 

I'm pretty sure this is really secure but don't take my word for it. there are a lot of smart people out there. I'm just saying this should be really difficult to crack.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
MIT License

```
Copyright (c) [10/1/2022] [Oskar]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
