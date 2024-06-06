#pragma once

#include <QGuiApplication>

#include <app-backend/app-backend.hpp>
#include <app-backend/contact-list-model.hpp>
#include <QQmlApplicationEngine>

class GuiClient{
public:
    GuiClient(int argc, char *argv[]);
    int run();

private:
    QGuiApplication app_;
    QQmlApplicationEngine qml_engine_;

    ContactListModel contact_model_;
    AppBackend app_backend_;
};
