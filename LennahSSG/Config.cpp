#include "Config.h"


Config::Config() {
    _input = "";
    _output = "./dist";
    _fileType = 0;
}

/*
 * checkConfig - Checks arguments for --config or -c
 * argc:    number of commandline arguments
 * argv:    array of commandline arguments
 *
 * returns a bool if config was a given argument
 */
string Config::getConfig(int argc, char** argv)
{
    string configName;
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-c" || string(argv[i]) == "--config")
        {
            configName = argv[i + 1];
        }
    }
    return configName;
}

/*
 * readConfig - Reads a config JSON file for arguments
 * inputFile:   config file path
 *
 * returns a string containing the JSON
 */
void Config::readConfig(string inputFile)
{
    string storeConfig = "";
    ifstream configFile;
    configFile.open(inputFile, ios::in);
    if (configFile.is_open())
    {
        getline(configFile, storeConfig, '}');
        configFile.close();
    }
    //if empty config
    if (storeConfig.find("\"") == string::npos)
    {
        cerr << "Config file is empty.";
        exit(1);
    }
    else
    {
        //if output folder is specified in config file
        if (storeConfig.find("output") != string::npos)
        {
            size_t start = storeConfig.find("output") + 12;
            size_t end = storeConfig.find("\"", start - 1);
            _output = storeConfig.substr(start, (end - start));
            _output += "/";
        }

        //get input from config file
        if (storeConfig.find("input") != string::npos)
        {
            size_t start = storeConfig.find("input") + 11;
            size_t end = storeConfig.find("\"", start + 2);
            _input = storeConfig.substr(start, (end - start));
            if (_input.find(".txt") != string::npos)
            {
                _fileType = 1;
            }
            else if (_input.find(".md") != string::npos)
            {
                _fileType = 2;
            }
        }

    }
}

string Config::getInput()
{
    return _input;
}

string Config::getOutput()
{
    return _output;
}

int Config::getFileType()
{
    return _fileType;
}