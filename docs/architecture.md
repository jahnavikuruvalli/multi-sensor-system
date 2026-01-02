# Multi-Sensor-System Architecture

## Overview
This system consists of multiple microcontroller nodes connected through
UART and I2C, coordinated by an arbitration layer, and ingested by a central
compute node.

## Nodes
- Arduino Uno #1: Environmental sampling node
- Arduino Uno #2: Event-driven node
- Raspberry Pi Pico 2W: Arbiter and time authority
- Raspberry Pi 5: Ingestion, storage, and observability
- Odroid #1: Analytics
- Odroid #2: Redundancy and replay

## Design Principles
- Non-blocking firmware
- Explicit ownership of buses
- Observable behavior at every layer
- Failure containment
