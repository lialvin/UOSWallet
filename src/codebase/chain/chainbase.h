#ifndef CHAINBASE_H
#define CHAINBASE_H

#ifndef _WIN64
#define LONG long long
#else
#define LONG long
#endif

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class UOSByteWriter;

static const std::string UOS_SYSTEM_ACCOUNT = "uosio";

class ISerializer
{
public:
    virtual void serialize(UOSByteWriter* writer) const = 0;
};

class IFormater
{
public:
    virtual QJsonValue toJson() const = 0;
    virtual void fromJson(const QJsonValue& value) = 0;
};

#endif // CHAINBASE_H
