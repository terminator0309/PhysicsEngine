#include "Random.hpp"

namespace pe {
    namespace util {
        namespace Random {

            void init() {
                srand(time(0));
            }

            float generate() {
                return (float)rand() / (float)(RAND_MAX);
            }

            float getRandom() {
                return generate();
            }

            float getRandom(float end) {
                return (generate()) * end;
            }

            float getRandom(float start, float end) {
                if (start == end)
                    return start;

                if (start > end)
                    return getRandom(end, start);

                return generate() * (end - start) + start;
            }
        }
    }
}