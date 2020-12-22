#include "Graph.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// gets the contents of the file located at filePath
//@param string filePath the path to the file
//@return the contents of the file in a string vector
vector<tuple<int *, int *, double> > getFileContentsIntData(string filePath) {
  vector<tuple<int *, int *, double> > data; // raw input data from file
  ifstream infile;
  infile.open(filePath); // open the filename supplied
  string line;
  string word;
  int numWordsRead;
  map<int, int *> uniqueData;

  // while there are lines to read in the file
  while (getline(infile, line)) {
    numWordsRead = 0;
    // if its the first line of the file ignore it for vector making purposes
    if (line == "directed" || line == "undirected")
      continue;
    tuple<int *, int *, double> current;
    // read each word of the line using an input string stream
    istringstream iss(line, istringstream::in);
    // while there's a word to read on this line
    while (iss >> word) {
      if (numWordsRead == 0) {
        if (uniqueData.find(stoi(word)) != uniqueData.end()) {
          get<0>(current) = uniqueData[stoi(word)];
        } else {
          int *newInt = new int;
          *newInt = stoi(word);
          get<0>(current) = newInt;
          uniqueData[stoi(word)] = newInt;
        }
      } else if (numWordsRead == 1) {
        if (uniqueData.find(stoi(word)) != uniqueData.end()) {
          get<1>(current) = uniqueData[stoi(word)];
        } else {
          int *newInt = new int;
          *newInt = stoi(word);
          get<1>(current) = newInt;
          uniqueData[stoi(word)] = newInt;
        }
      } else {
        double weight = stod(word);
        get<2>(current) = weight;
      }
      numWordsRead++;
    }
    // push those lines to the end of the vector
    data.push_back(current);
  }
  infile.close();
  // return our vector
  return data;
}

bool isDirected(string filePath) {
  ifstream infile;
  infile.open(filePath);
  string line;
  getline(infile, line);
  infile.close();
  if (line == "directed")
    return true;
  else
    return false;
}

vector<tuple<string *, string *, double> >
getFileContentsStringData(string filePath) {
  vector<tuple<string *, string *, double> > data; // raw input data from file
  ifstream infile;
  infile.open(filePath); // open the filename supplied
  string line;
  string word;
  int numWordsRead;
  map<string, string *> uniqueData;

  // while there are lines to read in the file
  while (getline(infile, line)) {
    numWordsRead = 0;
    // if its the first line of the file ignore it for vector making purposes
    if (line == "directed" || line == "undirected")
      continue;
    tuple<string *, string *, double> current;
    // read each word of the line using an input string stream
    istringstream iss(line, istringstream::in);
    // while there's a word to read on this line
    while (iss >> word) {
      if (numWordsRead == 0) {
        if (uniqueData.find(word) != uniqueData.end()) {
          get<0>(current) = uniqueData[word];
        } else {
          string *newWord = new string(word);
          get<0>(current) = newWord;
          uniqueData[word] = newWord;
        }
      } else if (numWordsRead == 1) {
        if (uniqueData.find(word) != uniqueData.end()) {
          get<1>(current) = uniqueData[word];
        } else {
          string *newWord = new string(word);
          get<1>(current) = newWord;
          uniqueData[word] = newWord;
        }
      } else {
        double weight = stod(word);
        get<2>(current) = weight;
      }
      numWordsRead++;
    }
    // push those lines to the end of the vector
    data.push_back(current);
  }
  infile.close();
  // return our vector
  return data;
}

// Display usage information to cout
void usage() {
  cout << "Input path to graph input file in command line" << endl;
  cout << "Example: g++ GraphRunner.cpp ./CSCI222/lab5/GraphInput1.txt" << endl;
  cout << "note: file format is as follows"
          "line 1: \"directed\" or \"undirected\" graph\n\nrest of lines "
          "define "
          "edges in format: vertexFrom vertexTo weight\nexample: A B "
          "3.5\nexample: hotdog burger 5.3\nexample: 4 2 3.4"
       << endl;
}

int main(int argc, char const *argv[]) {
  // if there isn't at least 1 argument (argv[0] is filename)
  if (argc < 2) {
    usage();  // display usage info
    return 0; // exit program
  }

  vector<tuple<string *, string *, double> > stringFileContents =
      getFileContentsStringData(argv[1]);
  Graph<string> stringGraph(stringFileContents, isDirected(argv[1]));
  cout << stringGraph << endl;
  cout << "Outdegree of " << *stringGraph.getData(3) << ": "
       << stringGraph.getDegree(stringGraph.getData(3)) << endl;
  cout << "Outdegree of " << *stringGraph.getData(4) << ": "
       << stringGraph.getDegree(stringGraph.getData(4)) << endl;

  vector<tuple<int *, int *, double> > intFileContents =
      getFileContentsIntData(argv[2]);
  Graph<int> intGraph(intFileContents, isDirected(argv[2]));

  cout << "howdy doody" << endl;
  return 0;
}
