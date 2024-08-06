#pragma once

#include <string>
#include <vector>
#include <unordered_map>

constexpr std::string trim(const std::string& str) {
	std::size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) {
		return "";
	}

	std::size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

class MapReader {
public:
	void parse(const std::string& filename);
	void print() const;

	const std::unordered_map<std::string, int>& getMetaData() const;
	const std::vector<int>& getTileData() const;

private:
	std::unordered_map<std::string, int> mMetaData;
	std::vector<int> mTiles;

	void parseMetaData(const std::string& line);
	void parseTileData(const std::string& line);
};

