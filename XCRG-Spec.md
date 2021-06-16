# XCRG - eXtensible Chunked Raster Graphic

Designed to be simple, extensible and flexible

## XCRG File Format

1. Magic: 4 bytes - 58 43 52 47 | XCRG
2. Any number of chunks in any order

## Chunks

The actual file data is split into chunks, each chunk holding specific data about the image

### Chunk Format

- Chunk Magic: 4 bytes
- Chunk Length: 4 bytes
- Chunk Data: Length bytes
- Chunk CRC: 4 bytes (Note to self: A CRC library: [https://github.com/panzi/CRC-and-checksum-functions](https://github.com/panzi/CRC-and-checksum-functions))

### Standard Chunks

- INFO - Information about the image
- PIXD - The array of pixel data. There may be multiple PIXD chunks

### Chunk Specs

#### INFO

1. Chunk Magic: 49 4e 46 4f | INFO
2. Chunk Length: variable
3. Chunk Data:
    - Dimension Size: 1 byte
        - The amount of bytes to use for the dimensions. Only 1, 2, 4, 8, 16, 32 are to be used - Readers are only required to support up to 8 byte dimensions
    - Width: variable bytes
    - Height: variable bytes
    - Format ID: 1 byte
        - Refer to [Formats](#formats) section
    - Format Flags
        - (MSB) - - - En Fl Rv Pr Pa
            - Pa - Packed
                - Whether the bits in the pixel data are packed or not. No effect when using a format such as ARGB-32 that takes up complete bytes
            - Pr - Premultiplied
                - Whether the alpha is premultiplied or not. Ignored when there is not alpha channel
            - Rv - Reversed
                - Whether the channel order is reversed or not. E.g. ARGB becoming BGRA
            - Fl - Floating
                - Whether each channel is a floating-point number or not. Ignored for channels that are not either 32-bit or 64-bit - Currently not available in the defined formats
            - En - Endianness
                - The endianness of the pixel data. 0 is little-endian, 1 is big-endian
    - Compression: 1 byte
        - The type of compression algorithm to use (Note to self: include compression algorithms (including lossy compression) specific to images such as JPEG compression)
            0. No compression
            1. LZO
            2. Deflate
            3. LZMA

#### PIXD

1. Chunk Magic: 50 49 58 44 | PIXD
2. Chunk Length: variable
3. Chunk Data:
    - Index: 4 bytes
        - This is the index of this PIXD chunk. The index of the chunk defines where the data held by this chunk fits into the overarching array - To construct the complete pixel data you take the pixel data from each PIXD chunk and order them by index
        - So the pixel data of chunk with index 0 goes first, then pixel data of chunk with index 1, then 2, 3, etc.
    - Simply an array of bytes. The [INFO](#info) section contains information on how to interpret it

## Formats

XCRG recognises various formats. (Note to self: Custom formats?)

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

