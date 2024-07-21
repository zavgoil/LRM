FROM alpine:latest AS builder

# ARG DEBIAN_FRONTEND=noninteractive
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

# --- gui-client ---
WORKDIR /opt

RUN apk --no-cache update && apk --no-cache add \
    qt6-qtbase-dev \
    qt6-qtdeclarative-dev 

COPY ./workspace/gui-client /opt/gui-client
RUN cmake -S ./gui-client -B ./gui-client/build \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} && \
    make -C ./gui-client/build -j$(nproc) && \
    make -C ./gui-client/build install

FROM alpine:latest AS runner

RUN apk --no-cache update && apk --no-cache add \
    yaml-cpp \
    grpc-cpp \
    protobuf \
    mesa-dri-gallium \
    ttf-dejavu \
    bind-tools \
    qt6-qtbase \
    qt6-qtdeclarative

COPY --from=builder /opt/app_install /usr/local

ENV RPC_MAP_PATH=/usr/local/share/project-util/config/rpc_map.yaml

COPY --chmod=+x ./docker/script/create_rpc_map_config.sh /create_rpc_map_config.sh
COPY --chmod=+x ./docker/gui-client/script/entrypoint.sh /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]