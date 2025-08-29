# Particle Engine

A particle system engine built with Bevy that demonstrates various particle behaviors including player-controlled particles, autonomous particles, and collision detection.

## Features

- **Player Particle**: A controllable triangular particle
- **Test Particles**: Two particles that move automatically and can collide with each other
- **Autonomous Particles**: 360 particles arranged in a circle with color-shifting effects
- **Boundary Collision**: Particles can either bounce off boundaries or reset to initial position
- **Visual Boundaries**: White border showing the collision detection area
- **Keyboard Controls**: Full keyboard interaction for controlling particles

## Controls

### Player Particle
- `W` - Move forward (triangle shows direction)
- `A` - Rotate counter-clockwise
- `D` - Rotate clockwise
- `Q` - Increase size
- `E` - Decrease size
- `R` - Reset position and rotation
- `S` - Print particle info to console

### Autonomous Particles
- `M` - Set particles to "strength" mode (red color, bounce off boundaries)
- `N` - Set particles to normal mode (blue color, reset on boundary hit)
- `J` - Rotate all particles left
- `L` - Rotate all particles right
- `I` - Hold to stop particle movement
- `R` - Reset all particles

### General
- `Escape` - Exit application

## Running

```bash
cargo run
```

## Technical Details

The engine uses Bevy's Entity Component System (ECS) architecture with a modular design:

### Project Structure
- `src/main.rs` - Main application entry point and setup function
- `src/particle.rs` - Particle components, constants, and utility functions
- `src/systems.rs` - All game systems (input handling, movement, collision detection)

### Systems
- Input handling
- Player movement (with triangular mesh for directional indication)
- Test particle updates
- Autonomous particle updates
- Collision detection
- Visual boundary rendering
