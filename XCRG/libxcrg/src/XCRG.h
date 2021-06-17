#ifndef XCRG_H
#define XCRG_H

#include "Include.h"
#include <vector>
#include "CRC32.h"

struct Chunk {
	uint32_t magic;
	uint32_t length;
	std::vector<uint8_t> data;
	uint32_t CRC;
};

// NOTE Make sure I read/write everything to file with little-endian byte order (or maybe allow different byte orders...?), regardless of the endianness of the host machine.
// htons()/htonl() and ntohs()/ntohl() are functions that reverse the byte order for 16-bit values and 32-bit values

// NOTE Add the ability to define an image with an XCRGInfo object, and then sorta stream the data in, to allow writing an image without at any point having the whole pixel data array in memory

namespace xcrg {
	template <typename SizeType, typename DimsType>
	Array<xuint8_t, SizeType> CreateXCRG(Array<xuint8_t, SizeType> pixelData, XCRGInfo<DimsType> info) {
		// A li'l static assertion to make sure we're using types that will work. Cause it's a static assert it'll throw error at compile-time which is nice
		static_assert(sizeof(DimsType) == 1 ? sizeof(SizeType) >= 4
			: (sizeof(DimsType) == 2 ? sizeof(SizeType) >= 8
			: (sizeof(DimsType) == 4 ? sizeof(SizeType) >= 16
			: (sizeof(DimsType) == 8 ? sizeof(SizeType) >= 32
			: false)))
		);

		Chunk infoChunk;
		infoChunk.magic = Magic_Chunk_INFO;
		infoChunk.length = 4 + sizeof(DimsType) * 2;
	}
}


#endif // XCRG_H
