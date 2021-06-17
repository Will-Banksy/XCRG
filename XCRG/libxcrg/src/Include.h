#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdint.h>
#define WIDE_INTEGER_HAS_LIMB_TYPE_UINT64
#include "math/wide_integer/uintwide_t.h"

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

#define FormatFlags_Packed			0b00000001
#define FormatFlags_Premultiplied	0b00000010
#define FormatFlags_Reversed		0b00000100
#define FormatFlags_Floating		0b00001000
#define FormatFlags_Endianness		0b00010000

typedef uint8_t xuint8_t;
typedef uint16_t xuint16_t;
using xuint24_t = math::wide_integer::uintwide_t<24U, std::uint8_t>;
typedef uint32_t xuint32_t;
typedef uint64_t xuint64_t;
#ifdef __GNUC__
typedef unsigned __int128 xuint128_t;
#else
using xuint128_t = math::wide_integer::uintwide_t<128U>;
#endif
using xuint256_t = math::wide_integer::uintwide_t<256U>;
using xuint512_t = math::wide_integer::uintwide_t<512U>;
using xuint1024_t = math::wide_integer::uintwide_t<1024U>;

template <typename DimsType>
struct XCRGInfo {
	DimsType width;
	DimsType height;
	xuint8_t formatId;
	xuint8_t formatFlags;
	xuint8_t compressionType;
};

bool GetFlag(const xuint8_t flagsContainer, xuint8_t flag) {
	return (flagsContainer & flag) > 0;
}

void SetFlag(xuint8_t& flagsContainer, xuint8_t flag) {
	flagsContainer |= flag;
}

void UnsetFlag(xuint8_t& flagsContainer, xuint8_t flag) {
	flagsContainer &= ~flag;
}

template <typename T, typename SizeType = xuint64_t>
struct Array {
	T* ptr;
	SizeType size;
	bool onStack;

	Array(T* ptr, SizeType size, bool onStack = false) : ptr(ptr), size(size), onStack(onStack) {}
	explicit Array(SizeType size) : size(size) {
		ptr = new T[this->size];
	}

	~Array() {
		if(!onStack) {
			delete[] ptr;
		}
	}
};

#endif // INCLUDE_H