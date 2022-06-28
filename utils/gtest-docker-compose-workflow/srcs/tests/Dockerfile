FROM debian:latest

RUN set -ex; \
    apt-get update; \
    apt-get install -y \
      g++ \
      git \
      lcov \
      cmake \
      googletest \
    ; \
    rm -rf /var/lib/apt/lists/*;

COPY . /usr/src/tests

WORKDIR /usr/src/tests
RUN set -ex; \
    cd /usr/src/googletest; \
    cmake CMakeLists.txt; \
    make; \
    make install; \
    cd /usr/src/tests;

RUN chmod 0755 ./entrypoint.sh
ENTRYPOINT ["./entrypoint.sh"]
