//
//  !!! Dit bestand moet je in principe NIET wijzigen !!!
//

#include  <QApplication>
#include  "SchaakGUI.h"

int main(int argc, char *argv[])
{
#if defined(WIN64) || defined(_WIN64) || defined(WIN32) || defined(_WIN32)
    qputenv("QT_QPA_PLATFORM_PLUGIN_PATH", "C:\\Qt\\5.15.2\\mingw81_64\\plugins\\");
#endif
    QApplication a(argc, argv);
    SchaakGUI w;
    w.show();

    return a.exec();
}
