package telegram_users_postgre

import (
	"database/sql"
	"telegram-notifier/internal/storage/telegram_users"

	"github.com/lib/pq"
)

const (
	schema = `CREATE TABLE IF NOT EXISTS telegram_users(
		user_id TEXT PRIMARY KEY,
		chat_id INTEGER)`
)

type TelegramUsersPostgre struct {
	db *sql.DB
}

func New(connStr string) (*TelegramUsersPostgre, error) {
	db, err := sql.Open(
		"postgres",
		connStr)
	if err != nil {
		return nil, err
	}

	stmt, err := db.Prepare(schema)
	if err != nil {
		return nil, err
	}

	_, err = stmt.Exec()
	if err != nil {
		return nil, err
	}

	return &TelegramUsersPostgre{db: db}, nil
}

func (s *TelegramUsersPostgre) Close() error {
	return s.db.Close()
}

func (s *TelegramUsersPostgre) InsertTelegramUser(userId string, chatId int) error {
	stmt, err := s.db.Prepare(
		`INSERT INTO telegram_users(user_id, chat_id) VALUES($1, $2)`)
	if err != nil {
		return err
	}

	_, err = stmt.Exec(userId, chatId)
	if err != nil {
		if pqerr, ok := err.(*pq.Error); ok {
			switch pqerr.Code.Name() {
			case "unique_violation":
				return telegram_users.ErrUserAlreadyExists
			}
		}

		return err
	}

	return nil
}

func (s *TelegramUsersPostgre) DeleteTelegramUser(userId string) error {
	stmt, err := s.db.Prepare(
		`DELETE FROM telegram_users WHERE user_id = $1`)
	if err != nil {
		return err
	}

	_, err = stmt.Exec(userId)
	if err != nil {
		return err
	}

	return nil
}

func (s *TelegramUsersPostgre) TelegramUserIsExists(userId string) (bool, error) {
	stmt, err := s.db.Prepare(
		`SELECT EXISTS(SELECT 1 FROM telegram_users WHERE user_id = $1)`)
	if err != nil {
		return false, err
	}

	var exists bool
	err = stmt.QueryRow(userId).Scan(&exists)
	if err != nil {
		return false, err
	}

	return exists, nil
}

func (s *TelegramUsersPostgre) GetTelegramChatId(userId string) (int, error) {
	stmt, err := s.db.Prepare(
		`SELECT chat_id FROM telegram_users WHERE user_id = $1`)
	if err != nil {
		return 0, err
	}
	var chatId int

	err = stmt.QueryRow(userId).Scan(&chatId)

	if err != nil {
		if err == sql.ErrNoRows {
			return 0, telegram_users.ErrUserNotExists
		}
		return 0, err
	}

	return chatId, nil
}
