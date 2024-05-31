#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <app-backend/app-backend.hpp>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  AppBackend app_backend(argc, argv);

  QQmlApplicationEngine engine;
  QQuickStyle::setStyle("Material");

  engine.rootContext()->setContextProperty("AppBackend", &app_backend);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("app", "Main");

  return app.exec();
}
