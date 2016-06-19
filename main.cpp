#include <QCoreApplication>
#include "os/path.hpp"
#include "os.hpp"
#include "string.hpp"
#include "builtin.hpp"
#include <QDebug>
#include <QDir>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    for(std::string f: os::listdir("d:/"))
    {
        printf("%s\n",f.c_str());
    }
    return a.exec();
}
