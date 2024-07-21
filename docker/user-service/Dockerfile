FROM alpine:latest AS builder

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="Etc/UTC"

ARG INSTALL_PATH=/opt/app_install

RUN apk --no-cache update && apk --no-cache add \
    alpine-sdk \    
    cmake 

# --- 3rdparty: json ---
WORKDIR /opt

COPY ./workspace/3rdparty/json /opt/json
RUN cmake -S ./json -B ./json/build \ 
    -DJSON_Install=ON \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./json/build -j$(nproc) && \
    make -C ./json/build install

# --- 3rdparty: libpqxx ---
WORKDIR /opt

RUN apk --no-cache update && apk --no-cache add \
    postgresql \
    libpq-dev 

COPY ./workspace/3rdparty/libpqxx /opt/libpqxx
RUN cmake -S ./libpqxx -B ./libpqxx/build \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./libpqxx/build -j$(nproc) && \
    make -C ./libpqxx/build install

# --- dep: project-util ---
WORKDIR /opt

RUN apk --no-cache update && apk --no-cache add -f \
    yaml-cpp-dev 

COPY ./workspace/project-util /opt/project-util
RUN cmake -S ./project-util -B ./project-util/build \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./project-util/build -j$(nproc) && \
    make -C ./project-util/build install

# --- dep: proto ---
WORKDIR /opt

RUN apk --no-cache update && apk --no-cache add -f \
    grpc-dev \
    grpc-cpp \
    protobuf-dev

COPY ./workspace/proto /opt/proto
RUN cmake -S ./proto -B ./proto/build \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./proto/build -j$(nproc) && \
    make -C ./proto/build install

# --- user-service ---
WORKDIR /opt

RUN apk --no-cache update && apk --no-cache add -f \
    librdkafka-dev

COPY ./workspace/user-service /opt/user-service
RUN cmake -S ./user-service -B ./user-service/build \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./user-service/build -j$(nproc) && \
    make -C ./user-service/build install

# --- RUNNER ---
FROM alpine:latest AS runner

RUN apk --no-cache update && apk --no-cache add \
    libpq \
    yaml-cpp \
    grpc-cpp \
    protobuf \
    librdkafka

COPY --from=builder /opt/app_install /usr/local

ENV RPC_MAP_PATH=/usr/local/share/project-util/config/rpc_map.yaml
ENV DB_OPTION_PATH=/usr/local/share/user-service/config/db_option.yaml
ENV KAFKA_OPTION_PATH=/usr/local/share/user-service/config/kafka_option.yaml

COPY --chmod=+x ./docker/script/create_rpc_map_config.sh /create_rpc_map_config.sh
COPY --chmod=+x ./docker/user-service/script/create_db_config.sh /create_db_config.sh
COPY --chmod=+x ./docker/user-service/script/create_kafka_config.sh /create_kafka_config.sh
COPY --chmod=+x ./docker/user-service/script/entrypoint.sh /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]

