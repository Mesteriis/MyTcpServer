#include "gui/guicore.hpp"

#include <QApplication>
#include <QLockFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    guicore w;

    QCoreApplication::setOrganizationName("ShadeInc");
    QCoreApplication::setOrganizationDomain("www.sh-inc.ru");
    QCoreApplication::setApplicationName("Simple Tcp Graf Server");

    QLockFile lockFile(QDir::temp().absoluteFilePath("Server.lock"));
        if(!lockFile.tryLock(100)){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("The application is already running..\n"
                               "Only one instance of the application is allowed to run.");
            msgBox.exec();
            return 1;
        }

    w.move(0,10);
    w.show();
    return a.exec();
}
