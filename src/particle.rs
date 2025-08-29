use bevy::prelude::*;

pub const WINDOW_WIDTH: f32 = 640.0;
pub const WINDOW_HEIGHT: f32 = 480.0;

#[derive(Component)]
pub struct Particle {
    pub initial_x: f32,
    pub initial_y: f32,
    pub offset_x: f32,
    pub offset_y: f32,
    pub direction: f32,
    pub offset_direction: f32,
    pub size: f32,
    pub strength: bool,
    pub collision_enabled: bool,
}

#[derive(Component)]
pub struct PlayerParticle;

#[derive(Component)]
pub struct TestParticle;

#[derive(Component)]
pub struct AutonomousParticle;

pub fn move_particle(particle: &mut Particle, transform: &mut Transform, steps: f32) {
    let total_direction = particle.direction + particle.offset_direction;
    let radians = total_direction.to_radians();
    
    // Move based on direction - much faster movement
    let speed = 50.0; // Increased base movement speed
    let dx = radians.cos() * speed / steps;
    let dy = -radians.sin() * speed / steps; // Negative Y to match original coordinate system
    
    transform.translation.x += dx;
    transform.translation.y += dy;
    
    // Update rotation for non-player particles (player rotation is handled separately)
    // For other particles, we still need to update rotation during movement
    let visual_radians = (total_direction - 90.0).to_radians();
    transform.rotation = Quat::from_rotation_z(-visual_radians);
}

pub fn handle_boundary_collision(particle: &mut Particle, transform: &mut Transform) {
    let pos = transform.translation;
    let half_size = particle.size / 2.0;
    
    // Convert to screen coordinates (Bevy uses center origin, original used top-left)
    let screen_x = pos.x + WINDOW_WIDTH / 2.0;
    let screen_y = -pos.y + WINDOW_HEIGHT / 2.0;
    
    // Check boundaries and handle collisions
    if screen_x - half_size < 0.0 || screen_x + half_size > WINDOW_WIDTH ||
       screen_y - half_size < 0.0 || screen_y + half_size > WINDOW_HEIGHT {
        
        if particle.strength {
            // Bounce logic - proper reflection
            if screen_x - half_size < 0.0 || screen_x + half_size > WINDOW_WIDTH {
                particle.direction = 180.0 - particle.direction;
                // Keep particle in bounds
                if screen_x - half_size < 0.0 {
                    transform.translation.x = -WINDOW_WIDTH / 2.0 + half_size;
                } else {
                    transform.translation.x = WINDOW_WIDTH / 2.0 - half_size;
                }
            }
            if screen_y - half_size < 0.0 || screen_y + half_size > WINDOW_HEIGHT {
                particle.direction = 360.0 - particle.direction;
                // Keep particle in bounds
                if screen_y - half_size < 0.0 {
                    transform.translation.y = WINDOW_HEIGHT / 2.0 - half_size;
                } else {
                    transform.translation.y = -WINDOW_HEIGHT / 2.0 + half_size;
                }
            }
            
            // Normalize direction
            while particle.direction < 0.0 {
                particle.direction += 360.0;
            }
            while particle.direction >= 360.0 {
                particle.direction -= 360.0;
            }
        } else {
            // Reset to initial position (convert back to Bevy coordinates)
            transform.translation.x = particle.initial_x - WINDOW_WIDTH / 2.0;
            transform.translation.y = -(particle.initial_y - WINDOW_HEIGHT / 2.0);
            particle.offset_x = 0.0;
            particle.offset_y = 0.0;
            particle.offset_direction = 0.0;
        }
    }
}
