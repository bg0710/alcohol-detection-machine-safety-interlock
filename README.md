# Alcohol Detection & Machine Safety Interlock

An 8051-based embedded safety-interlock system that detects alcohol using an MQ-3 sensor and controls a motor-driven machine accordingly. The system provides visual and audible status indication through an LM016L LCD and buzzer.

## Overview

The project uses an **AT89C51 (8051-family) microcontroller** as the central controller.

The controller continuously reads the digital output of an **MQ-3 alcohol sensor**:

- **Sensor logic 0:** motor is commanded to run, buzzer is OFF, and the LCD displays `Alcohol Free`.
- **Sensor logic 1:** motor is commanded to stop through an **L293D motor driver**, buzzer is ON, and the LCD displays `Alcohol Detected`.

The implementation demonstrates sensor interfacing, GPIO programming, LCD interfacing, motor-driver control and embedded C programming.

## System Architecture

```text
MQ-3 Alcohol Sensor
        │
        ▼
   AT89C51 / 8051
     │    │    │
     │    │    └──────► Buzzer
     │    │
     │    └───────────► LM016L LCD
     │
     └───────────────► L293D ───► Motor / Machine
```

See [`docs/system-flowchart.png`](docs/system-flowchart.png) for the complete control flow and [`hardware/circuit-schematic.png`](hardware/circuit-schematic.png) for the circuit.

## Hardware

| Component | Role |
|---|---|
| AT89C51 | Main microcontroller |
| MQ-3 | Alcohol sensing |
| L293D | Motor-driver interface |
| LM016L LCD | System-status display |
| Buzzer | Audible alert |
| DC motor / machine load | Controlled actuator |

## Microcontroller I/O Mapping

| Pin / Port | Function |
|---|---|
| P2.0 | MQ-3 sensor input |
| P0.0 | Buzzer output |
| P3.0 | L293D motor-driver input A |
| P3.1 | L293D motor-driver input B |
| P1 | LCD data bus |
| P2.5 | LCD RS |
| P2.6 | LCD RW |
| P2.7 | LCD Enable |

## Software

The firmware is written in **Embedded C** using the 8051 `reg51.h` definitions.

Main software functions:

- `cmd()` – sends commands to the LCD
- `ldata()` – sends character/data bytes to the LCD
- `String()` – displays text on the LCD
- `motorRun()` – commands the motor driver to run
- `motorStop()` – commands the motor driver to stop
- `main()` – continuously reads the sensor and controls the outputs

## Repository Structure

```text
alcohol-detection-machine-safety-interlock/
├── README.md
├── src/
│   └── alcohol_detection.c
├── hardware/
│   └── circuit-schematic.png
└── docs/
    ├── system-flowchart.png
    └── project-documentation.pdf
```

## Project Documentation

A detailed technical report is available here:

**[Project Documentation](docs/project-documentation.pdf)**

It contains the system architecture, circuit, I/O mapping, software implementation, working principle, functional behaviour and engineering considerations.

## Functional Behaviour

| MQ-3 Input | Motor | Buzzer | LCD |
|---|---|---|---|
| Logic 0 | Run | OFF | Alcohol Free |
| Logic 1 | Stop | ON | Alcohol Detected |

The supplied firmware explicitly interprets logic 1 as the alcohol-detected state. The actual output polarity of a particular MQ-3 module/comparator arrangement should be verified against the physical module before deployment.

## Engineering Considerations

The supplied project is a prototype demonstrating the control concept. The provided files do not contain quantitative sensor calibration data, measured response time, alcohol-concentration thresholds or accuracy measurements.

For a real industrial safety application, additional validation, fail-safe mechanisms, appropriate electrical isolation and properly rated safety hardware would be required.

## Author

**Bhargab Gogoi**  
B.Tech – Electrical Engineering  
Jorhat Engineering College
