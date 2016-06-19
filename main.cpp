#include <QCoreApplication>
#include "os/path.hpp"
#include "os.hpp"
#include "string.hpp"
#include "builtin.hpp"
#include <QDebug>
#include <QDir>
#include <Windows.h>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    for(std::string f: os::walk(R"(F:\Warcraft3)"))
    {
        printf("%s\n",f.c_str());
    }
    return a.exec();
}
