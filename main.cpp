#include <QCoreApplication>
#include "os/path.hpp"
#include "os.hpp"
#include "string.hpp"
#include "os/path.hpp"
#include "builtin.hpp"
#include <QDebug>
#include <QDir>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    for(std::string f:os::walk("/home/cracker/Downloads"))
    {
        printf("%s\n",f.c_str());
    }
    return a.exec();
}
