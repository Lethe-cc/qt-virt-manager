
#if WITHOUT_LIBCACARD & 0
#include <libcacard.h>
#endif
#include "qspicehelper.h"
#include "qspicesmartcardmanager.h"

QSpiceSmartcardManager::QSpiceSmartcardManager(QObject *parent) :
    QSpiceObject(parent)
{
    gobject = NULL;
    init();
}

void QSpiceHelper::card_inserted(SpiceSmartcardManager *manager,
                                 SpiceSmartcardReader  *reader,
                                 gpointer user_data)
{
    Q_UNUSED(manager);
    QSpiceSmartcardManager *obj =
            static_cast<QSpiceSmartcardManager*>(user_data);
    if ( NULL==obj ) return;
#if WITHOUT_LIBCACARD & 0
    QString _name;
    VReader *_reader = (VReader*)reader;
    _name.append(vreader_get_name(_reader));
    if (_reader) vreader_free(_reader);
    if (!_name.isEmpty()) obj->cardInserted(_name);
#endif
}

void QSpiceHelper::card_removed(SpiceSmartcardManager *manager,
                                SpiceSmartcardReader  *reader,
                                gpointer user_data)
{
    Q_UNUSED(manager);
    QSpiceSmartcardManager *obj =
            static_cast<QSpiceSmartcardManager*>(user_data);
    if ( NULL==obj ) return;
#if WITHOUT_LIBCACARD & 0
    QString _name;
    VReader *_reader = (VReader*)reader;
    _name.append(vreader_get_name(_reader));
    if (_reader) vreader_free(_reader);
    if (!_name.isEmpty()) obj->cardRemoved(_name);
#endif
}

void QSpiceHelper::reader_added(SpiceSmartcardManager *manager,
                                SpiceSmartcardReader  *reader,
                                gpointer user_data)
{
    Q_UNUSED(manager);
    QSpiceSmartcardManager *obj =
            static_cast<QSpiceSmartcardManager*>(user_data);
    if ( NULL==obj ) return;
#if WITHOUT_LIBCACARD & 0
    QString _name;
    VReader *_reader = (VReader*)reader;
    _name.append(vreader_get_name(_reader));
    if (_reader) vreader_free(_reader);
    if (!_name.isEmpty()) obj->readerAdded(_name);
#endif
}

void QSpiceHelper::reader_removed(SpiceSmartcardManager *manager,
                                  SpiceSmartcardReader  *reader,
                                  gpointer user_data)
{
    Q_UNUSED(manager);
    QSpiceSmartcardManager *obj =
            static_cast<QSpiceSmartcardManager*>(user_data);
    if ( NULL==obj ) return;
#if WITHOUT_LIBCACARD & 0
    QString _name;
    VReader *_reader = (VReader*)reader;
    _name.append(vreader_get_name(_reader));
    if (_reader) vreader_free(_reader);
    if (!_name.isEmpty()) obj->readerRemoved(_name);
#endif
}

void QSpiceSmartcardManager::init()
{
    gobject = spice_smartcard_manager_get();
    if ( gobject ) {
        g_signal_connect(gobject, "card-inserted",
                         (GCallback) QSpiceHelper::card_inserted, this);
        g_signal_connect(gobject, "card-removed",
                         (GCallback) QSpiceHelper::card_removed, this);
        g_signal_connect(gobject, "reader-added",
                         (GCallback) QSpiceHelper::reader_added, this);
        g_signal_connect(gobject, "reader-removed",
                         (GCallback) QSpiceHelper::reader_removed, this);
        //qDebug()<<"SpiceSmartcardManager initiated";
    } else {
        //qDebug()<<"SpiceSmartcardManager not initiated";
    }
}


#if WITHOUT_LIBCACARD & 0
QStringList QSpiceSmartcardManager::spiceSmartcardManager_get_readers()
{
    QStringList _readerList;
    GList *_list = spice_smartcard_manager_get_readers(
                (SpiceSmartcardManager*)gobject);
    size_t count = count = g_list_length(_list);
    for ( uint i = 0; i<count; i++ ) {
        VReader *_reader =
                static_cast<VReader*>(g_list_nth_data(_list, i));
        if ( _reader ) {
            _readerList.append(vreader_get_name(_reader));
            vreader_free(_reader);
        };
    };
    if ( _list ) {
        // When no longer needed, the list must be freed
        // after unreferencing its elements with g_boxed_free()
        g_list_free(_list);
    };
    return _readerList;
}

bool QSpiceSmartcardManager::spiceSmartcardReader_is_software (QString &reader)
{
    if ( reader.isEmpty() ) return false;
    VReader *_reader = vreader_get_reader_by_name(
                reader.toUtf8().constData());
    return spice_smartcard_reader_is_software(
                (SpiceSmartcardReader*)_reader);
}

#else
QStringList QSpiceSmartcardManager::spiceSmartcardManager_get_readers()
{
    return QStringList();
}

bool QSpiceSmartcardManager::spiceSmartcardReader_is_software (QString &reader)
{
    return false;
}
#endif
