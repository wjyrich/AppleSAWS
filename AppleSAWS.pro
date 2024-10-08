
QT += core gui printsupport
CONFIG += c++11

MOC_DIR = ./.build
UI_DIR = ./.build
OBJECTS_DIR = ./.build

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppleSAWS
TEMPLATE = app

INCLUDEPATH += src/
INCLUDEPATH += src/relocatablefile
INCLUDEPATH += src/diskfiles
INCLUDEPATH += src/diskfiles/dos33
INCLUDEPATH += src/util
INCLUDEPATH += src/applesoftfile
INCLUDEPATH += src/intbasic
INCLUDEPATH += src/binaryfile
INCLUDEPATH += src/textfile
INCLUDEPATH += src/ui/viewers
INCLUDEPATH += src/imported
INCLUDEPATH += src/internals
INCLUDEPATH += src/ui/diskexplorer/
INCLUDEPATH += src/ui/widgets/
INCLUDEPATH += src/ui
INCLUDEPATH += src/memory
INCLUDEPATH += src/memory/roles


DEFINES += WS_VIDEO

SOURCES += \
    src/intbasic/IntBasicFile.cxx \
    src/main.cpp \
    src/diskfiles/dos33/diskfile.cxx \
    src/diskfiles/dos33/sector.cxx \
    src/diskfiles/dos33/vtoc.cxx \
    src/diskfiles/dos33/catalogsector.cxx \
    src/diskfiles/dos33/tracksectorlist.cxx \
    src/diskfiles/dos33/filedescriptiveentry.cxx \
    src/diskfiles/dos33/genericfile.cxx \
    src/memory/attributedmemory.cpp \
    src/memory/memorycell.cpp \
    src/memory/memrole.cpp \
    src/memory/roles/role_asm_opcode.cpp \
    src/memory/roles/role_asm_operand.cpp \
    src/ui/startupdialog.cpp \
    src/ui/viewers/intbasicfileviewer.cxx \
    src/ui/widgets/notesdialog.cpp \
    src/util/applestring.cxx \
    src/applesoftfile/applesoftfile.cxx \
    src/applesoftfile/applesofttoken.cxx \
    src/applesoftfile/applesoftformatter.cxx \
    src/binaryfile/disassembler.cxx \
    src/binaryfile/binaryfile.cxx \
    src/textfile/textfile.cxx \
    src/ui/catalogwidget.cxx \
    src/ui/viewers/hiresviewwidget.cxx \
    src/ui/viewers/applesoftfileviewer.cxx \
    src/ui/viewers/disassemblerviewer.cpp \
    src/ui/viewers/hexdumpviewer.cpp \
    src/ui/viewers/texthexdumpviewer.cpp \
    src/ui/viewers/mazeviewer.cpp \
    src/ui/viewers/charsetviewer.cpp \
    src/relocatablefile/relocatablefile.cxx \
    src/binaryfile/binaryfilemetadata.cpp \
    src/util/charset.cpp \
    src/ui/widgets/characterwidget.cpp \
    src/ui/viewers/applesoftfiledetailviewer.cpp \
    src/ui/widgets/hexconverter.cpp \
    src/ui/viewers/viewerbase.cpp \
    src/ui/widgets/CharacterSetExplorer.cpp \
    src/ui/widgets/HiresScreenWidget.cpp \
    src/ui/widgets/DisassemblerMetadataDialog.cpp \
    src/binaryfile/EntryPointModel.cpp \
    src/ui/widgets/LocationInfoDialog.cpp \
    src/binaryfile/EntryPoints.cpp \
    src/binaryfile/AssemblerSymbols.cpp \
    src/binaryfile/AssemblerSymbolModel.cpp \
    src/ui/diskexplorer/DiskExplorer.cpp \
    src/ui/diskexplorer/DiskExplorerMapWidget.cpp \
    src/applesoftfile/ApplesoftRetokenizer.cpp \
    src/internals/JumpLineManager.cpp \
    src/ui/widgets/FlowLineTextBrowser.cpp \
    src/util/opcodes.cpp


HEADERS += \
    src/diskfiles/dos33/diskfile.h \
    src/diskfiles/dos33/sector.h \
    src/diskfiles/dos33/vtoc.h \
    src/diskfiles/dos33/catalogsector.h \
    src/diskfiles/dos33/tracksectorlist.h \
    src/diskfiles/dos33/filedescriptiveentry.h \
    src/diskfiles/dos33/genericfile.h \
    src/intbasic/IntBasicFile.h \
    src/memory/attributedmemory.h \
    src/memory/memorycell.h \
    src/memory/memrole.h \
    src/memory/roles/role_asm_opcode.h \
    src/memory/roles/role_asm_operand.h \
    src/ui/startupdialog.h \
    src/ui/viewers/intbasicfileviewer.h \
    src/ui/widgets/notesdialog.h \
    src/util/opcodes.h \
    src/util/util.h \
    src/util/applestring.h \
    src/applesoftfile/applesoftfile.h \
    src/applesoftfile/applesofttoken.h \
    src/binaryfile/disassembler.h \
    src/binaryfile/binaryfile.h \
    src/textfile/textfile.h \
    src/ui/catalogwidget.h \
    src/ui/viewers/hiresviewwidget.h \
    src/ui/viewers/applesoftfileviewer.h \
    src/applesoftfile/applesoftformatter.h \
    src/applesoftfile/applesoftline.h  \
    src/ui/viewers/disassemblerviewer.h \
    src/ui/viewers/hexdumpviewer.h \
    src/ui/viewers/texthexdumpviewer.h \
    src/relocatablefile/relocatablefile.h \
    src/ui/viewers/mazeviewer.h \
    src/binaryfile/binaryfilemetadata.h \
    src/ui/widgets/characterwidget.h \
    src/util/charset.h \
    src/ui/viewers/charsetviewer.h \
    src/ui/viewers/applesoftfiledetailviewer.h \
    src/ui/widgets/hexconverter.h \
    src/ui/widgets/hrcgcontrolsinfo.h \
    src/ui/viewers/viewerbase.h \
    src/ui/viewers/fileviewerinterface.h \
    src/ui/widgets/CharacterSetExplorer.h \
    src/ui/widgets/HiresScreenWidget.h \
    src/ui/widgets/DisassemblerMetadataDialog.h \
    src/binaryfile/EntryPointModel.h \
    src/ui/widgets/LocationInfoDialog.h \
    src/binaryfile/EntryPoints.h \
    src/binaryfile/AssemblerSymbols.h \
    src/binaryfile/AssemblerSymbolModel.h \
    src/binaryfile/MemoryUsageMap.h \
    src/ui/diskexplorer/DiskExplorer.h \
    src/ui/diskexplorer/DiskExplorerMapWidget.h \
    src/applesoftfile/ApplesoftRetokenizer.h \
    src/util/AppleColors.h \
    src/internals/JumpLineManager.h \
    src/ui/widgets/FlowLineTextBrowser.h \
    src/ui/widgets/asciiinfodialog.h

FORMS += \
    src/ui/catalogwidget.ui \
    src/ui/startupdialog.ui \
    src/ui/viewers/applesoftfileviewer.ui \
    src/ui/viewers/disassemblerviewer.ui \
    src/ui/viewers/hexdumpviewer.ui \
    src/ui/viewers/intbasicfileviewer.ui \
    src/ui/viewers/texthexdumpviewer.ui \
    src/ui/viewers/applesoftfiledetailviewer.ui \
    src/ui/widgets/hexconverter.ui \
    src/ui/widgets/hrcgcontrolsinfo.ui \
    src/ui/viewers/viewerbase.ui \
    src/ui/widgets/CharacterSetExplorer.ui \
    src/ui/widgets/DisassemblerMetadataDialog.ui \
    src/ui/widgets/LocationInfoDialog.ui \
    src/ui/widgets/asciiinfodialog.ui \
    src/ui/widgets/notesdialog.ui

RESOURCES += \
    src/resource/resources.qrc

target.path = $$PREFIX/bin
desktop.files = AppleSAWS.desktop
desktop.path = $$PREFIX/share/applications/
icons.path = $$PREFIX/share/icons/hicolor/apps/
icons.files = AppleSAWS.png

INSTALLS += target desktop icons
