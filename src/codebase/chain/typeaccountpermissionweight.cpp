#include "typeaccountpermissionweight.h"
#include "uosbytewriter.h"

TypeAccountPermissionWeight::TypeAccountPermissionWeight()
{

}

TypeAccountPermissionWeight::TypeAccountPermissionWeight(const std::string &name, short weight)
{
    this->permission = TypePermissionLevel(name, "active");
    this->weight = weight;
}

void TypeAccountPermissionWeight::serialize(UOSByteWriter *writer) const
{
    if (writer) {
        permission.serialize(writer);
        writer->putShortLE(weight);
    }
}
