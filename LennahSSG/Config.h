#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

class Config
{
    string _input;
    string _output;
    int _fileType;

  public:
    Config();
    string getConfig(int argc, char **argv);
    void readConfig(string inputFile);
    string getInput();
    string getOutput();
    int getFileType();
};
