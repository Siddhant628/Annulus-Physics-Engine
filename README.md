# Annulus-Physics-Engine

Annulus is an **impluse based 2D physics engine** I worked on as a personal project over a semester at UCF. (It uses impulse based collision resolution)

## Features:
- Implemented support for particle physics (**Newton-Euler integration** method, with damping).

- Implemented architeture to support **force generators** which would produce forces in particles on each update call based on specific logic.

- Implemented custom force generators for **spring forces, gravity and bungee** and visualized them.

- Implemented particle contact resolution and **contact generators** to simulate non-spring based forces. Implemented custom contact generators to simulate **rod and cable** like forces between particles.

- Implemented **rigid body integrator** with logic to handle both translation and rotation due to external forces and torque.

- Implemented **force generators for rigid bodies** and custom force generators for **anchored spring and gravitational forces**.

- Implemented architecture to support rigid body collision detection/resolution (the contact information can be used by integrator to resolve collisions).

- Implemented **collision detection and resolution for circles**.

## Demos:

A rigid body under the infulence of gravity and an anchored spring:

<img src = "https://www.gamedevgrover.com/assets/img/posts/annulus-week-7-8/anchored-spring-demo.gif" width = "400" height = "400" />


Collision detection and resolution for two circles:

<img src = "https://www.gamedevgrover.com/assets/img/posts/annulus-week-7-8/circle-collision-demo.gif" width = "400" />
