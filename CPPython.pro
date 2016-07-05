#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T10:37:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CPPython
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11
TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    os/path.hpp \
    os.hpp \
    string.hpp \
    util.hpp \
    builtin.hpp

win32{
    INCLUDEPATH += $$PWD/iconv/include
    !contains(QMAKE_TARGET.arch, x86_64){
        CONFIG(release, debug|release){
            LIBS += -L$$PWD/iconv/lib/ -llibiconv
            iconv.commands = xcopy /Y \"$$PWD\iconv\lib\libiconv.dll\" \"$$OUT_PWD\"
            iconv.target = iconv
        }
        CONFIG(debug, debug|release){
            LIBS += -L$$PWD/iconv/lib/ -llibiconvD
            iconv.commands = xcopy /Y \"$$PWD\iconv\lib\libiconvD.dll\" \"$$OUT_PWD\"
            iconv.target = iconv
        }
    }
    contains(QMAKE_TARGET.arch, x86_64){
        CONFIG(release, debug|release){
            LIBS += -L$$PWD/iconv/lib64/ -llibiconv
            iconv.commands = xcopy /Y \"$$PWD\iconv\lib64\libiconv.dll\" \"$$OUT_PWD\"
            iconv.target = iconv
        }
        CONFIG(debug, debug|release){
            LIBS += -L$$PWD/iconv/lib64/ -llibiconvD
            iconv.commands = xcopy /Y \"$$PWD\iconv\lib64\libiconvD.dll\" \"$$OUT_PWD\"
            iconv.target = iconv
        }
    }
    QMAKE_EXTRA_TARGETS += iconv
    PRE_TARGETDEPS += iconv
}

