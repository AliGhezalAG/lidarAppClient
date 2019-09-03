#include "header.h"

Header::Header()
{

}

Header::Header(const Header &oldObj)
{
    this->frameId = oldObj.frameId;
    this->timestamp = oldObj.timestamp;
    this->sequence = oldObj.sequence;
}

Header::Header(QVariantMap &header_map)
{
    this->frameId = header_map["frameId"].toString();
    this->timestamp = header_map["timestamp"].toInt();
    this->sequence = header_map["sequence"].toInt();
}

Header::~Header()
{

}
