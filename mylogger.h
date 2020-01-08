#ifndef MYLOGGER_H
#define MYLOGGER_H

#include <iostream>
#include <string>

class MyLogger {
	bool debug;
	std::string possibleNewLine;
	std::string possibleProgramName;
	
  public:
    MyLogger() {
		setDebug(true);
		setNewLine(true);
	}
	
	void setNewLine(bool b) {
		if (b == true) {
			possibleNewLine = "\n";
		}
		else {
			possibleNewLine = "";
		}
	}
	
	void setDebug(bool b) {
		debug = b;
	}
	
	void setProgramName(const char *n) {
		possibleProgramName = n;
	}
	
	void log(const char* logMessage) {
		if (debug) {
			std::cout << "<= LOG => " << possibleProgramName << " => " << logMessage << possibleNewLine;
		}
	}
	void log(std::string logMessage) {
		if (debug) {
			std::cout << "<= LOG => " << possibleProgramName << " => " << logMessage << possibleNewLine;
		}
	}
	
	void operator()(const char* message) {
		log(message);
	}
	void operator()(std::string message) {
		log(message);
	}
};

#endif