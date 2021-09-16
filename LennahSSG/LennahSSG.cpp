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
            size_t isFile = argDetail.find(".txt");
            if (isFile != string::npos) {
                cout << "Converting: " << argDetail << endl;
                readTxt(argDetail);
            }
            else {
                using fileIterator = filesystem::recursive_directory_iterator;
                for (const auto& dirEntry : fileIterator(argDetail)) {
                    string path = dirEntry.path().string();
                    size_t isTxt = path.find(".txt");
                    if (isTxt != string::npos) {
                        cout << "Converting: " << path << endl;
                        readTxt(path);
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
    string line;
    string title, line1, line2, line3;
    bool hasTitle = false;

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


        //Getting Title
        outputFile << "<!doctype html>\n"
            << "<html lang = \"en\">\n"
            << "<head>\n"
            << "<meta charset=\"utf-8\">\n"
            << "<title>";

        getline(inputFile, line1);
        getline(inputFile, line2);
        getline(inputFile, line3);

        if (line1 != "" && line2 == "" && line3 == "") {
            title = line1;
            hasTitle = true;
        }

        outputFile << title;

        outputFile << "</title>\n"
            << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            << "</head>\n"
            << "<body>\n";

        outputFile << "<h1>" << title << "</h1>\n";


        //Reading input file
        string prevLine;
        while (getline(inputFile, line)) {
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