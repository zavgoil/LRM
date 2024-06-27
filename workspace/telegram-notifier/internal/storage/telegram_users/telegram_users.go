package telegram_users

import "errors"

var (
	ErrUserAlreadyExists = errors.New("user already exists")
	ErrUserNotExists     = errors.New("user not exists")
)

type TelegramUsers interface {
	InsertTelegramUser(userId string, chatId int) error
	DeleteTelegramUser(userId string) error
	TelegramUserIsExists(userId string) (bool, error)
	GetTelegramChatId(userId string) (int, error)
}
