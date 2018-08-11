#include "transactionextension.h"
#include "uosbytewriter.h"

TransactionExtension::TransactionExtension()
{

}

void TransactionExtension::serialize(UOSByteWriter *writer) const
{
    if (writer) {
        // It seems like that UOS duos not support any extensions yet.
        //writer->putShortLE(extensions.first);
        //SerializeCollection(extensions.second, writer);
    }
}
