/****************************************************************************
** Meta object code from reading C++ file 'myplaylistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/myplaylistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myplaylistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPlayListWidget_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPlayListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPlayListWidget_t qt_meta_stringdata_MyPlayListWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MyPlayListWidget"
QT_MOC_LITERAL(1, 17, 8), // "playFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "currentFile"
QT_MOC_LITERAL(4, 39, 19), // "addVideoForPlayList"
QT_MOC_LITERAL(5, 59, 9), // "showClick"
QT_MOC_LITERAL(6, 69, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 81, 5) // "index"

    },
    "MyPlayListWidget\0playFile\0\0currentFile\0"
    "addVideoForPlayList\0showClick\0QModelIndex\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPlayListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    1,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void MyPlayListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPlayListWidget *_t = static_cast<MyPlayListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = _t->addVideoForPlayList();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->showClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyPlayListWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyPlayListWidget::playFile)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyPlayListWidget::staticMetaObject = {
    { &DWidget::staticMetaObject, qt_meta_stringdata_MyPlayListWidget.data,
      qt_meta_data_MyPlayListWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyPlayListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPlayListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPlayListWidget.stringdata0))
        return static_cast<void*>(this);
    return DWidget::qt_metacast(_clname);
}

int MyPlayListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyPlayListWidget::playFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
