# Multi-Sensor-System

> **A distributed, event-driven embedded system integrating heterogeneous sensors across multiple microcontrollers with time synchronization, fault tolerance, and centralized observability.**

---

## Overview

**multi-sensor-system** is a large-scale embedded systems project focused on **end-to-end system design**, not individual sensors or isolated firmware.

The project integrates multiple microcontrollers, single-board computers, and a wide variety of sensors into a **coordinated, distributed system** that:

- collects environmental and event-driven data  
- synchronizes events across nodes  
- tolerates partial failures  
- logs and analyzes system behavior centrally  
- exposes system state through a minimal web interface  

This project is designed to be **completed fully**, not incrementally demoed.

---

## Project Goals

The primary goals of this project are to:

- Design and implement a **distributed embedded system**
- Practice **event-driven, non-blocking firmware architecture**
- Handle **real-world communication and timing constraints**
- Build **fault detection and recovery mechanisms**
- Develop strong intuition for **system-level tradeoffs**
- Create a realistic foundation for future **custom microcontroller / ISA design**

This is a **systems engineering project**, not a language or framework showcase.

---

## Hardware Architecture

### Controllers (all are required)

| Device | Role |
|------|-----|
| Arduino Uno #1 | Environmental / periodic sensor node |
| Arduino Uno #2 | Event-driven / interrupt-heavy sensor node |
| Raspberry Pi Pico 2W | Real-time arbiter and time authority |
| Raspberry Pi 5 | Central ingestion, logging, and web UI |
| Odroid #1 | Analytics and anomaly detection |
| Odroid #2 | Redundancy, replay, and verification |

---

## Node Responsibilities

### Arduino Uno #1 — Environmental Sensor Node
- Periodic sampling
- Low-urgency sensors (temperature, humidity, light, sound, water level, etc.)
- Non-blocking firmware
- Heartbeat messages

---

### Arduino Uno #2 — Event Sensor Node
- Interrupt-driven sensors (PIR, ultrasonic, flame, shock, IR, laser, etc.)
- Debouncing and event queueing
- Priority tagging for events

---

### Raspberry Pi Pico 2W — Real-Time Arbiter
- Receives data from both Arduinos
- Assigns timestamps to all events
- Prioritizes and reorders messages
- Detects missing heartbeats and stalled nodes
- Forwards a unified event stream upstream

This node acts as the **timing and coordination authority** of the system.

---

### Raspberry Pi 5 — System Brain
- Receives the unified event stream
- Performs persistent logging
- Maintains system-wide state
- Hosts a **minimal web UI** for observability and debugging

UI polish is not a goal — correctness and clarity are.

---

### Odroid #1 — Analytics Node
- Cross-sensor correlation
- Anomaly detection
- Long-window statistics
- Confidence / trust scoring

---

### Odroid #2 — Redundancy & Replay Node
- Consumes the same data stream independently
- Replays logs
- Verifies analytics results
- Acts as a consistency and correctness check

---

## Communication Model

### Arduino ↔ Pico
- **UART**: primary event and data stream  
- **I2C**: configuration, health checks, status queries  

### Pico ↔ Raspberry Pi 5
- USB / UART / network (implementation detail)

### Raspberry Pi 5 ↔ Odroids
- Networked message stream

A hybrid communication model is intentionally used to surface real-world failure modes and design tradeoffs.

---

## Firmware Philosophy

- Event-driven, non-blocking design
- No `delay()`-based logic
- Explicit timing and state machines
- Clear separation between:
  - sensor drivers
  - communication layers
  - application logic
- C / C++ with libraries allowed  
  *(language choice is secondary to system behavior)*

---

## Project Phases

The project is executed in **strict, well-defined phases**.  
Each phase represents a **stable, runnable system state** and must be fully completed before moving on.

| Phase | Focus |
|-----|------|
| Phase 0 | Specification & architecture |
| Phase 1 | Single environmental node stability |
| Phase 2 | Event-driven node stability |
| Phase 3 | Multi-MCU coexistence |
| Phase 4 | Pico arbitration & time synchronization |
| Phase 5 | Central ingestion & logging |
| Phase 6 | Analytics |
| Phase 7 | Redundancy & replay |
| Phase 8 | Fault injection & recovery |
| Phase 9 | Validation & closure |

Detailed definitions for each phase are documented in `docs/`.

---

## Definition of “Complete”

The project is considered **complete only when**:

- all nodes operate concurrently
- events are time-synchronized
- logs are persistent and replayable
- partial failures are detected and handled
- analytics and redundancy paths function correctly
- full documentation exists explaining design decisions and failures

There is **no partial completion** and no “future work” placeholders.

---

## Repository Structure

```text
multi-sensor-system/
├── arduino-node-env/
├── arduino-node-event/
├── pico-arbiter/
├── pi-brain/
├── odroid-analytics/
├── odroid-redundancy/
├── docs/
│   ├── architecture.md
│   ├── communication.md
│   ├── failure-modes.md
│   └── design-rationale.md
└── README.md
```
---

## Why This Project Exists

This project exists to build real systems intuition:

- how embedded systems behave under load
- how failures propagate
- how timing and communication interact
- how design tradeoffs matter more than language choice

---

## Status

🚧 In Progress


