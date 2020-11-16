/****************************************************************************
** Meta object code from reading C++ file 'serverStuff.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serverStuff.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverStuff.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerStuff_t {
    QByteArrayData data[19];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerStuff_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerStuff_t qt_meta_stringdata_ServerStuff = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ServerStuff"
QT_MOC_LITERAL(1, 12, 14), // "gotNewMesssage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "msg"
QT_MOC_LITERAL(4, 32, 15), // "smbDisconnected"
QT_MOC_LITERAL(5, 48, 12), // "jsonReceived"
QT_MOC_LITERAL(6, 61, 14), // "connectByNames"
QT_MOC_LITERAL(7, 76, 5), // "name1"
QT_MOC_LITERAL(8, 82, 5), // "name2"
QT_MOC_LITERAL(9, 88, 13), // "newConnection"
QT_MOC_LITERAL(10, 102, 10), // "readClient"
QT_MOC_LITERAL(11, 113, 16), // "gotDisconnection"
QT_MOC_LITERAL(12, 130, 12), // "sendToClient"
QT_MOC_LITERAL(13, 143, 11), // "QTcpSocket*"
QT_MOC_LITERAL(14, 155, 6), // "socket"
QT_MOC_LITERAL(15, 162, 3), // "str"
QT_MOC_LITERAL(16, 166, 10), // "handleJson"
QT_MOC_LITERAL(17, 177, 7), // "message"
QT_MOC_LITERAL(18, 185, 19) // "slot_connectByNames"

    },
    "ServerStuff\0gotNewMesssage\0\0msg\0"
    "smbDisconnected\0jsonReceived\0"
    "connectByNames\0name1\0name2\0newConnection\0"
    "readClient\0gotDisconnection\0sendToClient\0"
    "QTcpSocket*\0socket\0str\0handleJson\0"
    "message\0slot_connectByNames"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerStuff[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    1,   68,    2, 0x06 /* Public */,
       6,    2,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    2,   79,    2, 0x0a /* Public */,
      16,    1,   84,    2, 0x0a /* Public */,
      18,    2,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::LongLong, 0x80000000 | 13, QMetaType::QString,   14,   15,
    QMetaType::Void, QMetaType::QJsonObject,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

       0        // eod
};

void ServerStuff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerStuff *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gotNewMesssage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->smbDisconnected(); break;
        case 2: _t->jsonReceived((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 3: _t->connectByNames((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->newConnection(); break;
        case 5: _t->readClient(); break;
        case 6: _t->gotDisconnection(); break;
        case 7: { qint64 _r = _t->sendToClient((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->handleJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 9: _t->slot_connectByNames((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerStuff::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerStuff::gotNewMesssage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerStuff::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerStuff::smbDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerStuff::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerStuff::jsonReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ServerStuff::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerStuff::connectByNames)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerStuff::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ServerStuff.data,
    qt_meta_data_ServerStuff,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerStuff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerStuff::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerStuff.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerStuff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ServerStuff::gotNewMesssage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerStuff::smbDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ServerStuff::jsonReceived(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerStuff::connectByNames(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
