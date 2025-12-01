#include "PFM.hpp"

std::map<std::string, USERS> userLevel;

bool PFM::canDeleteFile(USERS user) {
    if (user == USER){
        return _fp == PL_NONE;
    }

    if (user == ADMIN){
        return _fp == PL_NONE || _fp == PL_MED;
    }

    if (user == OWNER){
        return _fp != PL_READONLY;
    }

    return false;
}

bool PFM::canSeeFile(USERS user) {
    if (user == USER){
        return _fp != PL_HIDDEN && _fp != PL_SYSTEM;
    }

    if (user == ADMIN){
        return _fp != PL_SYSTEM;
    }

    if (user == OWNER){
        return true;
    }

    return false;
}

bool PFM::canModifyFile(USERS user) {
    if (user == USER){
        return _fp == PL_NONE;
    }

    if (user == ADMIN){
        return _fp == PL_NONE || _fp == PL_MED;
    }

    if (user == OWNER){
        return _fp != PL_READONLY;
    }

    return false;
}

bool PFM::canRenameFile(USERS user) {
    return canModifyFile(user);
}

bool PFM::isHidden(USERS user) {
    return !canSeeFile(user);
}

bool PFM::isProtected() {
    return _fp != PL_NONE;
}

bool PFM::hasFullControl(USERS user) {
    return user == OWNER || (user == ADMIN && _fp != PL_SYSTEM && _fp != PL_READONLY);
}

bool PFM::isAccessible(USERS user) {
    return canSeeFile(user) && (canModifyFile(user) || canDeleteFile(user));
}

void PFM::setPermissions(FILES newPerm, USERS user) {
    if (user != OWNER){
        throw std::invalid_argument("You are not the level of \"OWNER\".");
    }

    _fp = newPerm;
}

void PFM::promoteToAdmin(const std::string &name) {
    if (userLevel[name] == USER){
        userLevel[name] = ADMIN;
    }
}

void PFM::promoteToOwner(const std::string &name) {
    bool ownerExists = std::any_of(userLevel.begin(),
    userLevel.end(), [](const auto& pair){
        return pair.second == OWNER;
    });

    if (!ownerExists && userLevel[name] == ADMIN){
        userLevel[name] = OWNER;
    }
}

std::string PFM::getPermissionLevel_user(USERS user) {
    if (user == USER){
        return "User Permission level.";
    }
    else if (user == ADMIN){
        return "Admin Permission level.";
    }
    else if (user == OWNER){
        return "Owner Permission level.";
    }
    else {
        // usually impossible but lets just do it.
        return "Level unknown.";
    }
}

std::string PFM::getPermissionLevel_file() {
    switch (_fp) {
        case PL_NONE:
            return "No Protection (PL_NONE)";
        case PL_MED:
            return "Medium Protection (PL_MED)";
        case PL_FULL:
            return "Full Protection (PL_FULL)";
        case PL_READONLY:
            return "Read-only (PL_READONLY)";
        case PL_HIDDEN:
            return "Hidden (PL_HIDDEN)";
        case PL_SYSTEM:
            return "System (PL_SYSTEM)";
        default:
            return "Unknown protection level";
    }
}

std::string PFM::AccessReport(USERS user) {
    std::string report = "User level: " + getPermissionLevel_user(user) + "\n";

    report += "File Level: " + getPermissionLevel_file() + "\n";
    report += "Can see: " + std::string(canSeeFile(user) ? "Yes" : "No") + "\n";
    report += "Can modify: " + std::string(canModifyFile(user) ? "Yes" : "No") + "\n";
    report += "Can delete: " + std::string(canDeleteFile(user) ? "Yes" : "No") + "\n";

    return report;
}
