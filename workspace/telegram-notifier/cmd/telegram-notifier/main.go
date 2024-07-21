package main

import (
	"context"
	"os"
	"os/signal"
	"telegram-notifier/api/kafka/telegram_notification_consumer"
	"telegram-notifier/internal/bot"
	"telegram-notifier/internal/config"
	"telegram-notifier/internal/storage/telegram_users_postgre"
)

func main() {
	cfg := config.MustLoad()

	signals := make(chan os.Signal, 1)
	signal.Notify(signals, os.Interrupt)
	ctx, cancel := context.WithCancel(context.Background())

	telegram_users_storage, err := telegram_users_postgre.New(
		cfg.DB.Host, cfg.DB.DbName, cfg.DB.Username,
		cfg.DB.Password, cfg.DB.Port, cfg.DB.TelegramUserTableName)
	if err != nil {
		panic(err)
	}
	defer telegram_users_storage.Close()

	bot, err := bot.New(cfg.BotToken, telegram_users_storage)
	if err != nil {
		panic(err)
	}
	go bot.Run(ctx)

	telegram_notification_consumer, err := telegram_notification_consumer.New(
		cfg.KafkaBroker, bot, cfg.TelegramNotificationTopic, cfg.ConsumerGroup)
	if err != nil {
		panic(err)
	}
	defer telegram_notification_consumer.Close()
	go telegram_notification_consumer.Run(ctx)

	<-signals
	cancel()
}
