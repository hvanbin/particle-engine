use bevy::prelude::*;

mod particle;
mod systems;

use particle::*;
use systems::*;

fn main() {
    App::new()
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Particle Engine".into(),
                resolution: (WINDOW_WIDTH, WINDOW_HEIGHT).into(),
                ..default()
            }),
            ..default()
        }))
        .add_systems(Startup, setup)
        .add_systems(Update, (
            handle_input,
            update_player_movement,
            update_test_particles,
            update_autonomous_particles,
            handle_collisions,
        ))
        .run();
}

fn setup(mut commands: Commands, mut meshes: ResMut<Assets<Mesh>>, mut materials: ResMut<Assets<ColorMaterial>>) {
    commands.spawn(Camera2dBundle::default());

    // Create border outline
    let border_thickness = 2.0;
    
    // Top border
    commands.spawn(SpriteBundle {
        sprite: Sprite {
            color: Color::WHITE,
            custom_size: Some(Vec2::new(WINDOW_WIDTH, border_thickness)),
            ..default()
        },
        transform: Transform::from_xyz(0.0, WINDOW_HEIGHT / 2.0 - border_thickness / 2.0, 1.0),
        ..default()
    });
    
    // Bottom border
    commands.spawn(SpriteBundle {
        sprite: Sprite {
            color: Color::WHITE,
            custom_size: Some(Vec2::new(WINDOW_WIDTH, border_thickness)),
            ..default()
        },
        transform: Transform::from_xyz(0.0, -WINDOW_HEIGHT / 2.0 + border_thickness / 2.0, 1.0),
        ..default()
    });
    
    // Left border
    commands.spawn(SpriteBundle {
        sprite: Sprite {
            color: Color::WHITE,
            custom_size: Some(Vec2::new(border_thickness, WINDOW_HEIGHT)),
            ..default()
        },
        transform: Transform::from_xyz(-WINDOW_WIDTH / 2.0 + border_thickness / 2.0, 0.0, 1.0),
        ..default()
    });
    
    // Right border
    commands.spawn(SpriteBundle {
        sprite: Sprite {
            color: Color::WHITE,
            custom_size: Some(Vec2::new(border_thickness, WINDOW_HEIGHT)),
            ..default()
        },
        transform: Transform::from_xyz(WINDOW_WIDTH / 2.0 - border_thickness / 2.0, 0.0, 1.0),
        ..default()
    });

    // Player particle - using acute triangle mesh to show direction
    let triangle_mesh = Mesh::from(Triangle2d::new(
        Vec2::new(0.0, 12.0),  // Long pointed vertex (forward direction)
        Vec2::new(-4.0, -6.0), // Bottom left (narrower base)
        Vec2::new(4.0, -6.0),  // Bottom right (narrower base)
    ));
    
    commands.spawn((
        ColorMesh2dBundle {
            mesh: meshes.add(triangle_mesh).into(),
            material: materials.add(ColorMaterial::from(Color::srgb(0.2, 0.7, 0.9))),
            transform: Transform::from_xyz(100.0 - WINDOW_WIDTH / 2.0, -(100.0 - WINDOW_HEIGHT / 2.0), 0.0),
            ..default()
        },
        Particle {
            initial_x: 100.0,
            initial_y: 100.0,
            offset_x: 0.0,
            offset_y: 0.0,
            direction: 0.0,
            offset_direction: 0.0,
            size: 10.0,
            strength: true,
            collision_enabled: true,
        },
        PlayerParticle,
    ));

    // Test particles (convert to Bevy coordinates)
    for (_i, (x, dir)) in [(50.0, 90.0), (600.0, 270.0)].iter().enumerate() {
        commands.spawn((
            SpriteBundle {
                sprite: Sprite {
                    color: Color::BLACK,
                    custom_size: Some(Vec2::new(10.0, 10.0)),
                    ..default()
                },
                transform: Transform::from_xyz(*x - WINDOW_WIDTH / 2.0, -(300.0 - WINDOW_HEIGHT / 2.0), 0.0),
                ..default()
            },
            Particle {
                initial_x: *x,
                initial_y: 300.0,
                offset_x: 0.0,
                offset_y: 0.0,
                direction: *dir,
                offset_direction: 0.0,
                size: 10.0,
                strength: true,
                collision_enabled: true,
            },
            TestParticle,
        ));
    }

    // Autonomous particles (360 particles in a circle, convert to Bevy coordinates)
    for angle in 0..360 {
        commands.spawn((
            SpriteBundle {
                sprite: Sprite {
                    color: Color::srgb(0.0, 0.0, 1.0),
                    custom_size: Some(Vec2::new(3.0, 3.0)),
                    ..default()
                },
                transform: Transform::from_xyz(0.0, 0.0, 0.0), // Center of screen in Bevy coordinates
                ..default()
            },
            Particle {
                initial_x: WINDOW_WIDTH / 2.0,
                initial_y: WINDOW_HEIGHT / 2.0,
                offset_x: 0.0,
                offset_y: 0.0,
                direction: angle as f32,
                offset_direction: 0.0,
                size: 3.0,
                strength: false,
                collision_enabled: true, // Enable collisions for autonomous particles
            },
            AutonomousParticle,
        ));
    }
}
