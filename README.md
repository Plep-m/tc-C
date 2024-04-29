just include the .h in your project and you are good to go<br>
Usage Exemple:
```c
#include "tc.h"

int main() {
    
    try {
        throw(404, "Page not found");
    }
    
    catch(e, 404, 503) {
        printf("Caught a 404 or 503 exception: %s\n", e->message);
    }

    otherwise {
        printf("No exception caught.\n");
    }

    return 0;
}
```
