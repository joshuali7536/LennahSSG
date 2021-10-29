#include "FileReader.h"


/*
 * readTxt - reads and converts a .txt or .md file to an html file
 * path:    the file path of the .txt/.md file
 * config:  bool if there was a config file given
 * 
 * returns the name of the newly generated html file
 */
string FileReader::convertFile(string input, string output, int fileType, bool isFolder)
{
    Formatter format;
    string title, line;

    


    ifstream inputFile;
    inputFile.open(input);
    if (!inputFile)
    {
        cout << "File not found. Please try again";
        exit(1);
    }
    //Creating Output file and inital html
    string base_filename = input.substr(input.find_last_of("/\\") + 1);
    string::size_type const p(base_filename.find_last_of('.'));
    string file_without_extension = base_filename.substr(0, p);
    string newHTML = output + file_without_extension + ".html";
    ofstream outputFile(newHTML);
    title = file_without_extension;

    if (inputFile.is_open())
    {

        outputFile << "<!doctype html>\n"
            << "<html lang = \"en\">\n"
            << "<head>\n"
            << "<meta charset=\"utf-8\">\n"
            << "<title>";

        if (fileType == 1)
        {

            //Getting Title
            string line1, line2, line3;
            bool hasTitle = false;
            getline(inputFile, line1);
            getline(inputFile, line2);
            getline(inputFile, line3);

            if (line1 != "" && line2 == "" && line3 == "")
            {
                title = line1;
                hasTitle = true;
            }
            outputFile << title;
        }

        outputFile << "</title>\n"
            << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            << "</head>\n"
            << "<body>\n";

        if (isFolder)
            outputFile << "<a href=\"index.html\">Home Page</a>\n";

        outputFile << "<h1>" << title << "</h1>\n";

        //Reading input file
        string prevLine;
        while (getline(inputFile, line))
        {
            //markdown
            if (fileType == 2)
            {
                if (line.find("**") != string::npos || line.find("__") != string::npos)
                {
                    line = format.boldify(line);
                }
                if (line.find("*") != string::npos || line.find("_") != string::npos)
                {
                    line = format.italicize(line);
                }
                if (line.find("`") != string::npos)
                {
                    line = format.inlineCode(line);
                }

                if (format.trim(line) == "---")
                {
                    line = "<hr>";
                }
            }

            //format <p> tags
            if (prevLine == "" && line != "")
            {
                outputFile << "<p>\n"
                    << line << "\n";
            }
            else if (prevLine != "" && line == "")
            {
                outputFile << "</p>\n";
            }
            else
            {
                outputFile << line << "\n";
            }

            prevLine = line;
        }

        inputFile.close();
    }

    outputFile << "</body>\n"
        << "</html>";

    outputFile.close();
    return file_without_extension;
}