FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y python3-pip libpng-dev libtiff5-dev libjpeg-dev libgtk-3-0
RUN apt-get clean
RUN pip3 install --upgrade pip
RUN pip3 install pygame numpy networkx
ADD /PythonAPI /PythonAPI
ENV PYTHONPATH=$PYTHONPATH:/PythonAPI/carla/dist/carla-0.9.15-py3.7-linux-x86_64.egg
CMD ["/bin/bash"]

