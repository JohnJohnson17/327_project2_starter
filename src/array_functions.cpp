/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
#include "constants.h"
using namespace constants;
using namespace std;
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry {
	std::string word;
	int number_occurences;
};
//TODO add a global array of entry structs (global to this file)
entry * words = new entry[0];
//TODO add variable to keep track of next available slot in array
int tracker = 0;
//TODO define all functions in header file
void clearArray() {
tracker = 0;
}

int getArraySize() {
	return tracker;
}

std::string getArrayWordAt(int i) {
	return words[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
	return words[i].number_occurences;
}

bool processFile(std::fstream &myfstream) {
	if(!myfstream.is_open()) {
		return false;
	} else {
		std::string line;
		while(std::getline(myfstream, line)) {
			processLine(line);
		}
	}
	return true;
}

void processLine(std::string &myString) {
	stringstream ss(myString);

	std::string tempToken;

	while(getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

void processToken(std::string &token) {
	for(int i = 0; i < tracker;i++) {
			if (words[i].word == token) {
				words[i].number_occurences++;
				return;
			}
		}

	entry temp[tracker + 1];

	for(int i = 0 ; i < tracker ; i++){
		temp[i] = words[i];
	}

	temp[tracker].word = token;
	temp[tracker].number_occurences = 1;

	tracker++;

	delete[] words;

	words = temp;

}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

	myfile.open(myFileName.c_str(), mode);

	return myfile.is_open();
}

void closeFile(std::fstream& myfile) {
	if(myfile.is_open()) {
		myfile.close();
	}
}

int writeArraytoFile(const std::string &outputfilename) {
	ofstream myfile;
	myfile.open(outputfilename);
	if(!myfile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}

	if(tracker == 0) {
		return FAIL_NO_ARRAY_DATA;
	}

	for(int i = 0 ; i < tracker ; i++) {
		myfile << words[i].word + " " << words[i].number_occurences << "\n";
	}

	return SUCCESS;
}

void sortArray(constants::sortOrder so) {

}
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
