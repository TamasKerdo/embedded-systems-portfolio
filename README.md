# Embedded Systems Portfolio

A structured embedded systems learning portfolio documenting a career transition from backend software engineering into embedded software engineering.

## Learning Roadmap

| Phase | Weeks | Focus |
|---|---|---|
| 1 | 1–3 | C/C++ fundamentals + toolchain |
| 2 | 4–9 | Bare-metal + FreeRTOS on STM32F4 Discovery |
| 3 | 10–15 | Embedded Linux + Yocto on Raspberry Pi 4 |
| 4 | 16–21 | Automotive/safety-critical (AUTOSAR, ISO 26262, CAN-FD, UDS) |
| 5 | 22–26 | Interview preparation |

## Portfolio Projects

### 1. FreeRTOS Sensor Node — STM32F4 Discovery *(Phase 2)*
- BME280 temperature/humidity/pressure sensor over I2C
- FreeRTOS task scheduling, queues, watchdog
- UART debug output
- GitHub Actions CI pipeline with Unity unit tests

### 2. Custom Yocto Linux Image — Raspberry Pi 4 *(Phase 3)*
- Custom Yocto layer with kernel driver
- systemd service
- GitHub Actions CI pipeline

### 3. CAN Bus Logger with UDS Diagnostic Services *(Phase 4)*
- CAN-FD communication using SN65HVD230 transceivers
- UDS diagnostic services implementation
- python-can protocol tests via virtual CAN interface

## Development Environment

All builds run inside a Docker container — the same image runs locally and in CI, eliminating environment differences.

### Toolchain
- `arm-none-eabi-gcc 13.2` — ARM cross-compiler for STM32F407 Cortex-M4
- `cmake` + `make` — build system
- `cppcheck` — static analysis
- Host `gcc` with ASAN/UBSAN — sanitizer-based host testing

### CI/CD Pipeline (GitHub Actions)

Every commit triggers three automated steps:

| Step | Tool | Purpose |
|---|---|---|
| Lint | cppcheck | Static analysis — catches bugs the compiler misses |
| Test | gcc + ASAN/UBSAN | Host-side sanitizer tests — memory and UB checks |
| Build | arm-none-eabi-gcc | Cross-compile firmware for STM32F407 Cortex-M4 |

Pipeline is designed to **fail fast** — cheap checks (lint, tests) run before the expensive ARM compilation step.

### Compiler Flags (STM32F407 Cortex-M4)
```
-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
```

## Hardware

| Device | Purpose |
|---|---|
| STM32F4 Discovery (STM32F407VGT6) | Primary development board — Phase 2 |
| InnoMaker LA1010 Logic Analyzer | I2C, SPI, UART, CAN signal debugging |
| AZDelivery GY-BME280 | Temperature/humidity/pressure sensor |
| 2x CP2102 USB-UART adapters | UART debug output |
| Raspberry Pi 4 | Embedded Linux development — Phase 3 |
| 2x SN65HVD230 CAN transceivers | CAN bus logger — Phase 4 |

> **Portfolio projects** (Phase 2 onward) live in separate repositories, each with their own pipeline:
> - [`freertos-sensor-node`](https://github.com/TamasKerdo/freertos-sensor-node) — Phase 2
> - [`yocto-rpi4`](https://github.com/TamasKerdo/yocto-rpi4) — Phase 3
> - [`can-bus-logger`](https://github.com/TamasKerdo/can-bus-logger) — Phase 4

## Pipeline Roadmap

| Week | Addition |
|---|---|
| 4 | Unity test framework for bare-metal unit tests |
| 4 | st-flash/OpenOCD stage for STM32 flashing via ST-LINK/V2 |
| 9 | QEMU-based firmware smoke tests (ARM emulation, no hardware needed) |
| 10 | BME280 I2C driver tests with mock HAL |
| 15 | Yocto build stage for Raspberry Pi 4 image |
| 20 | python-can CAN protocol tests via virtual CAN (vcan) interface |
