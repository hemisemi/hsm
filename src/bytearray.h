#ifndef SWAPI_BYTEARRAY_H
#define SWAPI_BYTEARRAY_H

#include <vector>
#include <string>
#include "types.h"
#include "datastream.h"

namespace hsm{

typedef std::string bytearray;

bytearray swCompress(const uint8 *data, int nbytes, int compressionLevel = -1);
bytearray swUncompress(const uint8* data, int nbytes);
bytearray swCompress(const bytearray &, int compressionLevel = -1);
bytearray swUncompress(const bytearray &);

}

hsm::datastream & operator<<(hsm::datastream & stream, const hsm::bytearray & data);
hsm::datastream & operator>>(hsm::datastream & stream, hsm::bytearray & data);

#endif // SWAPI_BYTEARRAY_H
