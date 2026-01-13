# Phase 3 — Multi MCU Coexistence

Two Arduino Uno boards operate simultaneously.

Communication:
- SoftwareSerial on D8/D9
- Hardware USB Serial reserved for debugging

Properties:
- Bidirectional framed communication
- No echo or self-reception
- Reset-safe
- One node failure does not freeze the other

Conclusion:
Phase 3 coexistence verified successfully.
