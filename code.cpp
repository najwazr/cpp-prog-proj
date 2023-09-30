#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream inFile;
    ofstream outFile;
    string sentence;

    inFile.open("input.txt");
    outFile.open("output.json");

    if (!inFile.is_open()) {
        cerr << "Error! Unable to open input file." << endl;
        return 1;
    }

    if (!outFile.is_open()) {
        cerr << "Error! Unable to open output file." << endl;
        return 1;
    }

    getline(inFile, sentence);
    transform(sentence.begin(), sentence.end(), sentence.begin(), [](unsigned char c){ return tolower(c); });
    sentence.erase(remove_if(sentence.begin(), sentence.end(), ::ispunct), sentence.end());

    istringstream iss(sentence);
    unordered_map<string, int> wordCount;
    string word;

    while (iss >> word) {
        wordCount[word]++;
    }

    outFile << "{" << endl;
    istringstream iss2(sentence);
    while (iss2 >> word) {
        if (wordCount[word] > 0) {
            outFile << "  \"" << word << "\":" << wordCount[word] << "," << endl;
            wordCount[word] = 0;
        }
    }
    outFile << "}" << endl;

    inFile.close();
    outFile.close();
    return 0;
}