FROM golang:alpine AS builder

WORKDIR /opt
COPY ./workspace/telegram-notifier /opt/telegram-notifier

WORKDIR /opt/telegram-notifier
RUN go mod download
RUN go build -o telegram-notifier  ./cmd/telegram-notifier/main.go

FROM alpine:latest AS runner

COPY --from=builder /opt/telegram-notifier/config /usr/local/share/telegram-notifier/config
COPY --from=builder /opt/telegram-notifier/telegram-notifier /usr/local/bin/telegram-notifier

ENV CONFIG_PATH=/usr/local/share/telegram-notifier/config/config.yaml

ENTRYPOINT [ "telegram-notifier" ]