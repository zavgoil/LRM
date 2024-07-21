package telegram_users_postgre

import (
	"database/sql"
	"strconv"
	"telegram-notifier/internal/storage/telegram_users"

	"github.com/lib/pq"
)

type TelegramUsersPostgre struct {
	db         *sql.DB
	table_name string
}

func New(host, db_name, username, password string, port int, telegram_user_table_name string) (*TelegramUsersPostgre, error) {
	connStr := "dbname=" + db_name + " user=" + username +
		" password=" + password + " host=" + host +
		" port=" + strconv.Itoa(port) + " connect_timeout=5 sslmode=disable"
	db, err := sql.Open(
		"postgres",
		connStr)
	if err != nil {
		return nil, err
	}

	stmt, err := db.Prepare(`CREATE TABLE IF NOT EXISTS ` + telegram_user_table_name + `(
		user_id TEXT PRIMARY KEY,
		chat_id INTEGER)`)
	if err != nil {
		return nil, err
	}

	_, err = stmt.Exec()
	if err != nil {
		return nil, err
	}

	return &TelegramUsersPostgre{db: db, table_name: telegram_user_table_name}, nil
}

func (s *TelegramUsersPostgre) Close() error {
	return s.db.Close()
}

func (s *TelegramUsersPostgre) InsertTelegramUser(userId string, chatId int) error {
	stmt, err := s.db.Prepare(
		`INSERT INTO ` + s.table_name + `(user_id, chat_id) VALUES($1, $2)`)
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
		`DELETE FROM ` + s.table_name + ` WHERE user_id = $1`)
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
		`SELECT EXISTS(SELECT 1 FROM ` + s.table_name + ` WHERE user_id = $1)`)
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
		`SELECT chat_id FROM ` + s.table_name + ` WHERE user_id = $1`)
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
