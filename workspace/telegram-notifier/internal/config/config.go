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
	ConnectionURI string `yaml:"connection_uri"`
}

type KafkaConfig struct {
	KafkaBroker string `yaml:"broker"`
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
