#pragma once

#ifndef KC_CHANGE_HPATCHZ_H
#define KC_CHANGE_HPATCHZ_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    __declspec(dllimport) int hpatch(const char* oldFileName, const char* diffFileName, const char* outNewFileName,
        int isLoadOldAll = 0, size_t patchCacheSize = 0, unsigned long long diffDataOffert = 0,
        unsigned long long diffDataSize = 0, int vcpatch_isChecksum = 0, int vcpatch_isInMem = 0);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !KC_CHANGE_HPATCHZ_H
