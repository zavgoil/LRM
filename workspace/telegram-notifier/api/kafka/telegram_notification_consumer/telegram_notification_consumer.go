package telegram_notification_consumer

import (
	"context"
	"errors"
	"fmt"
	"telegram-notifier/internal/bot"

	"github.com/segmentio/kafka-go"
)

type TelegramNotificationConsumer struct {
	reader *kafka.Reader
	bot    *bot.Bot
}

const topic = "telegram_notification"
const consumerGroup = "telegram_notifier"
const maxBytes = 10e6

func New(broker string, bot *bot.Bot) (*TelegramNotificationConsumer, error) {
	reader := kafka.NewReader(kafka.ReaderConfig{
		Brokers:  []string{broker},
		Topic:    topic,
		GroupID:  consumerGroup,
		MaxBytes: maxBytes,
	})

	return &TelegramNotificationConsumer{reader: reader, bot: bot}, nil
}

func (t *TelegramNotificationConsumer) Close() {
	t.reader.Close()
}

func (t *TelegramNotificationConsumer) Run(ctx context.Context) {
	// ctx, cancel := context.WithCancel(context.Background())

	for {
		m, err := t.reader.ReadMessage(ctx)
		if err != nil {
			if errors.Is(err, context.Canceled) {
				return
			}
			break
		}

		err = t.bot.SendMessage(string(m.Key), string(m.Value))
		if err != nil {
			fmt.Printf("error sending message: %s\n", err)
		}
	}

	fmt.Printf("connection closed\n")
}
