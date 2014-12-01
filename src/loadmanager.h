#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <QObject>

class LoadManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool inlineEditorRequested READ inlineEditorRequested WRITE setInlineEditorRequested NOTIFY inlineEditorRequestedChanged)
    Q_PROPERTY(bool questionPopupRequested READ questionPopupRequested WRITE setQuestionPopupRequested NOTIFY questionPopupRequestedChanged)
    Q_PROPERTY(bool archiveRequested READ archiveRequested WRITE setArchiveRequested NOTIFY archiveRequestedChanged)
    Q_PROPERTY(bool taskListRequested READ taskListRequested WRITE setTaskListRequested NOTIFY taskListRequestedChanged)
    Q_PROPERTY(bool configurePopupRequested READ configurePopupRequested WRITE setConfigurePopupRequested NOTIFY configurePopupRequestedChanged)
    Q_PROPERTY(bool configurePageRequested READ configurePageRequested WRITE setConfigurePageRequested NOTIFY configurePageRequestedChanged)
    Q_PROPERTY(bool aboutPageRequested READ aboutPageRequested WRITE setAboutPageRequested NOTIFY aboutPageRequestedChanged)
    Q_PROPERTY(bool taskContextMenuRequested READ taskContextMenuRequested WRITE setTaskContextMenuRequested NOTIFY taskContextMenuRequestedChanged)
public:
    explicit LoadManager(QObject *parent = 0);

    void setTaskContextMenuRequested(bool);
    bool taskContextMenuRequested() const;

    bool useDelayedLoading() const;

    void setAboutPageRequested(bool);
    bool aboutPageRequested() const;

    void setConfigurePageRequested(bool);
    bool configurePageRequested() const;

    void setConfigurePopupRequested(bool);
    bool configurePopupRequested() const;

    void setArchiveRequested(bool);
    bool archiveRequested() const;

    void setTaskListRequested(bool);
    bool taskListRequested() const;

    void setQuestionPopupRequested(bool);
    bool questionPopupRequested() const;

    void setInlineEditorRequested(bool);
    bool inlineEditorRequested() const;

Q_SIGNALS:
    void inlineEditorRequestedChanged();
    void questionPopupRequestedChanged();
    void archiveRequestedChanged();
    void taskListRequestedChanged();
    void configurePopupRequestedChanged();
    void configurePageRequestedChanged();
    void aboutPageRequestedChanged();
    void taskContextMenuRequestedChanged();

private:

    bool m_taskContextMenuRequested;
    bool m_aboutPageRequested;
    bool m_configurePageRequested;
    bool m_configurePopupRequested;
    bool m_archiveRequested;
    bool m_taskListRequested;
    bool m_questionPopupRequested;
    bool m_inlineEditorRequested;
};

#endif