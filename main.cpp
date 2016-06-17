#include <QCoreApplication>
#include "os/path.hpp"
#include "os.hpp"
#include "string.hpp"
#include <QDebug>
#include <QDir>
#include <Windows.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string path = "d:/1/";
    for(auto i: os::listdir(path))
    {
        printf("%s\n",i.c_str());
    }
    return a.exec();
}
