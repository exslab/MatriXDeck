# MatriXDeck Case Design

This directory contains the 3D design files for the MatriXDeck enclosure.

## Files

- `matrixdeck_case_top.stl` - Top case 3D printable file
- `matrixdeck_case_bottom.stl` - Bottom case 3D printable file
- `matrixdeck_case.step` - Complete case assembly in STEP format
- `matrixdeck_case.f3d` - Fusion 360 source file

## Design Specifications

The MatriXDeck case is designed with the following features:

1. **Dimensions:** 120mm x 70mm x 18mm
2. **Ergonomic Design:** Inspired by the Steam Deck handheld gaming device
3. **Material:** Designed for 3D printing in PLA or PETG
4. **Button Access:** Cutouts for all buttons, joystick, and display
5. **Durability:** 2mm wall thickness for robustness
6. **Assembly:** Snap-fit design with optional screw reinforcement
7. **Cable Access:** Cutout for USB-C charging port
8. **Expandability:** Optional mounting points for accessories

## Printing Guidelines

### Recommended Print Settings

- **Layer Height:** 0.2mm for standard quality, 0.12mm for higher quality
- **Infill:** 20-30% (grid or honeycomb pattern)
- **Supports:** Required for button cutouts and some overhangs
- **Material:** PLA or PETG
- **Nozzle Size:** 0.4mm standard
- **Print Temperature:** Material dependent (typically 200-220°C for PLA, 230-250°C for PETG)
- **Bed Temperature:** Material dependent (typically 60°C for PLA, 80°C for PETG)

### Post-Processing

- Remove all support material carefully, especially around button holes
- Test-fit buttons and joystick in their cutouts, and sand if necessary
- Optional: Light sanding of external surfaces for smoother feel
- Optional: Painting or finishing for customized appearance

## Assembly Instructions

1. Install PCB into bottom case, securing with 4 self-tapping screws (M2 x 8mm)
2. Connect battery if not pre-installed on PCB
3. Test-fit buttons and joystick through top case cutouts
4. Carefully align top and bottom cases, then snap together
5. If needed, secure with 4 additional screws on side mounting points

## Customization

The case design is provided in editable formats to allow for customization:

- Add personalized text or logos to the case exterior
- Modify button layouts if creating custom hardware configurations
- Create add-on mounting accessories for the expansion points
- Adjust internal mounting points for hardware revisions

## Balance Robot Add-on Case

For the Balance Robot Kit, additional 3D files are provided:
- `matrixdeck_robot_chassis.stl` - Main chassis body
- `matrixdeck_robot_wheel_left.stl` - Left wheel design
- `matrixdeck_robot_wheel_right.stl` - Right wheel design 