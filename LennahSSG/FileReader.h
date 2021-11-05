#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Formatter.h"

using namespace std;

class FileReader
{
  public:
    string convertFile(string input, string output, int fileType, bool isFolder);
};
