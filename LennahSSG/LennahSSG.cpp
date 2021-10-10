#include <iostream>
#include <fstream>
#include <string>
//#include <direct.h>
#include <filesystem>
#include <sys/stat.h>
#define VERSION 1.0

using namespace std;

void help_message();
void version_message();
void readTxt(string path, bool config);
bool checkConfig(int argc, char** argv);
string readConfig(string inputFile, string input, string output);
string italicize(string itLine);
string boldify(string boldLine);
string trim(string line);
string inlineCode(string line);
int fileType = 0;


int main(int argc, char** argv)
{
    //Checking number of arguments
    if (argc < 2) {
        help_message();
        return 1;
    }
    else if (argc == 2) {
        std::string arg = argv[1];
        if ((arg == "-v") || (arg == "--version")) {
            version_message();
            return 0;
        }
        else if ((arg == "-h") || (arg == "--help")) {
            help_message();
            return 0;
        }
        else {
            cout << "Not using proper arguments";
        }
    }
    else if (argc == 3) {
        std::string arg = argv[1];
        std::string argDetail = argv[2];
        bool config = checkConfig(argc, argv);
        if ((arg == "-c") || (arg == "--config")) {
            if (argDetail.find(".json") != string::npos) {
                    cout << "Converting: " << argDetail << endl;
                    fileType = 1;
                    readTxt(argDetail, config);
            }
        }
        if ((arg == "-i") || (arg == "--input")) {
        if (argDetail.find(".txt") != string::npos) {
                cout << "Converting: " << argDetail << endl;
                fileType = 1;
                readTxt(argDetail, config);
            }
            else if (argDetail.find(".md") != string::npos) {
                cout << "Converting: " << argDetail << endl;
                fileType = 2;
                readTxt(argDetail, config);
            }
            else {
                using fileIterator = filesystem::recursive_directory_iterator;
                for (const auto& dirEntry : fileIterator(argDetail)) {
                    string path = dirEntry.path().string();
                    if (path.find(".txt") != string::npos || path.find(".md") != string::npos) {
                        if (path.find(".txt") != string::npos) {
                            cout << "Converting: " << path << endl;
                                fileType = 1;
                                readTxt(path, config);
                        }
                        else if (path.find(".md") != string::npos) {
                        cout << "Converting: " << path << endl;
                        fileType = 2;
                        readTxt(path, config);
                    }
                    }
                }
            }
        }
    }

    return 0;
}

/*
 * help_message - Displays the arguments
 */
void help_message() {
    std::cout << "LENNAH - a static site generator" << endl;
    std::cout << "-----------------------------------" << endl;
    std::cout << "Arguments:" << endl;
    std::cout << "-i/--input <file/folder path>" << endl;
    std::cout << "-h/--help" << endl;
    std::cout << "-v/--version" << endl;
}

/*
 * version_message - Displays the version number of the application
 */
void version_message() {
    std::cout << "LENNAH V" << VERSION;
}
bool checkConfig(int argc, char** argv) {
    bool config = false;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-c" || string(argv[i]) == "--config") {
            config = true;
        }
    }
    return config;
}
string readConfig(string inputFile, string input, string output) {
    string storeConfig = "";
    ifstream configFile;
    configFile.open(inputFile, ios::in);
    if (configFile.is_open()) {
        getline(configFile, storeConfig, '}');
        configFile.close();
    }
        //if empty config
        if (storeConfig.find("\"") == string::npos) {
            cerr << "Config file is empty.";
            exit(1);
        }
        else {
            //if output folder is specified in config file
            if (storeConfig.find("output") != string::npos) {  
                size_t start = storeConfig.find("output") + 12;
                size_t end = storeConfig.find("\"", start - 1);
                output = storeConfig.substr(start, (end - start));
            }
            //get input from config file
            if (storeConfig.find("input") != string::npos)
            {
                size_t start = storeConfig.find("input") + 9;
                size_t end = storeConfig.find("\"", start + 2);
                input = storeConfig.substr(start, (end - start));
            }
        }
    return storeConfig;
}

/*
 * readTxt - reads and converts a txt file to an html file
 * path:    the file path of the txt file
 */
void readTxt(string path, bool config) {
    string title, line, output, input;
    ifstream inputFile;
    inputFile.open(path);
    if (!inputFile) {
        cout << "File not found. Please try again";
        exit(1);
    }
    //Delete folder if already exists
    std::filesystem::remove_all("./dist");
    if (config){
        readConfig(path, input, output);
    } else {
            //Create New Folder
            if (std::filesystem::create_directory("dist") != 0) {
                exit(1);
            }
    }
    //Creating Output file and inital html
    string base_filename = path.substr(path.find_last_of("/\\") + 1);
    string::size_type const p(base_filename.find_last_of('.'));
    string file_without_extension = base_filename.substr(0, p);
    string newHTML = output + file_without_extension + ".html";
    ofstream outputFile(newHTML);

    title = file_without_extension;

    if (inputFile.is_open()) {

        outputFile << "<!doctype html>\n"
            << "<html lang = \"en\">\n"
            << "<head>\n"
            << "<meta charset=\"utf-8\">\n"
            << "<title>";

        if (fileType == 1) {
            

            //Getting Title     
            string line1, line2, line3;
            bool hasTitle = false;
            getline(inputFile, line1);
            getline(inputFile, line2);
            getline(inputFile, line3);

            if (line1 != "" && line2 == "" && line3 == "") {
                title = line1;
                hasTitle = true;
            }
            outputFile << title;
        }
       

        outputFile << "</title>\n"
            << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            << "</head>\n"
            << "<body>\n";

        outputFile << "<h1>" << title << "</h1>\n";


        //Reading input file
        string prevLine;
        while (getline(inputFile, line)) {
            //markdown
            if (fileType == 2) {
                if (line.find("**") != string::npos || line.find("__") != string::npos) {
                    line = boldify(line);
                }            
                if (line.find("*") != string::npos || line.find("_") != string::npos) {
                    line = italicize(line);
                }
                if (line.find("`") != string::npos) {
                    line = inlineCode(line);
                }

                if (trim(line) == "---") {
                    line = "<hr>";
                }
            }

            //format <p> tags
            if (prevLine == "" && line != "") {
               outputFile << "<p>\n"                
                    << line << "\n";
            }
            else if (prevLine != "" && line == "") {
                outputFile << "</p>\n";
            }
            else {
                outputFile << line << "\n";
            }

            prevLine = line;
        }

        inputFile.close();
    }


    outputFile << "</body>\n"
        << "</html>";

    outputFile.close();
}
string italicize(string itLine) {
    while (itLine.find("*") != string::npos || itLine.find("_")) {
        if (itLine.find("*") != string::npos && itLine.find("*") != itLine.find_last_of("*")) {
            itLine.replace(itLine.find("*"), 1, "<i>");
            itLine.replace(itLine.find_last_of("*"), 1, "</i>");            
        }
        else if (itLine.find("_") != string::npos && itLine.find("_") != itLine.find_last_of("*")) {
            itLine.replace(itLine.find("_"), 1, "<i>");
            itLine.replace(itLine.find_last_of("_"), 1, "</i>");            
        }
        else {
            return itLine;
        }
    }
    return itLine;
}
string boldify(string boldLine) {
    while (boldLine.find("**") != string::npos || boldLine.find("__") != string::npos) {
        if (boldLine.find("**") != string::npos && boldLine.find("**") != boldLine.find_last_of("**")) {
            boldLine.replace(boldLine.find("**"), 2, "<b>");
            boldLine.replace(boldLine.find_last_of("**") - 1, 2, "</b>");            
        }
        else if (boldLine.find("__") != string::npos && boldLine.find("__") != boldLine.find_last_of("__")) {
            boldLine.replace(boldLine.find("__"), 1, "<b>");
            boldLine.replace(boldLine.find_last_of("__"), 1, "</b>");            
        }
        else {
            return boldLine;
        }
    }    
    return boldLine;
}
string trim(string line)
{
    const char* WhiteSpace = " \t\v\r\n";
    size_t start = line.find_first_not_of(WhiteSpace);
    size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? string() : line.substr(start, end - start + 1);
}
string inlineCode(string line) {
    while (line.find("`") != string::npos) {
        if (line.find("`") != string::npos && line.find("`") != line.find_last_of("`")) {
            line.replace(line.find("`"), 1, "<code>");
            line.replace(line.find("`"), 1, "</code>");
        }
        else {
            return line;
        }
    }
    return line;
}