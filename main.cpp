#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include <MButton>
#include <MToolBar>
#include <MAction>
#include <MWidgetAction>
#include <MTextEdit>
#include <QObject>

#include "mainpage.h"

int main(int argc, char *argv[]){
    MApplication application(argc, argv);
    application.setOrganizationName("arcean");
    application.setOrganizationDomain("arcean.com");
    application.setApplicationName("SketchIt");

    MApplicationWindow window;
    MainPage page;

    page.appear(&window);

    window.showFullScreen();

    return application.exec();
 }
