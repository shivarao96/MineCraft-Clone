#include "blockData.h"

#include <iostream>
#include <fstream>

BlockData::BlockData(const std::string& blockName) {
	std::ifstream inFile("assets/blocks/" + blockName + ".block");
	if (!inFile.is_open()) {
		std::cout << "Failed to open the block file:: " << blockName << std::endl;
		throw std::runtime_error("Failed to open block file");
	}

	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "TexTop") {
			int x, y;
			inFile >> x >> y;
			m_blockDataHolder.texTopCoords    = { x,y };
		}
		if (line == "TexSide") {
			int x, y;
			inFile >> x >> y;
			m_blockDataHolder.texSideCoords   = { x,y };
		}
		if (line == "TexBottom") {
			int x, y;
			inFile >> x >> y;
			m_blockDataHolder.texBottomCoords = { x,y };
		}
		if (line == "TexAll") {
			int x, y;
			inFile >> x >> y;
			m_blockDataHolder.texTopCoords    = { x,y };
			m_blockDataHolder.texSideCoords   = { x,y };
			m_blockDataHolder.texBottomCoords = { x,y };
		}
		if (line == "Id") {
			int i;
			inFile >> i;
			m_blockDataHolder.id = static_cast<BlockId>(i);
		}
		if (line == "Opaque") {
			inFile >> m_blockDataHolder.isOpaque;
		}
		if (line == "MeshType") {
			int i;
			inFile >> i;
			m_blockDataHolder.meshType = static_cast<BlockMeshType>(i);
		}
		
	}

}
const BlockDataHolder& BlockData::getBlockData() const {
	return m_blockDataHolder;
}