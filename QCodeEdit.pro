QT += widgets

INCLUDEPATH += CMM/include

HEADERS         = \
                  mainwindow.h \
    QCodeEdit/qcodecpp.h \
    QCodeEdit/qcodeedit.h \
    AST.h \
    SourceMgr.h \
    CMMParser.h \
    CMMLexer.h

SOURCES         = \
                  mainwindow.cpp \
                  main.cpp \
    QCodeEdit/qcodecpp.cpp \
    QCodeEdit/qcodeedit.cpp \
    CMM/src/AST.cpp \
    CMM/src/SourceMgr.cpp \
    CMM/src/CMMParser.cpp \
    CMM/src/CMMLexer.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/syntaxhighlighter
INSTALLS += target


wince*: {
   addFiles.files = main.cpp mainwindow.cpp
   addFiles.path = .
   DEPLOYMENT += addFiles
}

CONFIG += static

RESOURCES += \
    resources.qrc

QMAKE_LFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++

