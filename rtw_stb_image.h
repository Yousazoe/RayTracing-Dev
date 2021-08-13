#ifndef RAYTRACING_DEV_RTW_STB_IMAGE_H
#define RAYTRACING_DEV_RTW_STB_IMAGE_H

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
    #pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb/stb_image.h"

// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
    #pragma warning (pop)
#endif

#endif //RAYTRACING_DEV_RTW_STB_IMAGE_H
