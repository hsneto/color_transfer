FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
RUN apt-get install -qqy x11-apps
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y wget vim

# Install OpenCV
RUN apt-get install -y unzip
RUN wget -P /usr/local/src/ https://github.com/opencv/opencv/archive/3.4.1.zip
RUN cd /usr/local/src/ && unzip 3.4.1.zip && rm 3.4.1.zip
RUN cd /usr/local/src/opencv-3.4.1/ && mkdir build
RUN cd /usr/local/src/opencv-3.4.1/build && cmake -D CMAKE_INSTALL_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local/ .. && make -j4 && make install

# Setting up working directory 
RUN mkdir /lab
WORKDIR /lab

# Make
RUN git clone https://github.com/hsneto/color_transfer
RUN cd ./color_transfer/sample/ && make
RUN ln -s ./color_transfer/sample/color_transfer ./transfer

RUN ldconfig -v

# Minimize image size 
RUN (apt-get autoremove -y; \
     apt-get autoclean -y)

CMD ./transfer
