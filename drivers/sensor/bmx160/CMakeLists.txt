# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources(bmx160.c)
zephyr_library_sources_ifdef(CONFIG_BMX160_TRIGGER bmx160_trigger.c)
