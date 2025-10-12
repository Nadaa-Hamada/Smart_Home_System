SUMMARY = "Qt Application for Smart Home"
LICENSE = "CLOSED"
SRC_URI = "file://CMakeLists.txt \
           file://main.cpp \
           file://mainwindow.cpp \
           file://mainwindow.h \
           file://mainwindow.ui \
           file://gpio.cpp \
           file://gpio.h \
           file://serialreader.cpp \
           file://serialreader.h \
           file://resources.qrc \
           file://Icons/ \
           file://qt-app.service \
           file://read_all_gpio.sh \
           file://read_all_gpio.service \
          "

DEPENDS += "qtbase qtdeclarative qtwayland qtserialport"
RDEPENDS:${PN} += "smartsensors"

S = "${WORKDIR}"

inherit cmake qt6-cmake systemd

do_install() {
    # install main binary
    install -d ${D}${bindir}
    install -m 0755 ${B}/SmartHome3 ${D}${bindir}/qt-app

    # install qt-app systemd service (if you have one)
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/qt-app.service ${D}${systemd_system_unitdir}/qt-app.service

    # install gpio reader script and service
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/read_all_gpio.sh ${D}${bindir}/read_all_gpio.sh

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/read_all_gpio.service ${D}${systemd_system_unitdir}/read_all_gpio.service
}

# include both services in packaging
SYSTEMD_SERVICE_${PN} = "qt-app.service read_all_gpio.service"
SYSTEMD_AUTO_ENABLE = "enable"

# files to ship
FILES:${PN}:append = "${bindir}/*"
FILES:${PN}:append = "${systemd_system_unitdir}/*"
FILES:${PN}:append = "/lib /lib/systemd /lib/systemd/system /lib/systemd/system/qt-app.service"

