/****************************************************************************
** Meta object code from reading C++ file 'MainWidgetController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MainWidgetController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWidgetController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20MainwidgetcontrollerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20MainwidgetcontrollerE = QtMocHelpers::stringData(
    "Mainwidgetcontroller",
    "pushRotationAfterRelease",
    "",
    "rotationFactor",
    "pushScaleAfterChange",
    "scaleFactor",
    "setGreyScaleOnOff",
    "setEdgeDetectionOnOff",
    "setResetImage",
    "uploadImage",
    "saveImage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20MainwidgetcontrollerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x0a,    1 /* Public */,
       4,    1,   59,    2, 0x0a,    3 /* Public */,
       6,    0,   62,    2, 0x0a,    5 /* Public */,
       7,    0,   63,    2, 0x0a,    6 /* Public */,
       8,    0,   64,    2, 0x0a,    7 /* Public */,
       9,    0,   65,    2, 0x0a,    8 /* Public */,
      10,    0,   66,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Mainwidgetcontroller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN20MainwidgetcontrollerE.offsetsAndSizes,
    qt_meta_data_ZN20MainwidgetcontrollerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20MainwidgetcontrollerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Mainwidgetcontroller, std::true_type>,
        // method 'pushRotationAfterRelease'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'pushScaleAfterChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setGreyScaleOnOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setEdgeDetectionOnOff'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setResetImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'uploadImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Mainwidgetcontroller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Mainwidgetcontroller *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pushRotationAfterRelease((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->pushScaleAfterChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->setGreyScaleOnOff(); break;
        case 3: _t->setEdgeDetectionOnOff(); break;
        case 4: _t->setResetImage(); break;
        case 5: _t->uploadImage(); break;
        case 6: _t->saveImage(); break;
        default: ;
        }
    }
}

const QMetaObject *Mainwidgetcontroller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mainwidgetcontroller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20MainwidgetcontrollerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mainwidgetcontroller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
