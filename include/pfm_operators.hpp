#include "PFM.hpp"

bool operator==(const PFM& lhs, const PFM& rhs) {
    return lhs._fp == rhs._fp;
}

bool operator!=(const PFM& lhs, const PFM& rhs){
    return !(lhs == rhs);
}
