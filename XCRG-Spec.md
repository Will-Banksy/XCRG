# XCRG - eXtensible Chunked Raster Graphic

Designed to be extensible and highly flexible

## Chunks

The file is split into chunks, each chunk holding specific data about the image

### Chunk Format

- Chunk Magic: 4 bytes
- Chunk Length: 4 bytes
- Chunk Data: Length bytes
- Chunk CRC: 4 bytes (Note to self: A CRC library: [https://github.com/panzi/CRC-and-checksum-functions](https://github.com/panzi/CRC-and-checksum-functions))

### Standard Chunks

- INFO - Information about the image
- PIXD - The array of pixel data

### Chunk Specs

#### INFO

1. Chunk Magic: 49 4e 46 4f | INFO
2. Chunk Length: variable
3. Chunk Data:
    - Dimension Size: 1 byte
        - The amount of bytes to use for the dimensions. Only 1, 2, 4, 8, 16 are to be used
    - Width: variable bytes
    - Height: variable bytes
    - Format ID: 1 byte
        - Refer to [Formats](#formats) section
    - Flags
        - (MSB) - - - - - Rv Pr Pa
            - Pa - Packed
                - Whether the bits in the pixel data are packed or not. No effect when using a format such as ARGB-32 that takes up complete bytes
            - Pr - Premultiplied
                - Whether the alpha is premultiplied or not. Ignored when there is not alpha channel
            - Rv - Reversed
                - Whether the channel order is reversed or not. E.g. ARGB becoming BGRA

#### PIXD

1. Chunk Magic: 50 49 58 44 | PIXD
2. Chunk Length: variable
3. Chunk Data:
    - Simply an array of bytes. The [INFO](#info) section contains information on how to interpret it

## Formats

XCRG recognises various formats.

Each format has a numeric ID used in the format field in the [INFO](#info) section, and a name (in brackets) used to refer to it

0. 1-bpp monochrome (Mono1)
    - This format uses 1 bit per pixel to represent an image comprised of only 2 colours, typically white (1) and black (0)
1. 8-bpp monochrome (Mono8)
    - This format uses 8 bits (1 byte) per pixel to represent an image comprised of one channel, typically white to represent a greyscale image
2. 16-bpp monochrome & alpha (AlphaMono16)
    - As above, but with an 8-bit alpha channel. The order is AC, where A is alpha and C is the colour channel
4. 16-bpp RGB555 (RGB16_555)
    - Uses 5 bits for each of the channels, red, green and blue. The order is RGB
6. 16-bpp RGB565 (RGB16_565)
    - Same as above but uses 6 bits for the green channel, as the human eye is most sensitive to green. This means it takes up the full 2 bytes without leaving a bit out like the previous format. The order is RGB
7. 16-bpp ARGB (ARGB16)
    - Uses 4 bits for each of the channels, alpha, red, green and blue. The order is ARGB
8. 24-bpp RGB (RGB24)
    - Uses 8 bits for each of the channels, red, green and blue. The order is RGB
9. 24-bpp ARGB (ARGB24)
    - Uses 6 bits for each of the channels, alpha, red, green and blue. The order is ARGB
10. 32-bpp ARGB (ARGB32)
    - Uses 8 bits for each of the channels, alpha, red, green and blue. The order is ARGB
11. 48-bpp RGB (RGB48)
    - Uses 16 bits for each of the channels, red, green and blue, The order is RGB
13. 64-bpp ARGB (ARGB64)
    - Uses 16 bits (2 bytes) for each of the channels, alpha, red, green and blue. The order is ARGB

(Note to self: Possibly add more. Look at Qt's supported QImage formats: [https://doc.qt.io/qt-5/qimage.html#Format-enum](https://doc.qt.io/qt-5/qimage.html#Format-enum))

## XCRG File Format

1. Magic: 4 bytes - 58 43 52 47 | XCRG
2. Any number of chunks in any order
