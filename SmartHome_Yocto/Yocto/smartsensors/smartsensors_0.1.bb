DESCRIPTION = "Smart Sensors C++ Service"
LICENSE = "CLOSED"

SRC_URI = " \
    file://main.cpp \
    file://gpio.cpp \
    file://recieve.cpp \
    file://serial.cpp \
    file://gpio.h \
    file://recieve.h \
    file://serial.h \
    file://Makefile \
    file://smartsensors.service \
"
S = "${WORKDIR}"
TARGET_CC_ARCH += "${CXXFLAGS}"

do_compile() {
    oe_runmake CC="${CC}" CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}"
}

do_install() {
    install -d ${D}${bindir}

    if [ -f ${S}/build/smartsensors ]; then
        install -m 0755 ${S}/build/smartsensors ${D}${bindir}/smartsensors
    elif [ -f ${S}/smartsensors ]; then
        install -m 0755 ${S}/smartsensors ${D}${bindir}/smartsensors
    else
        echo "Error: smartsensors binary not found!"
        exit 1
    fi

    # Copy systemd service file
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/smartsensors.service ${D}${systemd_system_unitdir}
}


SYSTEMD_SERVICE:${PN} = "smartsensors.service"
inherit systemd

INSANE_SKIP:${PN} += "ldflags"
