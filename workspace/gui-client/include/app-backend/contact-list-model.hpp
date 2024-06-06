#pragma once

#include <proto/user-service.grpc.pb.h>

#include <QAbstractListModel>
#include <vector>

class ContactListModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(QStringList contactTypes READ contactTypesToStringList NOTIFY
                 contactTypesChanged FINAL)

 public:
  static const int FIRST_ROLE_INDEX = Qt::UserRole + 1;
  enum ModelRoles { TYPE = FIRST_ROLE_INDEX, DATA, END_INDICATOR };
  const inline static std::map<::user_service::NotificationClientType,
                               std::string> TypeToString = {
      {::user_service::NotificationClientType::INTERNAL,
       "Внутреннее приложение"},
      {::user_service::NotificationClientType::EMAIL, "Email"},
      {::user_service::NotificationClientType::TELEGRAM, "Телеграм"},
    };

  Q_INVOKABLE void addEmptyRow() {
    beginInsertRows(QModelIndex(), contacts_.size(), contacts_.size());
    ::user_service::NotificationClient contact{};
    contact.set_type(user_service::NotificationClientType::INTERNAL);
    contact.set_data("");
    contacts_.Add(std::move(contact));
    endInsertRows();
  }

  Q_INVOKABLE void removeRow(int index) {
    if (index < 0 || index >= contacts_.size()) return;

    beginRemoveRows(QModelIndex(), index, index);
    contacts_.erase(contacts_.begin() + index);
    endRemoveRows();
  }

  Q_INVOKABLE void editRow(int row_index, int type_index, QString data) {
    if (row_index < 0 || row_index >= contacts_.size()) return;
    qDebug() << "EDIT";
    contacts_.at(row_index).set_type(getContactTypeByIndex(type_index));
    contacts_.at(row_index).set_data(data.toStdString());
  }

  void setContacts(::google::protobuf::RepeatedPtrField<
                   ::user_service::NotificationClient>&& contacts) {
    if (contacts_.size() > 0) {
      beginRemoveRows(QModelIndex(), 0, contacts_.size() - 1);
      contacts_.Clear();
      endRemoveRows();
    }

    if (contacts.size() > 0) {
      beginInsertRows(QModelIndex(), 0, contacts.size() - 1);
      contacts_ = std::move(contacts);
      endInsertRows();
    }
  }

  Q_INVOKABLE void clearCache()
  {
    contacts_.Clear();
  }

  const ::google::protobuf::RepeatedPtrField<
      ::user_service::NotificationClient>&
  getContacts() {
    return contacts_;
  }

  explicit ContactListModel(QObject* parent = nullptr)
      : QAbstractListModel(parent) {}
  ~ContactListModel() {}
  int rowCount(const QModelIndex& parent = QModelIndex()) const override {
    return contacts_.size();
  }
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid()) return QVariant();
    if (index.row() > contacts_.size() - 1) return QVariant();

    switch (role) {
      case TYPE:
        return getContactTypeIndex(contacts_.at(index.row()).type());
        break;
      case DATA:
        return QString::fromStdString(contacts_.at(index.row()).data());
        break;
    }

    return QVariant();
  }

 protected:
  QHash<int, QByteArray> roleNames() const override {
    // Ключи, которые будут использоваться в QML
    QHash<int, QByteArray> roles;
    roles[TYPE] = "contact_type";
    roles[DATA] = "contact_data";
    return roles;
  }

 private:
  ::google::protobuf::RepeatedPtrField< ::user_service::NotificationClient>
      contacts_ = {};

  static QStringList contactTypesToStringList() {
    QStringList list;
    for (auto& i : TypeToString)
      list << QString::fromStdString(i.second);
    return list;
  }

 signals:
  void contactTypesChanged();

 private:
  static inline int getContactTypeIndex(
      const ::user_service::NotificationClientType type) {
    int index = 0;

    for (const auto& pair : TypeToString) {
      if (pair.first == type) return index;
      index++;
    }
    return -1;
  }

  static inline ::user_service::NotificationClientType getContactTypeByIndex(
      const int index) {
    int current_index = 0;
    for (const auto& pair : TypeToString) {
      if (current_index == index) return pair.first;
      current_index++;
    }
    return ::user_service::NotificationClientType::NONE;
  }
};
