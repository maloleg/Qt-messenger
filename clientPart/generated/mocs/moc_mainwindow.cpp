/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[478];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "setStatus"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "newStatus"
QT_MOC_LITERAL(4, 32, 12), // "receivedJson"
QT_MOC_LITERAL(5, 45, 7), // "message"
QT_MOC_LITERAL(6, 53, 8), // "gotError"
QT_MOC_LITERAL(7, 62, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 91, 3), // "err"
QT_MOC_LITERAL(9, 95, 26), // "on_pushButton_send_clicked"
QT_MOC_LITERAL(10, 122, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(11, 152, 32), // "on_pushButton_disconnect_clicked"
QT_MOC_LITERAL(12, 185, 33), // "on_pushButton_enterDialog_cli..."
QT_MOC_LITERAL(13, 219, 33), // "on_pushButton_sendPicture_cli..."
QT_MOC_LITERAL(14, 253, 24), // "on_pushButton_r1_clicked"
QT_MOC_LITERAL(15, 278, 24), // "on_pushButton_r2_clicked"
QT_MOC_LITERAL(16, 303, 24), // "on_pushButton_r3_clicked"
QT_MOC_LITERAL(17, 328, 24), // "on_pushButton_r4_clicked"
QT_MOC_LITERAL(18, 353, 24), // "on_pushButton_r5_clicked"
QT_MOC_LITERAL(19, 378, 24), // "on_pushButton_r6_clicked"
QT_MOC_LITERAL(20, 403, 27), // "on_pushButton_apply_clicked"
QT_MOC_LITERAL(21, 431, 8), // "getUsers"
QT_MOC_LITERAL(22, 440, 8), // "getImage"
QT_MOC_LITERAL(23, 449, 2), // "id"
QT_MOC_LITERAL(24, 452, 5), // "image"
QT_MOC_LITERAL(25, 458, 9), // "SendFrame"
QT_MOC_LITERAL(26, 468, 9) // "readSound"

    },
    "MainWindow\0setStatus\0\0newStatus\0"
    "receivedJson\0message\0gotError\0"
    "QAbstractSocket::SocketError\0err\0"
    "on_pushButton_send_clicked\0"
    "on_pushButton_connect_clicked\0"
    "on_pushButton_disconnect_clicked\0"
    "on_pushButton_enterDialog_clicked\0"
    "on_pushButton_sendPicture_clicked\0"
    "on_pushButton_r1_clicked\0"
    "on_pushButton_r2_clicked\0"
    "on_pushButton_r3_clicked\0"
    "on_pushButton_r4_clicked\0"
    "on_pushButton_r5_clicked\0"
    "on_pushButton_r6_clicked\0"
    "on_pushButton_apply_clicked\0getUsers\0"
    "getImage\0id\0image\0SendFrame\0readSound"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x0a /* Public */,
       4,    1,  112,    2, 0x0a /* Public */,
       6,    1,  115,    2, 0x0a /* Public */,
       9,    0,  118,    2, 0x08 /* Private */,
      10,    0,  119,    2, 0x08 /* Private */,
      11,    0,  120,    2, 0x08 /* Private */,
      12,    0,  121,    2, 0x08 /* Private */,
      13,    0,  122,    2, 0x08 /* Private */,
      14,    0,  123,    2, 0x08 /* Private */,
      15,    0,  124,    2, 0x08 /* Private */,
      16,    0,  125,    2, 0x08 /* Private */,
      17,    0,  126,    2, 0x08 /* Private */,
      18,    0,  127,    2, 0x08 /* Private */,
      19,    0,  128,    2, 0x08 /* Private */,
      20,    0,  129,    2, 0x08 /* Private */,
      21,    0,  130,    2, 0x08 /* Private */,
      22,    2,  131,    2, 0x08 /* Private */,
      25,    0,  136,    2, 0x08 /* Private */,
      26,    0,  137,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,   23,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->receivedJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 2: _t->gotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_send_clicked(); break;
        case 4: _t->on_pushButton_connect_clicked(); break;
        case 5: _t->on_pushButton_disconnect_clicked(); break;
        case 6: _t->on_pushButton_enterDialog_clicked(); break;
        case 7: _t->on_pushButton_sendPicture_clicked(); break;
        case 8: _t->on_pushButton_r1_clicked(); break;
        case 9: _t->on_pushButton_r2_clicked(); break;
        case 10: _t->on_pushButton_r3_clicked(); break;
        case 11: _t->on_pushButton_r4_clicked(); break;
        case 12: _t->on_pushButton_r5_clicked(); break;
        case 13: _t->on_pushButton_r6_clicked(); break;
        case 14: _t->on_pushButton_apply_clicked(); break;
        case 15: _t->getUsers(); break;
        case 16: _t->getImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 17: _t->SendFrame(); break;
        case 18: _t->readSound(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
