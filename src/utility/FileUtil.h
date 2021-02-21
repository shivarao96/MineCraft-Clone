#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
std::string getFileContent(const std::string& filePath) {
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		std::cout << "Error opening file:: " + filePath << std::endl;
		throw std::runtime_error(filePath);
	}

	std::stringstream fileStream;
	fileStream << inputFile.rdbuf();

	return fileStream.str();
}