#include <iostream>
#include "libxcrg/src/XCRG.h"

int main() {
    std::cout << "Hello, world!" << std::endl;

	xcrg::CreateXCRG(Array<xuint8_t>(8), XCRGInfo<xuint8_t>());

    return 0;
}
