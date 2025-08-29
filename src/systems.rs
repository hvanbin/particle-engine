use bevy::prelude::*;
use crate::particle::*;

pub fn handle_input(
    keyboard_input: Res<ButtonInput<KeyCode>>,
    mut player_query: Query<&mut Particle, With<PlayerParticle>>,
    mut autonomous_query: Query<(&mut Particle, &mut Sprite), (With<AutonomousParticle>, Without<PlayerParticle>)>,
    mut exit: EventWriter<AppExit>,
) {
    if keyboard_input.pressed(KeyCode::Escape) {
        exit.send(AppExit::Success);
    }

    if let Ok(mut player) = player_query.get_single_mut() {
        if keyboard_input.pressed(KeyCode::KeyQ) {
            player.size += 1.0;
        }
        if keyboard_input.pressed(KeyCode::KeyE) {
            player.size -= 1.0;
            if player.size < 1.0 {
                player.size = 1.0;
            }
        }
        if keyboard_input.pressed(KeyCode::KeyX) {
            // Color shift functionality would be handled in update_colors_by_rotation
        }
        if keyboard_input.pressed(KeyCode::KeyW) {
            // Move forward
        }
        if keyboard_input.pressed(KeyCode::KeyA) {
            player.direction += 9.0; // Counter-clockwise (A key)
            if player.direction >= 360.0 {
                player.direction -= 360.0;
            }
        }
        if keyboard_input.pressed(KeyCode::KeyD) {
            player.direction -= 9.0; // Clockwise (D key)
            if player.direction < 0.0 {
                player.direction += 360.0;
            }
        }
        if keyboard_input.pressed(KeyCode::KeyR) {
            player.offset_x = 0.0;
            player.offset_y = 0.0;
            player.offset_direction = 0.0;
            player.direction = 0.0;
        }
        if keyboard_input.pressed(KeyCode::KeyS) {
            println!("Player - rotation: {}, size: {}", player.direction, player.size);
        }
    }

    // Handle autonomous particle controls
    for (mut particle, mut sprite) in autonomous_query.iter_mut() {
        if keyboard_input.pressed(KeyCode::KeyM) {
            particle.strength = true;
            sprite.color = Color::srgb(1.0, 0.0, 0.0);
        }
        if keyboard_input.pressed(KeyCode::KeyN) {
            particle.strength = false;
            sprite.color = Color::srgb(0.0, 0.0, 1.0);
        }
        if keyboard_input.pressed(KeyCode::KeyR) {
            particle.offset_x = 0.0;
            particle.offset_y = 0.0;
            particle.offset_direction = 0.0;
        }
        if keyboard_input.pressed(KeyCode::KeyJ) {
            particle.direction -= 0.3;
            if particle.direction < 0.0 {
                particle.direction += 360.0;
            }
        }
        if keyboard_input.pressed(KeyCode::KeyL) {
            particle.direction += 0.3;
            if particle.direction >= 360.0 {
                particle.direction -= 360.0;
            }
        }
    }
}

pub fn update_player_movement(
    mut query: Query<(&mut Particle, &mut Transform), With<PlayerParticle>>,
    keyboard_input: Res<ButtonInput<KeyCode>>,
) {
    for (mut particle, mut transform) in query.iter_mut() {
        // Move forward when W is pressed - much more responsive
        if keyboard_input.pressed(KeyCode::KeyW) {
            move_particle(&mut particle, &mut transform, 4.0);
        }

        // Update visual rotation immediately when A/D keys are pressed
        // Convert from degrees to radians and adjust for Bevy's coordinate system
        let total_direction = particle.direction + particle.offset_direction;
        // In Bevy, positive Z rotation is counter-clockwise, and we need to offset by 90 degrees
        // because our triangle points up (positive Y) but we want 0 degrees to point right (positive X)
        let radians = (total_direction - 90.0).to_radians();
        transform.rotation = Quat::from_rotation_z(-radians); // Negative to match our coordinate system

        // Reset player position when R is pressed
        if keyboard_input.pressed(KeyCode::KeyR) {
            transform.translation.x = particle.initial_x - WINDOW_WIDTH / 2.0;
            transform.translation.y = -(particle.initial_y - WINDOW_HEIGHT / 2.0);
            transform.rotation = Quat::from_rotation_z(0.0);
        }

        // Handle boundary collisions
        handle_boundary_collision(&mut particle, &mut transform);
    }
}

pub fn update_test_particles(
    mut query: Query<(&mut Particle, &mut Transform, &mut Sprite), With<TestParticle>>,
) {
    for (mut particle, mut transform, mut sprite) in query.iter_mut() {
        // Update size
        sprite.custom_size = Some(Vec2::new(particle.size, particle.size));

        // Test particles always move - faster movement
        move_particle(&mut particle, &mut transform, 30.0);

        // Handle boundary collisions
        handle_boundary_collision(&mut particle, &mut transform);
    }
}

pub fn update_autonomous_particles(
    mut query: Query<(&mut Particle, &mut Transform, &mut Sprite), With<AutonomousParticle>>,
    keyboard_input: Res<ButtonInput<KeyCode>>,
) {
    for (mut particle, mut transform, mut sprite) in query.iter_mut() {
        // Update size
        sprite.custom_size = Some(Vec2::new(particle.size, particle.size));

        // Move unless I key is pressed - much faster movement
        if !keyboard_input.pressed(KeyCode::KeyI) {
            move_particle(&mut particle, &mut transform, 30.0);
        }

        // Apply color shifting effect
        let current_color = sprite.color.to_srgba();
        let new_r = (current_color.red + 1.0/255.0).min(1.0);
        let new_g = (current_color.green + 2.0/255.0).min(1.0);
        let new_b = (current_color.blue + 3.0/255.0).min(1.0);
        sprite.color = Color::srgba(new_r, new_g, new_b, current_color.alpha);

        // Handle boundary collisions
        handle_boundary_collision(&mut particle, &mut transform);
    }
}

pub fn handle_collisions(
    mut all_particles: Query<(Entity, &mut Particle, &Transform)>,
) {
    let mut combinations = all_particles.iter_combinations_mut();
    while let Some([(_entity_a, mut particle_a, transform_a), (_entity_b, mut particle_b, transform_b)]) = combinations.fetch_next() {
        if particle_a.collision_enabled && particle_b.collision_enabled {
            let distance = transform_a.translation.distance(transform_b.translation);
            let collision_distance = (particle_a.size + particle_b.size) / 2.0;
            
            if distance < collision_distance {
                // Reset both particles on collision
                particle_a.offset_x = 0.0;
                particle_a.offset_y = 0.0;
                particle_a.offset_direction = 0.0;
                
                particle_b.offset_x = 0.0;
                particle_b.offset_y = 0.0;
                particle_b.offset_direction = 0.0;
            }
        }
    }
}
