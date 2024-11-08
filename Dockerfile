FROM ubuntu:latest
ENV TZ=Europe/Moscow \
    DEBIAN_FRONTEND=noninteractive

RUN apt update -y && apt install -y gcc g++ gcc-10 g++-10 git clang-format \
    cmake libpqxx-dev libspdlog-dev libboost-all-dev libgtest-dev libgmock-dev && \
    git clone https://github.com/jbeder/yaml-cpp.git && \
    mkdir -p yaml-cpp/build && cd yaml-cpp/build && cmake .. && make && make install && \
    cd / && \
    git clone https://github.com/nlohmann/json.git && \
    cd json && mkdir build && cd build && cmake .. && make && make install && \
    cd /usr/src/googletest/googletest && cmake . && make && cp lib/*.a /usr/lib

COPY . /myproject
WORKDIR /myproject/src

RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make