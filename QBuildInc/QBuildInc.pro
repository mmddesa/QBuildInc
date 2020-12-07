QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

include(QMMDVer)
VERSION = $${MMD_VERV}.$${MMD_VERS}.$${MMD_VERB}.$${MMD_VERR}

message($$VERSION)

#Caracteres UNICODE en octal \\000 o hexa \\xFF
QMAKE_TARGET_COMPANY = MMD
QMAKE_TARGET_PRODUCT = QBuildInc
QMAKE_TARGET_DESCRIPTION = Programa de incremento/decremento de versiones
QMAKE_TARGET_COPYRIGHT = Copyright \\251 Mariano Muñoz Díaz
RC_CODEPAGE = 1200
RC_LANG = 0xc0a

message($$VERSION)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Use.txt
