#include "triplet.h"

Triplet::Triplet()
{

}

Triplet::Triplet(QVariantMap &triplet_map)
{
    this->x = triplet_map["x"].toDouble();
    this->y = triplet_map["y"].toDouble();
    this->z = triplet_map["z"].toDouble();
}
