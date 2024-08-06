#include "MapReader.h"

#include <cstdio>
#include <fstream>
#include <sstream>

void MapReader::parse(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		std::fprintf(stderr, "Unable to open file: %s\n", filename.c_str());
		return;
	}

	std::string line;
	std::string currentTag;

	while (std::getline(file, line)) {
		line = trim(line);

		// Handle empty line
		if (line.empty()) {
			continue;
		}

		// Handle tag
		if (line.front() == '[' && line.back() == ']') {
			currentTag = line.substr(1, line.size() - 2);
			continue;
		}

		// Parse data based on current tag
		if (currentTag == "Meta") {
			parseMetaData(line);
		}
		else if (currentTag == "Tiles") {
			parseTileData(line);
		}
	}

	file.close();
}

void MapReader::print() const {
	std::printf("Meta Data:\n");
	for (const auto& meta : mMetaData) {
		std::printf("%s = %d\n", meta.first.c_str(), meta.second);
	}

	int width = mMetaData.at("Width");
	std::printf("Tile Data:\n");
	for (auto i = 0; i < mTiles.size(); i++) {
		std::printf("0x%X ", mTiles[i]);
		
		if (i > 0 && (i + 1) % width == 0) {
			std::printf("\n");
		}
	}
}

const std::unordered_map<std::string, int>& MapReader::getMetaData() const {
	return mMetaData;
}

const std::vector<int>& MapReader::getTileData() const {
	return mTiles;
}

void MapReader::parseMetaData(const std::string& line) {
	std::istringstream ss(line);
	std::string key;
	std::string value;

	if (std::getline(ss, key, '=') && std::getline(ss, value)) {
		key = trim(key);
		value = trim(value);
		mMetaData[key] = std::stoi(value);
	}
}

void MapReader::parseTileData(const std::string& line) {
	std::istringstream ss(line);
	std::string tile;

	while (ss >> tile) {
		mTiles.push_back(std::stoi(tile, nullptr, 16));
	}
}