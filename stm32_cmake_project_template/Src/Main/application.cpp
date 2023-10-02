#include "application.hpp"
#include "main.h"
#include "stdio.h"

extern "C" {

    void setup() {

    }

    void loop() {
        printf("Hello World");
        HAL_Delay(1000);
    }

}