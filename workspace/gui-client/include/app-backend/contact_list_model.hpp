#pragma once

#include <QAbstractListModel>
#include "contact.hpp"
#include <vector>

class ContactListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QStringList contactTypes READ contactTypesToStringList NOTIFY contactTypesChanged FINAL)
public:
    static const int FIRST_ROLE_INDEX = Qt::UserRole + 1;
    enum ModelRoles {
        TYPE = FIRST_ROLE_INDEX,
        DATA,
        END_INDICATOR
    };

    explicit ContactListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {
    }
    ~ContactListModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return contacts_.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid())
            return QVariant();
        if(index.row() > contacts_.size()-1)
            return QVariant();

        switch (role) {
        case TYPE:
            return getContactTypeIndex(contacts_.at(index.row()).type);
            break;
        case DATA:
            return QString::fromStdString(contacts_.at(index.row()).data);
            break;
        }

        return QVariant();
    }

    Q_INVOKABLE void addEmptyRow()
    {
        beginInsertRows(QModelIndex(), contacts_.size(), contacts_.size());
        contacts_.push_back({Contact::Type::INTERNAL, ""});
        endInsertRows();
    }

    Q_INVOKABLE void removeRow(int index)
    {
        if (index < 0 || index >= contacts_.size())
            return;

        beginRemoveRows(QModelIndex(), index, index);
        contacts_.erase(contacts_.begin() + index);
        endRemoveRows();
    }

    Q_INVOKABLE void editRow(int row_index, int type_index, QString data)
    {
        if (row_index < 0 || row_index >= contacts_.size())
            return;
        contacts_.at(row_index) = Contact{getContactTypeByIndex(type_index), data.toStdString()};
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
    std::vector<Contact> contacts_ = {
        {Contact::Type::EMAIL, "hui@masd"},
        {Contact::Type::INTERNAL, "avxzvas"},
        {Contact::Type::INTERNAL, "asfzxv"},
        };

    static QStringList contactTypesToStringList()
    {
        QStringList list;
        for(auto& i: Contact::TypeToString)
            list << QString::fromStdString(i.second);
        return list;
    }

signals:
    void contactTypesChanged();

private:

    static inline int getContactTypeIndex(const Contact::Type type)
    {
        int index = 0;

        for(const auto& pair: Contact::TypeToString)
        {
            if(pair.first == type)
                return index;
            index++;
        }
        return -1;
    }

    static inline Contact::Type getContactTypeByIndex(const int index)
    {
        int current_index = 0;
        for(const auto& pair: Contact::TypeToString)
        {
            if(current_index == index)
                return pair.first;
            current_index++;
        }
        return Contact::Type::NONE;
    }
};

