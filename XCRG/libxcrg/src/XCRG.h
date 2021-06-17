#ifndef XCRG_H
#define XCRG_H

#include "Include.h"
#include <vector>

template <typename DimsType>
std::vector<uint8_t> CreateXCRG(std::vector<uint8_t> pixelData, XCRGInfo<DimsType> info);

#endif // XCRG_H
