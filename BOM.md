# Bill of Materials (BOM)

## Electronics Components

| Qty | Component | Description | Specifications | Link |
|-----|-----------|-------------|----------------|------|
| 4 | Linear Vibration Motor | 0619AAC Brushless X-axis vibration motor | 1.2V, 100mA max, precision linear pulse | [AliExpress](https://www.aliexpress.com/item/1005006421331249.html) |
| 1 | Microcontroller | Pro Micro ATmega32U4 USB Type-C | 5V, 16MHz, 2-row header | [AliExpress](https://www.aliexpress.com/item/1576902211.html) |
| 4 | MOSFET Transistor | IRLZ44N TO-220 | Logic-level N-channel MOSFET for motor control | [AliExpress](https://www.aliexpress.com/item/1005007084688391.html) |
| 1 | Battery Holder | 18650 single slot battery case | 3.7V battery storage (3-pack) | [AliExpress](https://www.aliexpress.com/item/1005006283625827.html) |

## Additional Components (Not Listed)

The following components are assumed to be needed based on the circuit design:

| Qty | Component | Description | Specifications |
|-----|-----------|-------------|----------------|
| 4 | Resistor | Gate resistor for MOSFETs | 220Ω - 1kΩ |
| 4 | Diode | Flyback diode for motors | 1N4001 or equivalent |
| 1 | Battery | Rechargeable lithium-ion | 18650, 3.7V |
| 1 | Breadboard/PCB | For prototyping or final assembly | - |
| - | Wire | Hookup wire | 22-24 AWG solid/stranded |
| - | USB Cable | USB Type-C cable | For programming and power |

## Circuit Design Notes

### Motor Driver Circuit (per motor)

Each vibration motor requires:
- 1x IRLZ44N MOSFET (logic-level compatible with 5V Arduino pins)
- 1x Gate resistor (220Ω - 1kΩ) between Arduino pin and MOSFET gate
- 1x Flyback diode (1N4001) across motor terminals (cathode to +)

### Power Considerations

- **Arduino**: Powered via USB (5V) or battery with voltage regulator
- **Motors**: 1.2V nominal, 100mA each = 400mA total max
- **Battery**: 18650 cell (3.7V nominal, typically 2000-3500mAh)
  - Requires voltage regulation to 1.2V for motors
  - Consider using a buck converter or PWM from 5V rail with appropriate duty cycle

### Wiring

- Motor PWM pins: 3, 5, 6, 9 (Arduino Pro Micro)
- Common ground between Arduino, motors, and battery
- MOSFETs switch the negative (ground) side of motors

## Assembly Notes

1. Upload firmware to Pro Micro before final assembly
2. Test each motor individually before connecting all four
3. Ensure proper heatsinking for MOSFETs if driving motors continuously
4. Use appropriate wire gauge for motor current (22-24 AWG sufficient)
5. Include physical mounting for motors to maximize haptic feedback transfer

## Cost Estimate

Based on AliExpress listings (approximate):
- Motors: ~€15 (4x ~€3.75 each)
- Microcontroller: ~€3.63
- MOSFETs: Price varies (typically <€1 each)
- Battery holders: ~€1.30 (per 3-pack)

**Total estimated cost**: ~€25-30 USD for main components (excluding shipping, resistors, diodes, wire, etc.)
