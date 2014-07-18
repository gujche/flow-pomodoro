/*
  This file is part of Flow.

  Copyright (C) 2013-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "task.h"

#include <QObject>
#include <QString>
#include <QPointer>

class QTimer;
class TaskStorage;
class QuickView;

class Controller : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool firstSecondsAfterAdding READ firstSecondsAfterAdding NOTIFY firstSecondsAfterAddingChanged)
    Q_PROPERTY(int remainingMinutes READ remainingMinutes NOTIFY remainingMinutesChanged)
    Q_PROPERTY(int currentTaskDuration READ currentTaskDuration NOTIFY currentTaskDurationChanged)
    Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expandedChanged)
    Q_PROPERTY(Page currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int defaultPomodoroDuration READ defaultPomodoroDuration WRITE setDefaultPomodoroDuration NOTIFY defaultPomodoroDurationChanged)
    Q_PROPERTY(Task* currentTask READ currentTask NOTIFY currentTaskChanged) // Task being played
    Q_PROPERTY(Task* rightClickedTask READ rightClickedTask WRITE setRightClickedTask NOTIFY rightClickedTaskChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex NOTIFY selectedIndexChanged)
    // Editing task properties
    Q_PROPERTY(int indexBeingEdited READ indexBeingEdited NOTIFY indexBeingEditedChanged)
    Q_PROPERTY(QObject* taskBeingEdited READ taskBeingEdited NOTIFY indexBeingEditedChanged)
    Q_PROPERTY(EditMode editMode READ editMode NOTIFY editModeChanged)
    // Shortcuts
    Q_PROPERTY(bool paused  READ paused  NOTIFY taskStatusChanged)
    Q_PROPERTY(bool stopped READ stopped NOTIFY taskStatusChanged)
    Q_PROPERTY(bool running READ running NOTIFY taskStatusChanged)
    // Popup properties
    Q_PROPERTY(QString popupText READ popupText NOTIFY popupTextChanged)
    Q_PROPERTY(bool popupVisible READ popupVisible NOTIFY popupVisibleChanged)
    //Editing Tag properties
    Q_PROPERTY(TagEditStatus tagEditStatus READ tagEditStatus NOTIFY tagEditStatusChanged)
    // Other properties
    Q_PROPERTY(qreal dpiFactor READ dpiFactor CONSTANT)
public:

    enum Page {
        InvalidPage = 0,
        TheQueuePage,
        ConfigurePage,
        AboutPage
    };
    Q_ENUMS(Page)

    enum EditMode {
        EditModeNone = 0, // We're not editing a task
        EditModeInline, // We're editing inline
        EditModeEditor // We're using the task editor
    };
    Q_ENUMS(EditMode)

    enum TagEditStatus {
        TagEditStatusNone = 0,
        TagEditStatusEdit, // Tag is being edited
        TagEditStatusNew // Tag is being created
    };
    Q_ENUMS(TagEditStatus)

    Controller(QuickView *quickView, TaskStorage *model, QObject *parent = 0);
    ~Controller();

    int remainingMinutes() const;
    int currentTaskDuration() const; // in minutes
    Task *currentTask() const;
    int indexBeingEdited() const;
    EditMode editMode() const;

    bool expanded() const;
    void setExpanded(bool expanded);

    bool firstSecondsAfterAdding() const;

    Controller::Page currentPage() const;
    void setCurrentPage(Page page);

    void setDefaultPomodoroDuration(int duration);
    int defaultPomodoroDuration() const;

    int selectedIndex() const;
    void setSelectedIndex(int index);

    bool running() const;
    bool stopped() const;
    bool paused() const;

    qreal dpiFactor() const;

    bool popupVisible() const;
    void setPopupVisible(bool);

    QString popupText() const;
    void setPopupText(const QString &);

    Task *taskBeingEdited() const;
    TagEditStatus tagEditStatus() const;

    Task *rightClickedTask() const;
public Q_SLOTS:
    void addTask(const QString &text, bool startEditMode);
    void removeTask(int index);

    void startPomodoro(int queueIndex);
    void stopPomodoro();
    void pausePomodoro();

    void toggleSelectedIndex(int index);
    void cycleSelectionUp();
    void cycleSelectionDown();

    void showQuestionPopup(QObject *obj, const QString &text, const QString &callback);
    void onPopupButtonClicked(bool okClicked);

    void editTag(const QString &tagName);
    bool renameTag(const QString &oldName, const QString &newName);

    void editTask(int proxyIndex, EditMode);

    void beginAddingNewTag();
    void endAddingNewTag(const QString &tagName);

    void requestContextMenu(Task *);
private Q_SLOTS:
    void onTimerTick();

Q_SIGNALS:
    void remainingMinutesChanged();
    void currentTaskDurationChanged();
    void taskFinished();
    void expandedChanged();
    void firstSecondsAfterAddingChanged();
    void currentPageChanged();
    void defaultPomodoroDurationChanged();
    void taskStatusChanged();
    void selectedIndexChanged();
    void forceFocus(int index);
    void currentTaskChanged();
    void popupVisibleChanged();
    void popupTextChanged();
    void indexBeingEditedChanged();
    void editModeChanged();
    void tagEditStatusChanged();
    void rightClickedTaskChanged();

private:
    void setTaskStatus(TaskStatus status);
    void setTagEditStatus(TagEditStatus);
    void setRightClickedTask(Task *);
    bool eventFilter(QObject *, QEvent *) Q_DECL_OVERRIDE;

    int m_currentTaskDuration;
    QTimer *m_tickTimer;
    QTimer *m_afterAddingTimer;
    int m_elapsedMinutes;
    bool m_expanded;
    int m_indexBeingEdited;
    TaskStorage *m_taskStorage;
    Task::Ptr m_currentTask;
    Page m_page;
    int m_defaultPomodoroDuration;
    int m_selectedIndex;
    QuickView *m_quickView;
    bool m_popupVisible;
    QString m_popupText;
    QString m_popupOkCallback;
    QPointer<QObject> m_popupCallbackOwner;
    Tag::Ptr m_tagBeingEdited;
    QPointer<Task> m_taskBeingEdited;
    EditMode m_editMode;
    TagEditStatus m_tagEditStatus;
    QPointer<Task> m_rightClickedTask;
    Task * m_invalidTask;
};

#endif
