#include "bytearray.h"
#include <cstring>
#include <iostream>
#include <zlib.h>

namespace hsm{

bytearray swUncompress(const uint8* data, int nbytes){
    if(!data){
        std::cerr << "swUncompress: Data is null" << std::endl;
        return bytearray();
    }
    if (nbytes <= 4){
        if (nbytes < 4 || (data[0]!=0 || data[1]!=0 || data[2]!=0 || data[3]!=0))
            std::cerr << "swUncompress: Input data is corrupted" << std::endl;
        return bytearray();
    }
    ulong expectedSize = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
    ulong len = std::max<ulong>(expectedSize, 1ul);
    ulong alloc = len;
    uint8 *dst = new uint8[alloc];
    int res = ::uncompress(dst, &len, (uchar*)data+4, nbytes-4);
    switch (res){
    case Z_OK:
        if(len != alloc)
            std::cerr << "swUncompress: Input data is corrupted" << std::endl;
        return bytearray((const char*)dst, (size_t)len);
    case Z_MEM_ERROR:
        std::cerr << "swUncompress: Z_MEM_ERROR: Not enough memory" << std::endl;
        break;
    case Z_BUF_ERROR:
        std::cerr << "swUncompress: Z_BUF_ERROR: Input data is corrupted" << std::endl;
        break;
    case Z_DATA_ERROR:
        std::cerr << "swUncompress: Z_DATA_ERROR: Input data is corrupted" << std::endl;
        break;
    }
    return bytearray();
}

bytearray swUncompress(const bytearray & ary){
    return swUncompress((const uint8*)ary.data(), ary.size());
}

bytearray swCompress(const uint8* data, int nbytes, int compressionLevel){
    if(nbytes == 0)
        return bytearray(4, '\0');
    if(!data){
        std::cerr << "swCompress : Data is null" << std::endl;
        return bytearray();
    }
    if(compressionLevel < -1 || compressionLevel > 9)
        compressionLevel = -1;
    ulong len = nbytes + nbytes / 100 + 13;
    bytearray bazip;
    int res;
    do{
        bazip.resize(len + 4);
        res = ::compress2((uchar*)bazip.data()+4, &len, (uchar*)data, nbytes, compressionLevel);
        switch(res){
        case Z_OK:
            bazip.resize(len + 4);
            bazip[0] = (nbytes & 0xff000000) >> 24;
            bazip[1] = (nbytes & 0x00ff0000) >> 16;
            bazip[2] = (nbytes & 0x0000ff00) >> 8;
            bazip[3] = (nbytes & 0x000000ff);
            break;
        case Z_MEM_ERROR:
            std::cerr << "swCompress: Z_MEM_ERROR: Not enough memory" << std::endl;
            bazip.resize(0);
            break;
        case Z_BUF_ERROR:
            len *= 2;
            break;
        }
    }while(res == Z_BUF_ERROR);
    //
    return bazip;
}

bytearray swCompress(const bytearray & ary, int compressionLevel){
    return swCompress((const uint8*)ary.data(), ary.size(), compressionLevel);
}

}

hsm::datastream & operator << (hsm::datastream & stream, const hsm::bytearray & data){
    stream.writeBytes(data.data(), data.size());
    return stream;
}

hsm::datastream & operator >> (hsm::datastream & stream, hsm::bytearray & data){
    char *d = 0;
    hsm::uint32 len = 0;
    stream.readBytes(d, len);
    data = hsm::bytearray(d, len);
    delete[] d;
    return stream;
}
