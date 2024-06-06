#include <gui-client/gui-client.hpp>

#include <QQmlContext>
#include <QQuickStyle>

GuiClient::GuiClient(int argc, char *argv[]): app_(argc, argv), contact_model_(), app_backend_(argc, argv, &contact_model_)
{
    QQuickStyle::setStyle("Material");

    qml_engine_.rootContext()->setContextProperty("AppBackend", &app_backend_);
    qml_engine_.rootContext()->setContextProperty("ContactModel", &contact_model_);

    QObject::connect(
        &qml_engine_, &QQmlApplicationEngine::objectCreationFailed, &app_,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    qml_engine_.loadFromModule("app", "Main");
}

int GuiClient::run()
{
    return app_.exec();
}
