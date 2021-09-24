#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <filesystem>
#include <sys/stat.h>
#define VERSION 1.0

using namespace std;

void help_message();
void version_message();
void readTxt(string path);
string italicize(string itLine);
string boldify(string boldLine);
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
        if ((arg == "-i") || (arg == "--input")) {

            //Delete folder if already exists
            std::filesystem::remove_all("./dist");
            //Create New Folder
            if (_mkdir("./dist") != 0) {
                exit(1);
            }

            //Check if argument is Folder or txt File


            if (argDetail.find(".txt") != string::npos) {
                cout << "Converting: " << argDetail << endl;
                fileType = 1;
                readTxt(argDetail);
            }
            else if (argDetail.find(".md") != string::npos) {
                cout << "Converting: " << argDetail << endl;
                fileType = 2;
                readTxt(argDetail);
            }
            else {
                using fileIterator = filesystem::recursive_directory_iterator;
                for (const auto& dirEntry : fileIterator(argDetail)) {
                    string path = dirEntry.path().string();
                    if (path.find(".txt") != string::npos || path.find(".md") != string::npos) {
                        if (path.find(".txt") != string::npos) {
                            cout << "Converting: " << path << endl;
                                fileType = 1;
                                readTxt(path);
                        }
                        else if (path.find(".md") != string::npos) {
                        cout << "Converting: " << path << endl;
                        fileType = 2;
                        readTxt(path);
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
static void help_message() {
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
static void version_message() {
    std::cout << "LENNAH V" << VERSION;
}

/*
 * readTxt - reads and converts a txt file to an html file
 * path:    the file path of the txt file
 */
static void readTxt(string path) {
    string title, line;

    ifstream inputFile;
    inputFile.open(path);
    if (!inputFile) {
        cout << "File not found. Please try again";
        exit(1);
    }
    //Creating Output file and inital html
    string base_filename = path.substr(path.find_last_of("/\\") + 1);
    string::size_type const p(base_filename.find_last_of('.'));
    string file_without_extension = base_filename.substr(0, p);
    string newHTML = "./dist/" + file_without_extension + ".html";
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