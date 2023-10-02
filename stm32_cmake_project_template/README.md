# STM32 CMake Project Template - C C++

- Install the following packages.
    - [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
    - [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html)
- Clone required Firmwares into /STM32Cube/Repository. Eg. [STM32CubeF3](https://github.com/STMicroelectronics/STM32CubeF3)
- Create a new project and generate code using STM32CubeMX.
    - Find high-speed clock configurations on [page 24](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf).
- Copy CMakeLists.txt and arm-none-eabi.cmake files into the new project, and make required changes.
- Build project inside /Build folder.
