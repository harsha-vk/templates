#include "application.hpp"

extern "C"
{
    uint8_t currPos;
    bool started;

    void LD2Blink(uint8_t count);

    void setup()
    {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
        started = false;
        currPos = 0;
    }

    void loop()
    {
        if(!started && !HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
        {
            uint32_t millis = HAL_GetTick();
            while (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) && HAL_GetTick() - millis <= LONG_MS);
            if (HAL_GetTick() - millis < SHORT_MS)
            {
                HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
                started = true;
            }
            else if (HAL_GetTick() - millis >= LONG_MS)
            {
                LD2Blink(3);
                HAL_Delay(200);
                if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
                {
                    millis = HAL_GetTick();
                    while (HAL_GetTick() - millis < NA_MS)
                    {
                        if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
                        {
                            HAL_Delay(200);
                            if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
                            {
                                currPos = (currPos >= POS_CONST) ? 1 : (currPos + 1);
                                LD2Blink(1);
                                millis = HAL_GetTick();
                            }
                        }
                    }
                    // TODO: Save Settings in FLASH
                }
                LD2Blink(4);
            };
        }
        if(started)
        {
            if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
            {
                HAL_Delay(200);
                if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
                {
                    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
                    started = false;
                }
            }
        }
        HAL_Delay(10);
    }

    void LD2Blink(uint8_t count)
    {
        for (uint8_t i = 0; i < count * 2; i++)
        {
            HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
            HAL_Delay(200);
        }
    }
}
