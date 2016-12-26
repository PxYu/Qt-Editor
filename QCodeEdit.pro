QT += widgets

HEADERS         = \
                  mainwindow.h \
    QCodeEdit/qcodecpp.h \
    QCodeEdit/qcodeedit.h
SOURCES         = \
                  mainwindow.cpp \
                  main.cpp \
    QCodeEdit/qcodecpp.cpp \
    QCodeEdit/qcodeedit.cpp

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
