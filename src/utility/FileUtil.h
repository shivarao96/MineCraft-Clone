#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string getFileContent(const std::string& filePath) {
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		throw std::runtime_error("Error opening file:: " + filePath);
	}

	std::stringstream fileStream;
	fileStream << inputFile.rdbuf();

	return fileStream.str();
}