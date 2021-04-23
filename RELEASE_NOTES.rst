..
    Copyright 2020-2021 MicroEJ Corp. All rights reserved.
    This library is provided in source code for use, modification and test, subject to license terms.
    Any modification of the source code will break MicroEJ Corp. warranties on the whole library.

.. _release-notes:
.. |BOARD_NAME| replace:: Thunderboard EFR32BG22
.. |BOARD_REVISION| replace:: A01
.. |PLATFORM_NAME| replace:: EFR32BG22 Platform
.. |PLATFORM_VER| replace:: 0.2.0
.. |RCP| replace:: MICROEJ SDK
.. |PLATFORM| replace:: MicroEJ Platform
.. |PLATFORMS| replace:: MicroEJ Platforms
.. |SIM| replace:: MicroEJ Simulator
.. |ARCH| replace:: MicroEJ Architecture
.. |CIDE| replace:: MICROEJ SDK
.. |RTOS| replace:: Micrium RTOS
.. |MANUFACTURER| replace:: Silicon Labs

.. _README MicroEJ BSP: ./efr32bg22_micriumos-bsp/projects/microej/README.rst
.. _RELEASE NOTES: ./RELEASE_NOTES.rst
.. _CHANGELOG: ./CHANGELOG.rst

.. _release-notes:

========================================================
|PLATFORM| Release Notes for |MANUFACTURER| |BOARD_NAME|
========================================================

Description
===========

This is the release notes of the |PLATFORM| for |BOARD_NAME|.

Versions
========

Platform
--------

|PLATFORM_VER|

Dependencies
------------

This |PLATFORM| contains the following dependencies:

.. list-table::
   :header-rows: 1
   
   * - Dependency Name
     - Version
   * - Architecture (flopi4I35)
     - 7.14.0

Please refer to the |PLATFORM| `module description file <./efr32bg22_micriumos-configuration/module.ivy>`_ 
for more details.

Board Support Package
---------------------

- BSP provider: |MANUFACTURER| (``gecko_sdk``)
- BSP version: v3.0.0

For downloading the SDK, please refer to the |MANUFACTURER| ``Simplicity Studio``
available `here
<https://www.silabs.com/developers/simplicity-studio>`__.

Third Party Software
--------------------

Third party softwares used in BSP can be found `here 
<./efr32bg22_micriumos-bsp/projects/microej/gecko_sdk_3.0.0>`__.

Here is a list of the most important ones:

.. list-table::
   :widths: 3 3 3

   * - RTOS 
     - Micrium OS
     - 5.9.0

Known issues/limitations
========================

- None

Platform Memory Layout
======================

Memory Sections
---------------

Each memory section is discribed in the IAR linker file available
`here
<./efr32bg22_micriumos-bsp/projects/microej/autogen/linkerfile.icf>`__.

Memory Layout
-------------

.. list-table::
   :header-rows: 1
   
   * - Section Content
     - Section Source
     - Section Destination
     - Memory Type
   * - MicroEJ Application static
     - ``.bss.soar``
     - ``.bss``
     - internal RAM
   * - MicroEJ Application threads stack blocks 
     - ``.bss.vm.stacks.java``
     - ``.bss``
     - internal RAM
   * - MicroEJ Core Engine internal heap 
     - ``ICETEA_HEAP``
     - ``.bss``
     - internal RAM
   * - MicroEJ Application heap 
     - ``_java_heap``
     - ``.bss``
     - internal RAM
   * - MicroEJ Application Immortal Heap 
     - ``_java_immortals``
     - ``.bss``
     - internal RAM
   * - MicroEJ Application and Library code 
     - ``.text.soar``
     - ``.rodata``
     - internal Flash

Please also refer to the MicroEJ docs website page available `here
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/coreEngine.html#link>`__
for more details.
