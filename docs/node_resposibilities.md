# Node Responsibilities

## Arduino Uno #1 (Environmental Node)
- Periodic sensor sampling
- Stable timing
- Heartbeat generation
- UART data streaming to Pico

## Arduino Uno #2 (Event Node)
- Interrupt-driven sensing
- Debounced event handling
- Priority tagging
- UART event streaming to Pico

## Pico 2W (Arbiter)
- Timestamp assignment
- Heartbeat monitoring
- Event ordering
- Unified stream output

## Raspberry Pi 5
- Data ingestion
- Persistent logging
- System health monitoring
- Minimal web dashboard

## Odroids
- Analytics
- Redundancy
- Replay verification
