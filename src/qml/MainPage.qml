import QtQuick 2.0
import Controller 1.0
import QtGraphicalEffects 1.0

Page {
    id: root
    page: Controller.MainPage

    Rectangle {
        color: _style.queueBackgroundColor
        anchors.fill: parent
        radius: parent.radius

        Component {
            id: taskListComponent
            TaskListView {
                id: stagedView
                model: _storage.stagedTasksModel
                emptyText: qsTr("No queued tasks for today.") + "\n"+ qsTr("Please create new ones or pick some from your archive.")
            }
        }

        Component {
            id: decentTabViewComponent
            DecentTabView { }
        }

        Loader {
            anchors.topMargin: _style.marginSmall
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            asynchronous: true
            visible: _controller.queueType === Controller.QueueTypeToday
            sourceComponent: _controller.taskListRequested ? taskListComponent
                                                           : null
        }

        Loader {
            id: tabView
            // Delayed loading for startup performance improvement
            visible: _controller.queueType !== Controller.QueueTypeToday
            anchors.margins: _style.marginSmall
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            sourceComponent:  _controller.archiveRequested ? decentTabViewComponent
                                                           : null
        }

        LinearGradient {
            id: rightScrollIndicator
            anchors.fill: tabView
            visible: !tabView.atXEnd && tabView.visible
            start: Qt.point(tabView.width - _style.tagScrollIndicatorFadeWidth, 0)
            end: Qt.point(tabView.width, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 1.0; color: _style.queueBackgroundColor }
            }
        }

        LinearGradient {
            id: leftScrollIndicator
            visible: !tabView.atXBeginning && tabView.visible
            anchors.fill: tabView
            start: Qt.point(0, 0)
            end: Qt.point(_style.tagScrollIndicatorFadeWidth, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: _style.queueBackgroundColor }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }

        Component {
            id: archiveViewComponent
            TaskListView {
                id: archiveView
                model: _controller.currentTabTag == null ? _storage.untaggedTasksModel : _controller.currentTabTag.taskModel
                emptyText: _controller.currentTabTag == null ? qsTr("No archived untagged tasks found.")
                                                             : qsTr("No archived tasks found with tag %1").arg(_controller.currentTabTag.name)
            }
        }

        Loader {
            anchors.topMargin: _style.marginMedium
            anchors.top: tabView.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            visible: tabView.visible
            sourceComponent: _controller.archiveRequested ? archiveViewComponent
                                                          : null
        }
    }
}
