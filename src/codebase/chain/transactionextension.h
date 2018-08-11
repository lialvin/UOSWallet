#ifndef TRANSACTIONEXTENSION_H
#define TRANSACTIONEXTENSION_H

#include "chainbase.h"
#include <vector>

class TransactionExtension : public ISerializer
{
public:
    TransactionExtension();

    virtual void serialize(UOSByteWriter* writer) const;

private:
    std::pair<uint16_t,std::vector<char>> extensions;
};

#endif // TRANSACTIONEXTENSION_H
