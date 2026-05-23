# pingu-engine

A real-time 3D graphics engine built from scratch in C++ and OpenGL 3.3 Core, developed over 3 months as a course project during the Computer Graphics, Multimedia and VR master's program at University Politehnica of Bucharest. The engine implements a complete rendering pipeline with its own scene format, scripting system, physics, and editor GUI — no game engine frameworks involved.

---

## Features

### Rendering
- **OpenGL 3.3 Core** rendering pipeline via GLFW3 and GLAD
- **Custom mesh format** — interleaved VBO layout (position + UV + normals + color, 11 floats/vertex) with EBO index buffering
- **Phong illumination model** — ambient, diffuse, and specular components computed per-fragment in GLSL
- **Multi-format texture support** — JPG and PNG via `stb_image`, with configurable wrap modes and mipmap generation
- **3D model import** — OBJ/MTL via Assimp, with full mesh hierarchy and diffuse texture binding

### Scene Management
- **XML scene format** — custom schema with per-object transform (position, rotation, scale), color, texture path, and model path
- **Hierarchical object graph** — parent-child transform inheritance for both `Mesh` and `Model` instances, parsed recursively from XML
- **Frustum culling** — Radar Approach implementation: bounding sphere computed per object (longest axis as radius), tested against camera frustum planes using dot product projections for Z, tangent-derived height for Y, and aspect-ratio-scaled width for X
- **Backface culling** — CCW winding order with `GL_CULL_FACE` enabled

### Particle System
- Configurable birth/death color (interpolated over lifetime), birth/death scale, starting position, speed, and lifetime
- Per-particle VBO creation in the main loop with overloaded `CreateBuffers()` and `Draw()` to avoid model matrix conflicts
- Back-to-front draw order to minimize alpha blending artifacts
- Controlled via Dear ImGui panel at runtime

### Physics
- **AABB collision detection** — bounding sphere intersection test (reuses frustum culling radius logic)
- **Collision resolution** — automatic de-penetration pushes intersecting objects outside each other's bounding volumes

### Scripting
- **Lua 5.4.4** scripting via `ScriptingSystem::CallFunctionByName()`
- Engine calls `Init()` and `Update()` Lua functions automatically each frame if defined
- Decoupled from C++ — scene logic can be written entirely in Lua scripts

### Editor GUI
- **Dear ImGui** integrated as a Singleton `GuiDrawer` with `Init()`, `Draw()`, `End()` lifecycle
- Particle System Manager panel — live control of all particle parameters

### Camera
- FPS-style camera with WASD + mouse look
- Configurable FOV, near/far clip planes, movement speed, and mouse sensitivity
- Vertical rotation clamped to [5°, 175°] to prevent gimbal flip
- Right-click to capture mouse; Shift for sprint speed

---

## Architecture

```
Engine          — GLFW window lifecycle, main loop (Init / Run / End)
World           — scene root, owns all objects, runs Lua Init() and Update()
XMLParser       — loads scene from XML, builds object hierarchy
Shader          — compiles and links GLSL vertex + fragment shaders
VAO / VBO / EBO — GPU buffer wrappers
Mesh            — geometry with transform, material, and texture
Model           — Assimp-loaded multi-mesh hierarchy
Texture         — stb_image loader with wrap/mipmap config
Camera          — FPS camera, view/projection matrix, frustum internals
FrustumCulling  — MeshInFrustum() / ModelInFrustum() using Radar Approach
CollisionSystem — bounding sphere intersection + de-penetration
ParticleSystem  — per-particle VBO, lifetime interpolation, back-to-front draw
GuiDrawer       — Dear ImGui Singleton, Particle System Manager panel
ScriptingSystem — Lua 5.4.4 bridge, CallFunctionByName()
```

Main loop per frame:
```
BeforeDrawing   — clear color + depth buffers
  Update()      — frustum cull, collision detect, particle update, Lua Update()
  Draw()        — XML scene draw (lights first, then objects), particles, GUI
AfterDrawing    — swap buffers, poll GLFW events
```

---

## Build

**Dependencies** (all linked statically or via headers):
- OpenGL 3.3+
- [GLFW3](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)
- [Assimp](https://github.com/assimp/assimp)
- [stb_image](https://github.com/nothings/stb)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [pugixml](https://pugixml.org/)
- [Lua 5.4.4](https://www.lua.org/)

**Build (CMake):**
```bash
git clone https://github.com/valentinpopescu98/pingu-engine
cd pingu-engine
mkdir build && cd build
cmake ..
cmake --build .
```

---

## Scene Format

Scenes are described in XML. Example:

```xml
<scene>
  <object type="light" model="assets/cube.obj" texture="assets/white.png"
          pos="2 4 -3" rot="0 0 0" scale="0.2 0.2 0.2" color="1 1 1"/>

  <object type="model" model="assets/backpack.obj" texture=""
          pos="0 0 -5" rot="0 45 0" scale="1 1 1" color="1 1 1">
    <children>
      <object type="model" model="assets/tag.obj" texture=""
              pos="0 1 0" rot="0 0 0" scale="0.5 0.5 0.5" color="0.8 0.8 0.8"/>
    </children>
  </object>
</scene>
```

Child transforms are relative to their parent. The engine resolves the full world transform recursively at load time.

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Graphics API | OpenGL 3.3 Core |
| Windowing | GLFW3 |
| GL Loader | GLAD |
| Math | GLM |
| Model Import | Assimp (OBJ/MTL) |
| Textures | stb_image |
| GUI | Dear ImGui |
| XML | pugixml |
| Scripting | Lua 5.4.4 |

---

## Academic Context

Course project — Computer Graphics, Multimedia and VR M.Sc. program, Faculty of Automatic Control and Computers, University Politehnica of Bucharest (2020–2022). Built in 3 months.

The companion project [deepfake-animator](https://github.com/valentinpopescu98/deepfake-animator) — a deepfake-driven educational animation generator built on First Order Model — was the M.Sc. dissertation project from the same program (grade 10/10).
