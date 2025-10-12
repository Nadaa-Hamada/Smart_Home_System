#!/bin/sh
# /usr/bin/read_all_gpio.sh
# Reads GPIO 17, 22, 23, 27 and writes values to /run/gpio_<pin>.txt

GPIO_PINS="17 22 24 27"
RUN_DIR="/run"

# Ensure /run exists and files created
for PIN in $GPIO_PINS; do
    GPIO_PATH="/sys/class/gpio/gpio${PIN}"
    OUT_FILE="${RUN_DIR}/gpio_${PIN}.txt"

    touch "${OUT_FILE}"
    chmod 0644 "${OUT_FILE}"

    # Export if needed
    if [ ! -d "${GPIO_PATH}" ]; then
        echo "${PIN}" > /sys/class/gpio/export 2>/dev/null || true
        sleep 0.1
        echo "in" > "${GPIO_PATH}/direction" 2>/dev/null || true
    fi
done

# Continuous reading loop
while true; do
    for PIN in $GPIO_PINS; do
        GPIO_PATH="/sys/class/gpio/gpio${PIN}"
        OUT_FILE="${RUN_DIR}/gpio_${PIN}.txt"

        if [ -r "${GPIO_PATH}/value" ]; then
            cat "${GPIO_PATH}/value" > "${OUT_FILE}" 2>/dev/null || echo 0 > "${OUT_FILE}"
        else
            echo 0 > "${OUT_FILE}"
        fi
    done
    sleep 1
done
