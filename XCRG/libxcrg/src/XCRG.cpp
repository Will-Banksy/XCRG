#include "XCRG.h"

struct Chunk {
	uint32_t magic;
	uint32_t length;
	std::vector<uint8_t> data;
};

template<typename DimsType>
std::vector<uint8_t> CreateXCRG(std::vector<uint8_t> pixelData, XCRGInfo<DimsType> info) {
}
