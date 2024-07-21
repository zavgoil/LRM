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

const maxBytes = 10e6

func New(broker string, bot *bot.Bot, telegramNotificationTopic string, consumerGroup string) (
	*TelegramNotificationConsumer, error) {
	reader := kafka.NewReader(kafka.ReaderConfig{
		Brokers:  []string{broker},
		Topic:    telegramNotificationTopic,
		GroupID:  consumerGroup,
		MaxBytes: maxBytes,
	})
	return &TelegramNotificationConsumer{reader: reader, bot: bot}, nil
}

func (t *TelegramNotificationConsumer) Close() {
	t.reader.Close()
}

func (t *TelegramNotificationConsumer) Run(ctx context.Context) {
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
