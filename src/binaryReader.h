typedef unsigned char byte;

struct binaryReader{
    byte* buffer;
    unsigned int buffer_size;
    FILE *binary;

    binaryReader();

    // return size
    int getBuffer();
}