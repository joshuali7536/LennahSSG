#include <iostream>
#include <string>

using namespace std;

class Formatter
{
  public:
    string italicize(string itLine);
    string boldify(string boldLine);
    string trim(string line);
    string inlineCode(string line);
};
