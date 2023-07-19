#pragma once

#include <time.h>
#include <cstdlib>

namespace pe{
    namespace util {
        namespace Random{

            void init();

            float generate();

            float getRandom();

            float getRandom(float end);

            float getRandom(float start, float end);
        }
    }
}