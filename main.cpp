#include <QCoreApplication>
#include "os/path.hpp"
#include "os.hpp"
#include "string.hpp"
#include <QDebug>
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string path = "d:/1/2.dcm";
    auto p = os::path::splitext(path);
    printf("%s %s",std::get<0>(p).c_str(),
           std::get<1>(p).c_str());
    //qDebug()<< QDir(QString::fromStdString(os::path::normpath(path))).entryInfoList().count();
    return a.exec();
}
