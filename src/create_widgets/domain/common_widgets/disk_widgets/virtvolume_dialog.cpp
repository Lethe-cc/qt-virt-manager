#include "virtvolume_dialog.h"

VirtVolumeDialog::VirtVolumeDialog(
        QWidget *parent,
        virConnectPtr conn) :
    QDialog(parent), currWorkConnect(conn)
{
    setModal(true);
    poolList = new QListWidget(this);
    setPoolList();
    volumes = new VirtStorageVolControl(this);

     connect(poolList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(showVolumes(QListWidgetItem*)));
    listLayout = new QHBoxLayout(this);
    listLayout->addWidget(poolList, 2);
    listLayout->addWidget(volumes, 8);
    listWidget = new QWidget(this);
    listWidget->setLayout(listLayout);

    choiceVolume = new QPushButton(QIcon::fromTheme("dialog-ok"), "Choice Volume", this);
    cancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), "Cancel", this);
    connect(choiceVolume, SIGNAL(clicked()), this, SLOT(set_Result()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(set_Result()));
    buttonlayout = new QHBoxLayout(this);
    buttonlayout->addWidget(choiceVolume);
    buttonlayout->addWidget(cancel);
    buttons = new QWidget(this);
    buttons->setLayout(buttonlayout);

    commonLayout = new QVBoxLayout(this);
    commonLayout->addWidget(listWidget);
    commonLayout->addWidget(buttons);
    setLayout(commonLayout);
}

/* public slots */
QStringList VirtVolumeDialog::getResult() const
{
    QStringList _ret;
    _ret.append( poolList->currentItem()->text() );
    _ret.append(volumes->getCurrentVolumeName());
    return _ret;
}

/* private slots */
void VirtVolumeDialog::setPoolList()
{
    virStoragePoolPtr *pools = NULL;
    unsigned int flags = VIR_CONNECT_LIST_STORAGE_POOLS_ACTIVE |
                         VIR_CONNECT_LIST_STORAGE_POOLS_INACTIVE;
    int ret = virConnectListAllStoragePools(currWorkConnect, &pools, flags);
    if ( ret<0 ) {
        poolList->addItem("Not found");
    } else {
        int i = 0;
        while ( pools[i] != NULL ) {
            poolList->addItem( virStoragePoolGetName(pools[i]) );
            virStoragePoolFree(pools[i]);
            i++;
        };
    };
    free(pools);
}
void VirtVolumeDialog::set_Result()
{
    done( (sender()==choiceVolume)?1:0 );
    //qDebug()<<"done";
}
void VirtVolumeDialog::showVolumes(QListWidgetItem *_item)
{
    QString _poolName = _item->text();
    QString _connName;
    volumes->setCurrentStoragePool(
                currWorkConnect,
                _connName,
                _poolName);
}