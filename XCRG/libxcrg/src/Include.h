#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdint.h>

#define Magic_XCRG 0x58435247 // XCRG
#define Magic_Chunk_INFO 0x494e464f // INFO
#define Magic_Chunk_PIXD 0x50495844 // PIXD

#define Format_Mono1 0
#define Format_Mono8 1
#define Format_AlphaMono 2
#define Format_RGB16_555 3
#define Format_RGB16_565 4
#define Format_ARGB16 5
#define Format_RGB24 6
#define Format_ARGB24 7
#define Format_ARGB32 8
#define Format_RGB48 9
#define Format_ARGB64 10

template <typename DimType>
struct XCRGInfo {
	DimType width;
	DimType height;
	uint8_t formatId;
	uint8_t formatFlags;
	uint8_t compressionType;
};

#endif // INCLUDE_H