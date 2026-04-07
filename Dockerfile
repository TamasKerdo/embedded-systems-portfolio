FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN set -eux && \
  apt-get update && apt-get install -y ca-certificates gcc-arm-none-eabi binutils-arm-none-eabi gcc cppcheck cmake make git && \
  rm -rf /var/lib/apt/lists/*
