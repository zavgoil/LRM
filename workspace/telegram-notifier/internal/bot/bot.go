package bot

import (
	"context"
	"log"
	"telegram-notifier/internal/storage/telegram_users"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

type Bot struct {
	bot     *tgbotapi.BotAPI
	storage telegram_users.TelegramUsers
}

func New(bot_token string, storage telegram_users.TelegramUsers) (*Bot, error) {
	bot, err := tgbotapi.NewBotAPI(bot_token)
	if err != nil {
		return nil, err
	}

	return &Bot{bot: bot, storage: storage}, nil
}

func (b *Bot) Run(ctx context.Context) error {
	u := tgbotapi.NewUpdate(0)
	u.Timeout = 60

	updates := b.bot.GetUpdatesChan(u)

	for {
		select {
		case update := <-updates:
			if update.Message != nil {
				if update.Message.Text == "/start" {
					isExists, error := b.storage.TelegramUserIsExists(
						update.Message.From.UserName)
					if error != nil {
						log.Printf("Error: %s", error)
					}

					if !isExists {
						error := b.storage.InsertTelegramUser(
							update.Message.From.UserName,
							int(update.Message.Chat.ID))
						if error != nil {
							log.Printf("Error: %s", error)
						}
					}
				}

				log.Printf("[%s] %s", update.Message.From.UserName, update.Message.Text)
				msg := tgbotapi.NewMessage(update.Message.Chat.ID, update.Message.Text)
				msg.ReplyToMessageID = update.Message.MessageID
				b.bot.Send(msg)
			}
		case <-ctx.Done():
			return nil
		}
	}
}

func (b *Bot) SendMessage(username string, text string) error {
	chatId, err := b.storage.GetTelegramChatId(username)
	if err != nil {
		return err
	}

	msg := tgbotapi.NewMessage(int64(chatId), text)
	_, err = b.bot.Send(msg)
	if err != nil {
		return err
	}

	return nil
}
