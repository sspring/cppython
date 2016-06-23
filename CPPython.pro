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
    INCLUDEPATH += $$PWD/icu/include
    DEPENDPATH += $$PWD/icu/include
    !contains(QMAKE_TARGET.arch, x86_64){
        CONFIG(debug, debug|release){
            LIBS += -L$$PWD/icu/lib/ -licudtd -licuind -licuiod \
                                       -liculed -liculxd -licutestd \
                                       -licutud -licuucd
            icudt.commands = xcopy /Y \"$$PWD\icu\bin\icudt57d.dll\" \"$$OUT_PWD\"
            icudt.target = icudt
            icuin.commands = xcopy /Y \"$$PWD\icu\bin\icuin57d.dll\" \"$$OUT_PWD\"
            icuin.target = icuin
            icuio.commands = xcopy /Y \"$$PWD\icu\bin\icuio57d.dll\" \"$$OUT_PWD\"
            icuio.target = icuio
            icule.commands = xcopy /Y \"$$PWD\icu\bin\icule57d.dll\" \"$$OUT_PWD\"
            icule.target = icule
            iculx.commands = xcopy /Y \"$$PWD\icu\bin\iculx57d.dll\" \"$$OUT_PWD\"
            iculx.target = iculx
            icutest.commands = xcopy /Y \"$$PWD\icu\bin\icutest57d.dll\" \"$$OUT_PWD\"
            icutest.target = icutest
            icutu.commands = xcopy /Y \"$$PWD\icu\bin\icutu57d.dll\" \"$$OUT_PWD\"
            icutu.target = icutu
            icuuc.commands = xcopy /Y \"$$PWD\icu\bin\icuuc57d.dll\" \"$$OUT_PWD\"
            icuuc.target = icuuc
        }
        CONFIG(release, debug|release){
            LIBS += -L$$PWD/icu/lib/ -licudt -licuin -licuio \
                                       -licule -liculx -licutest \
                                       -licutu -licuuc
            icudt.commands = xcopy /Y \"$$PWD\icu\bin\icudt57.dll\" \"$$OUT_PWD\"
            icudt.target = icudt
            icuin.commands = xcopy /Y \"$$PWD\icu\bin\icuin57.dll\" \"$$OUT_PWD\"
            icuin.target = icuin
            icuio.commands = xcopy /Y \"$$PWD\icu\bin\icuio57.dll\" \"$$OUT_PWD\"
            icuio.target = icuio
            icule.commands = xcopy /Y \"$$PWD\icu\bin\icule57.dll\" \"$$OUT_PWD\"
            icule.target = icule
            iculx.commands = xcopy /Y \"$$PWD\icu\bin\iculx57.dll\" \"$$OUT_PWD\"
            iculx.target = iculx
            icutest.commands = xcopy /Y \"$$PWD\icu\bin\icutest57.dll\" \"$$OUT_PWD\"
            icutest.target = icutest
            icutu.commands = xcopy /Y \"$$PWD\icu\bin\icutu57.dll\" \"$$OUT_PWD\"
            icutu.target = icutu
            icuuc.commands = xcopy /Y \"$$PWD\icu\bin\icuuc57.dll\" \"$$OUT_PWD\"
            icuuc.target = icuuc
        }
    }
    contains(QMAKE_TARGET.arch, x86_64){
        CONFIG(debug, debug|release){
            LIBS += -L$$PWD/icu/lib64/ -licudtd -licuind -licuiod \
                                       -liculed -liculxd -licutestd \
                                       -licutud -licuucd
            icudt.commands = xcopy /Y \"$$PWD\icu\bin64\icudt57d.dll\" \"$$OUT_PWD\"
            icudt.target = icudt
            icuin.commands = xcopy /Y \"$$PWD\icu\bin64\icuin57d.dll\" \"$$OUT_PWD\"
            icuin.target = icuin
            icuio.commands = xcopy /Y \"$$PWD\icu\bin64\icuio57d.dll\" \"$$OUT_PWD\"
            icuio.target = icuio
            icule.commands = xcopy /Y \"$$PWD\icu\bin64\icule57d.dll\" \"$$OUT_PWD\"
            icule.target = icule
            iculx.commands = xcopy /Y \"$$PWD\icu\bin64\iculx57d.dll\" \"$$OUT_PWD\"
            iculx.target = iculx
            icutest.commands = xcopy /Y \"$$PWD\icu\bin64\icutest57d.dll\" \"$$OUT_PWD\"
            icutest.target = icutest
            icutu.commands = xcopy /Y \"$$PWD\icu\bin64\icutu57d.dll\" \"$$OUT_PWD\"
            icutu.target = icutu
            icuuc.commands = xcopy /Y \"$$PWD\icu\bin64\icuuc57d.dll\" \"$$OUT_PWD\"
            icuuc.target = icuuc
        }
        CONFIG(release, debug|release){
            LIBS += -L$$PWD/icu/lib64/ -licudt -licuin -licuio \
                                       -licule -liculx -licutest \
                                       -licutu -licuuc
            icudt.commands = xcopy /Y \"$$PWD\icu\bin64\icudt57.dll\" \"$$OUT_PWD\"
            icudt.target = icudt
            icuin.commands = xcopy /Y \"$$PWD\icu\bin64\icuin57.dll\" \"$$OUT_PWD\"
            icuin.target = icuin
            icuio.commands = xcopy /Y \"$$PWD\icu\bin64\icuio57.dll\" \"$$OUT_PWD\"
            icuio.target = icuio
            icule.commands = xcopy /Y \"$$PWD\icu\bin64\icule57.dll\" \"$$OUT_PWD\"
            icule.target = icule
            iculx.commands = xcopy /Y \"$$PWD\icu\bin64\iculx57.dll\" \"$$OUT_PWD\"
            iculx.target = iculx
            icutest.commands = xcopy /Y \"$$PWD\icu\bin64\icutest57.dll\" \"$$OUT_PWD\"
            icutest.target = icutest
            icutu.commands = xcopy /Y \"$$PWD\icu\bin64\icutu57.dll\" \"$$OUT_PWD\"
            icutu.target = icutu
            icuuc.commands = xcopy /Y \"$$PWD\icu\bin64\icuuc57.dll\" \"$$OUT_PWD\"
            icuuc.target = icuuc
        }
    }
    QMAKE_EXTRA_TARGETS += icudt icuin icuio icule iculx icutest icutu icuuc
    PRE_TARGETDEPS += icudt icuin icuio icule iculx icutest icutu icuuc
}

