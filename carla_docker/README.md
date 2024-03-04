# Running CARLA in a Docker

## Prerequisities
You will need to have installed:
- **Docker:**
    ```bash
    sudo apt-get autoremove docker docker-engine docker.io
    sudo apt-get update
    sudo apt-get install docker.io
    ```
    Note: Follow [this guide](https://docs.docker.com/install/linux/linux-postinstall/) to add users to the docker sudo group.
- **NVIDIA Container Toolkit:** Install the ```nvidia-docker2``` package by following the instructions [here](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html).

## Running CARLA server in a container
```bash
# Pull the CARLA image
docker pull carlasim/carla:0.9.14

# To run CARLA with a display
docker run --privileged --gpus all --net=host -e DISPLAY=$DISPLAY carlasim/carla:0.9.14 /bin/bash ./CarlaUE4.sh

# To run CARLA in off-screen mode
docker run --privileged --gpus all --net=host -v /tmp/.X11-unix:/tmp/.X11-unix:rw carlasim/carla:0.9.14 /bin/bash ./CarlaUE4.sh -RenderOffScreen
```
More info on [this page](https://carla.readthedocs.io/en/0.9.14/build_docker/).

## Running CARLA client in a container
- Run below command and copy container id. Eg: **carla@`45a52fa744e1`:~$**
    ```bash
    docker run -it --privileged --gpus all --net=host -e DISPLAY=$DISPLAY carlasim/carla:0.9.14 bash
    ```
- Run below command in new terminal to export PythonAPI folder.
    ```
    docker cp <container id>:/home/carla/PythonAPI <destination path>
    ```
- Build client image using Dockerfile.
    ```bash
    docker build -t carla-client .
    ```
    Note: Above command might be deprecated in the future releases. Make sure PythonAPI folder is present in the same path.
- Run client image.
    ```bash
    docker run -it --gpus all --net=host -e DISPLAY=$DISPLAY carla-client

    # Run below commands inside container
    
    # Launch manual control
    python3 PythonAPI/examples/manual_control.py

    # To change map
    python3 PythonAPI/util/config.py --map Town11

    # To list available maps
    python3 PythonAPI/util/config.py --list
    ```
- If any X11 DISPLAY related issue were found, use below command to accept connection from docker. More info on [this page](https://www.baeldung.com/linux/docker-container-gui-applications).
    ```bash
    sudo xhost +local:docker
    ```
    Note: Replace + with - to remove connection.

### Extras
- To export docker image
    ```bash
    docker save -o ~/carla-client.tar carla-client:latest
    ```
- To load archived docker image
    ```bash
    docker load --input ~/carla-client.tar
    ```
- Town11 and Town12 are included in **carlasim/carla:0.9.14** docker image. 

### References:
- https://github.com/unicorns/carla-client-docker
- https://antc2lt.medium.com/carla-on-ubuntu-20-04-with-docker-5c2ccdfe2f71
- https://antc2lt.medium.com/carla-simulator-in-docker-in-2023-1f11f240b2df
