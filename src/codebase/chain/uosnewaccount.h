#ifndef UOSNEWACCOUNT_H
#define UOSNEWACCOUNT_H

#include "typename.h"
#include "typeauthority.h"

class UOSNewAccount : public ISerializer
{
public:
    UOSNewAccount();
    UOSNewAccount(const std::string& creator, const std::string& newName, const TypeAuthority& owner, const TypeAuthority& active, const TypeAuthority& recovery);
    UOSNewAccount(const std::string& creator, const std::string& newName, const std::string& owner, const std::string& active, const std::string& recovery);

    virtual void serialize(UOSByteWriter *writer) const;

    std::string getCreatorName();
    std::string getActionName() const;

    std::vector<unsigned char> data();
    std::vector<unsigned char> dataAsHex();

private:
    TypeName creator;
    TypeName newName;
    TypeAuthority owner;
    TypeAuthority active;
    TypeAuthority recovery;
};

#endif // UOSNEWACCOUNT_H
