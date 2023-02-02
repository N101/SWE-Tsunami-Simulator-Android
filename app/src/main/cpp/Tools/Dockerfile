FROM ubuntu:22.04

RUN apt-get update -y && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        autoconf \
        automake \
        build-essential \
        bzip2 \
        ccache \
        clang-format \
        clang-tidy \
        cppcheck \
        curl \
        doxygen \
        gdb \
        git \
        graphviz \
        iwyu \
        less \
        libnetcdf-c++4 \
        libnetcdf-c++4-dev \
        libnetcdf-cxx-legacy-dev \
        libnetcdf-dev \
        libopenmpi-dev \
        libtool \
        make \
        netcdf-bin \
        ninja-build \
        pkg-config \
        python3 \
        python3-pip \
        texlive \
        texlive-full \
        unifdef \
        valgrind \
        vim \
        wget && \
    rm -rf /var/lib/apt/lists/*

# GNU compiler
RUN apt-get update -y && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        g++ \
        gcc \
        gfortran && \
    rm -rf /var/lib/apt/lists/*

# CMake version 3.25.0
RUN apt-get update -y && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        make \
        wget && \
    rm -rf /var/lib/apt/lists/*
RUN mkdir -p /var/tmp && wget -q -nc --no-check-certificate -P /var/tmp https://github.com/Kitware/CMake/releases/download/v3.25.0/cmake-3.25.0-linux-aarch64.sh && \
    mkdir -p /usr/local && \
    /bin/sh /var/tmp/cmake-3.25.0-linux-aarch64.sh --prefix=/usr/local --skip-license && \
    rm -rf /var/tmp/cmake-3.25.0-linux-aarch64.sh
ENV PATH=/usr/local/bin:$PATH

RUN apt-get update -y && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends python3-dev && rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install --upgrade pip matplotlib numpy jupyterlab hpccm

ENV DISPLAY=host.docker.internal:0.0 \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

