#include "uosnewaccount.h"
#include "uosbytewriter.h"
#include "../utility/utils.h"

UOSNewAccount::UOSNewAccount()
{

}

UOSNewAccount::UOSNewAccount(const std::string &creator, const std::string &newName, const TypeAuthority &owner, const TypeAuthority &active, const TypeAuthority &recovery)
{
    this->creator = TypeName(creator);
    this->newName = TypeName(newName);
    this->owner = owner;
    this->active = active;
    this->recovery = recovery;
}

UOSNewAccount::UOSNewAccount(const std::string &creator, const std::string &newName, const std::string &owner, const std::string &active, const std::string &recovery)
{
    this->creator = TypeName(creator);
    this->newName = TypeName(newName);
    this->owner = TypeAuthority(1, TypeKeyPermissionWeight(owner));
    this->active = TypeAuthority(1, TypeKeyPermissionWeight(active));
    this->recovery = TypeAuthority(1, TypeAccountPermissionWeight(recovery));
}

void UOSNewAccount::serialize(UOSByteWriter *writer) const
{
    if (writer) {
        creator.serialize(writer);
        newName.serialize(writer);
        owner.serialize(writer);
        active.serialize(writer);
        //recovery.serialize(writer);
    }
}

std::string UOSNewAccount::getCreatorName()
{
    return creator.to_string();
}

std::string UOSNewAccount::getActionName() const
{
    return "newaccount";
}

std::vector<unsigned char> UOSNewAccount::data()
{
    UOSByteWriter writer;
    serialize(&writer);

    return writer.toBytes();
}

std::vector<unsigned char> UOSNewAccount::dataAsHex()
{
    return Utils::convertBytesToHexStr(data());;
}
