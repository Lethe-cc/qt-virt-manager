#include "ram_fstype.h"

RAMFsType::RAMFsType(QWidget *parent, QString _type) :
    _FsType(parent, _type)
{
    wrPolicyLabel->setVisible(false);
    wrPolicy->setVisible(false);
    formatLabel->setVisible(false);
    format->setVisible(false);
    driverLabel->setVisible(false);
    driver->setVisible(false);
    readOnly->setVisible(false);
    commonLayout->removeWidget(sourceLabel);
    delete sourceLabel;
    sourceLabel = NULL;
    commonLayout->addWidget(new QLabel("Usage (MiB):", this), 4, 0);
    commonLayout->removeWidget(source);
    delete source;
    source = NULL;
    usage = new QSpinBox(this);
    usage->setRange(0, 1024);
    commonLayout->addWidget(usage, 4, 1);
    target->setPlaceholderText("Target guest directory");
}

/* public slots */
QDomDocument RAMFsType::getDevDocument() const
{
    QDomDocument doc = QDomDocument();
    QDomElement _source, _target, _device, _devDesc;
    _device = doc.createElement("device");
    _devDesc = doc.createElement("filesystem");
    _source = doc.createElement("source");
    _source.setAttribute("usage", QString::number( usage->value()*1024 ));
    _devDesc.appendChild(_source);
    _target = doc.createElement("target");
    _target.setAttribute("dir", target->text());
    _devDesc.appendChild(_target);
    _devDesc.setAttribute("type", "ram");
    _device.appendChild(_devDesc);
    doc.appendChild(_device);
    return doc;
}