#ifndef TYPEKEYPERMISSIONWEIGHT_H
#define TYPEKEYPERMISSIONWEIGHT_H

#include "chainbase.h"
#include "../ec/uos_key_encode.h"
#include <string>

class TypeKeyPermissionWeight : public ISerializer
{
public:
    TypeKeyPermissionWeight();
    TypeKeyPermissionWeight(const std::string& pubKey, short weight = 1);

    virtual void serialize(UOSByteWriter *writer) const;

private:
    std::string pubKey;
    short weight;
};

#endif // TYPEKEYPERMISSIONWEIGHT_H
