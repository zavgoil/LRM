package config

import (
	"log"
	"os"

	"gopkg.in/yaml.v2"
)

type Config struct {
	DB             `yaml:"db"`
	KafkaConfig    `yaml:"kafka"`
	TelegramConfig `yaml:"telegram"`
}

type DB struct {
	DbName                string `yaml:"db_name"`
	Username              string `yaml:"user"`
	Password              string `yaml:"password"`
	Host                  string `yaml:"host"`
	Port                  int    `yaml:"port"`
	TelegramUserTableName string `yaml:"telegram_user_table_name"`
}

type KafkaConfig struct {
	KafkaBroker               string `yaml:"broker"`
	TelegramNotificationTopic string `yaml:"telegram_notification_topic"`
	ConsumerGroup             string `yaml:"consumer_group"`
}

type TelegramConfig struct {
	BotToken string `yaml:"bot_token"`
}

func MustLoad() *Config {
	configPath := os.Getenv("CONFIG_PATH")
	if configPath == "" {
		log.Fatal("CONFIG_PATH is not set")
	}

	cfgFile, err := os.ReadFile(configPath)
	if err != nil {
		log.Fatalf("cannot read config file: %s", err)
	}

	var cfg Config
	err = yaml.Unmarshal(cfgFile, &cfg)
	if err != nil {
		log.Fatalf("cannot deserialize config file: %s", err)
	}

	return &cfg
}
