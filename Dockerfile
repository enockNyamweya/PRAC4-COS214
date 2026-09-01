FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install C++11 toolchain, build tool, and debugging tools required for Prac 4
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Default container shell
CMD ["bash"]