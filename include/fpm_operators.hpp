#include "FPM.hpp"

bool operator==(const FPM& lhs, const FPM& rhs) {
    return lhs._fp == rhs._fp;
}

bool operator!=(const FPM& lhs, const FPM& rhs){
    return !(lhs == rhs);
}
