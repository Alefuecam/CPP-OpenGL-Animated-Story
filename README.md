# C++ OpenGL — Animated Short Story

A scripted 2D animation developed in **C++ using OpenGL**, created as an academic computer graphics project.

The project uses geometric shapes to tell a short story through programmed movement, transformations, and scene transitions.

## Animation Demo

**[Watch the animation](demo/VideoProyecto1.mp4)**

The demonstration shows the original project's execution.

## Story

The animation follows a small circular character attempting to overcome a large obstacle.

1. The character enters the scene and approaches the obstacle.
2. It leaves to retrieve a stick and positions it as a climbing aid.
3. After several unsuccessful attempts, the character climbs successfully.
4. It moves across the obstacle and jumps toward a platform occupied by another circle.
5. The platform breaks, causing the characters to fall.

The entire sequence is scripted programmatically rather than animated using external video-editing software.

## Technologies

- **C++** — Application logic, geometry generation, and animation sequencing.
- **OpenGL 3.3** — Graphics rendering.
- **GLFW** — Window creation, graphics context, and event handling.
- **GLAD** — OpenGL function loading.
- **GLM** — Matrix transformations and vector mathematics.
- **GLSL** — GPU shader programming.
- **STL vectors** — Storage of generated geometric vertex data.

## Implementation

### Procedural Geometry

Custom functions generate circles and rectangles from mathematical parameters.

Circular geometry is calculated using trigonometric functions:

```cpp
x = radius * cos(glm::radians(angle));
y = radius * sin(glm::radians(angle));
```

The generated coordinates are assembled into triangles for rendering.

### Geometric Transformations

The animation uses transformation matrices to move, rotate, and scale objects.

GLM functions such as `glm::translate`, `glm::rotate`, and `glm::scale` control the positions and orientations of characters and scene elements.

Transformation matrices are passed to the graphics pipeline through shader uniforms.

### Time-Controlled Animation

The storyline is divided into sequential stages controlled by a timeline variable.

Conditional statements activate different behaviors, including character movement, object rotation, climbing attempts, jumping, and falling.

The rendering loop includes an elapsed-time check to regulate animation updates.

### OpenGL Rendering

The application uses vertex array objects (VAOs), vertex buffer objects (VBOs), shaders, and drawing commands to render the scene.

Objects are represented using geometric primitives, with vertex attributes defining their positions and colors.

## Project Structure

- `main.cpp` — Original C++ animation implementation.
- `demo/VideoProyecto1.mp4` — Video demonstration.
- `shaders/` — External shader files, if recovered.

## Running the Project

The original application was developed with OpenGL 3.3 and uses GLFW, GLAD, GLM, and an external shader helper.

The source references `shader_s.h`, `5.1.transform.vs`, and `5.1.transform.fs`. These dependencies must be available and configured to compile and run the original project.

A standalone build configuration is not currently provided. The demonstration video is included so the animation can be viewed without compiling the source.

## Skills Demonstrated

- C++ programming
- Graphics programming and the OpenGL rendering pipeline
- Trigonometry and procedural geometry
- Vector and matrix transformations
- Time-controlled animation and scene sequencing
- State management and conditional logic
- GPU buffers and shader integration

## Academic Context

This project was developed for a university computer graphics course. It demonstrates practical experience using C++ and graphics programming techniques to create a complete visual narrative.
