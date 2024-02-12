#include "application.hpp"

extern "C"
{
    volatile uint32_t userMillis;
    volatile uint32_t userLastMillis;
    bool settingsFlag;
    uint8_t currPos =  0;

    void LD2Blink(uint8_t count);

    void setup()
    {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
        HAL_Delay(3000);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    }

    void loop()
    {
        uint32_t tickDiff = HAL_GetTick() - userMillis;
        if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
        {
            if (tickDiff < SHORT_MS)
            {
                if (!settingsFlag)
                {
                    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
                }
                else
                {
                    currPos = (currPos + 1) % POS_CONST;
                    LD2Blink(1);
                }
                userMillis = 0;
                HAL_NVIC_EnableIRQ(B1_EXTI_IRQn);
            }
            else if (settingsFlag && HAL_GetTick() - userLastMillis > NA_MS)
            {
//				LD2Blink(currPos+1);
//				HAL_Delay(SHORT_MS);
//              currPos = 0;
                LD2Blink(4);
                settingsFlag = false;
                userLastMillis = 0;
            } 
        }
        else if (!settingsFlag && tickDiff > LONG_MS)
        {
            LD2Blink(3);
            HAL_Delay(SHORT_MS);
            settingsFlag = true;
            userMillis = 0;
            HAL_NVIC_EnableIRQ(B1_EXTI_IRQn);
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

    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    {
        HAL_NVIC_DisableIRQ(B1_EXTI_IRQn);
        if (GPIO_Pin == B1_Pin && !HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
        {
        	userLastMillis = HAL_GetTick();
            userMillis = userLastMillis;

        }
    }
}
