/*
  This file is part of Flow.

  Copyright (C) 2015 Sérgio Martins <iamsergio@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "storageplugin.h"
#include "storagebackendinstancemodel.h"
#include "logging.h"

#include <QSettings>
#include <QQmlComponent>
#include <QTimer>

Q_LOGGING_CATEGORY(LOG_PLUGIN_STORAGE, "flow.plugins.storage")

StoragePlugin::StoragePlugin()
    : PluginBase()
    , m_instanceModel(new StorageBackendInstanceModel(this))
    , m_settings(new QSettings("KDAB", "flow-pomodoro", this))
{
    // Must be called outside of CTOR, so that settingsGroup returns the name of the derived class
    QTimer::singleShot(0, this, &StoragePlugin::loadBackendInstances);
}

StorageBackendInstanceModel *StoragePlugin::instanceModel() const
{
    return m_instanceModel;
}

QUrl StoragePlugin::instanceConfigComponentUrl() const
{
    QString key = QString(metaObject()->className()).toLower().replace("plugin", "");
    return QUrl("qrc:/plugins/storage/" + key + "/Config.qml");
}

void StoragePlugin::createBackendInstance()
{
    StorageBackendInstance *instance = createBackend_impl();
    Q_ASSERT(instance);
    if (instance != nullptr) {
        m_instanceModel->appendInstance(instance);
        connectInstance(instance);
        saveBackendInstances();
    }
}

void StoragePlugin::removeBackendInstance(StorageBackendInstance *instance)
{
    Q_ASSERT(instance);
    m_instanceModel->removeInstance(instance);
    instance->deleteLater();
    saveBackendInstances();
}

QQmlComponent *StoragePlugin::configComponent() const
{
    return new QQmlComponent(qmlEngine(), QUrl("qrc:/qml/StoragePluginConfig.qml"),
                             QQmlComponent::PreferSynchronous, const_cast<QObject*>((QObject*)this));
}

void StoragePlugin::loadBackendInstances()
{
    m_instanceModel->clear();
    m_settings->beginGroup(settingsGroup());
    QVariantList backendsConfs = m_settings->value("instances").toList();
    qCDebug(LOG_PLUGIN_STORAGE) << "Loaded" << backendsConfs.count() << "instances from settings";
    m_settings->endGroup();

    foreach (const QVariant &conf, backendsConfs) {
        StorageBackendInstance *backend = fromConfiguration(conf);
        connectInstance(backend);
        m_instanceModel->appendInstance(backend);
    }
}

void StoragePlugin::saveBackendInstances()
{
    StorageBackendInstance::List instances = m_instanceModel->instances();
    QVariantList backendsConfs;
    foreach (StorageBackendInstance *instance, instances) {
        Q_ASSERT(instance != nullptr);
        backendsConfs << instance->configuration();
    }

    m_settings->beginGroup(settingsGroup());
    m_settings->setValue("instances", backendsConfs);
    qCDebug(LOG_PLUGIN_STORAGE) << "Saving" << backendsConfs.count() << "instances to settings. group=" << settingsGroup();
    m_settings->endGroup();
    m_settings->sync();
}

void StoragePlugin::connectInstance(StorageBackendInstance *instance)
{
    connect(instance, &StorageBackendInstance::configurationChanged,
            this, &StoragePlugin::saveBackendInstances, Qt::UniqueConnection);
}
