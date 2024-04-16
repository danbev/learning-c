FROM ubuntu:20.04

# Set noninteractive installation to avoid getting stuck with interactive prompts
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    software-properties-common

RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    cmake \
    gdb \
    git

RUN apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]
