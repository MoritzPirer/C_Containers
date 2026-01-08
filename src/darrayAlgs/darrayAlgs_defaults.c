///
/// @file: darrayAlgs_defaults.c
/// @description: Contains defaults for functions intended to be passed to other
///     darrayAlgs functions as function pointers. 
///
/// @date: 2026-01-07
/// @author: Moritz Pirer
///

#include "../../inc/darrayAlgs.h"

bool darrayDefaultCondition(const void* element, const void* data) {
    return (*(size_t*) element == *(size_t*) data);
}

int darrayDefaultOrdering(const void* a, const void* b) {
    return (*(size_t*) a - *(size_t*) b);
}