#include "batch_absolute.h"
#include <stdlib.h>

void batch_absolute(int data[], int absoluteValues[], int dataSize) {
    for (int i = 0; i < dataSize; i++) {
        absoluteValues[i] = abs(data[i]);
    }
}
