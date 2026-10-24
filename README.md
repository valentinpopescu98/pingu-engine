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

**Supported target:** x86_64 (64-bit) Windows and Linux; 32-bit x86 is not supported.

The engine uses C++17 and OpenGL 3.3 Core. GLAD, GLM, Dear ImGui, pugixml and stb are vendored as source/header dependencies. GLFW, Assimp and Lua use **vcpkg-managed dependencies on Windows** (including runtime `.dll` files); Linux uses vendored `.so` files under `deps/linux/x86_64/lib/`. The obsolete committed Windows DLLs and import libraries have been removed (issue #10). The application uses the same libraries conceptually on both systems; their binary formats and transitive dependencies differ.

OpenGL implementation, Mesa/GPU drivers and system runtime libraries are **not** bundled. A working graphical environment and an OpenGL 3.3-capable driver are required to run the editor.

### Ubuntu 22.04 / Linux x86_64

```bash
git clone https://github.com/valentinpopescu98/pingu-engine.git
cd pingu-engine
sudo apt-get update
sudo apt-get install -y build-essential cmake clang-14 libgl1-mesa-dev patchelf
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang-14 -DCMAKE_CXX_COMPILER=clang++-14
cmake --build build --parallel 2
./build/bin/pingu-engine
```

The build copies bundled Linux shared libraries to `build/bin/lib/` and configures ELF RUNPATH via `patchelf` to locate direct and transitive dependencies without `LD_LIBRARY_PATH`. For normal GUI operation, run from `build/bin` (or ensure resources are accessible relative to the current working directory).

### Windows x86_64

Install CMake, Ninja, Visual Studio C++ build tools, Clang/LLVM (`clang-cl`), and vcpkg. The root `vcpkg.json` declares the Windows-only dependencies (GLFW, Assimp, Lua) and fixes the registry baseline. For reproducibility, use the **same vcpkg tool commit** as CI: `0c2a9ace1964b818b15f7ae50ba1c42404918a7b`. Set `VCPKG_ROOT` to your vcpkg checkout, then run from a Visual Studio developer shell.

```powershell
git clone https://github.com/valentinpopescu98/pingu-engine.git
cd pingu-engine
git -C "$env:VCPKG_ROOT" fetch origin 0c2a9ace1964b818b15f7ae50ba1c42404918a7b
git -C "$env:VCPKG_ROOT" checkout --detach 0c2a9ace1964b818b15f7ae50ba1c42404918a7b
& "$env:VCPKG_ROOT/bootstrap-vcpkg.bat" -disableMetrics
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build --parallel 2
.\build\bin\pingu-engine.exe
```

CMake manifest-mode configuration installs packages in the project-local `build/vcpkg_installed/` directory (ignored by Git); a separate `vcpkg install` command is not required. The manifest and pinned registry select the dependency graph; the pinned vcpkg tool commit ensures CI and local builds use the same port definitions. Exact binary hashes can still differ with compiler/SDK/toolchain updates.

Run the configure/build commands from a developer shell with the Visual Studio linker and Windows SDK available. The required DLLs and runtime resources are copied beside the executable. For Visual Studio or other multi-config generators, the output location can vary.

### CI and portability

GitHub Actions builds Windows 2022 and Ubuntu 22.04 in Debug and Release, then runs the **same Ubuntu 22.04 Release executable** on Ubuntu 24.04, Fedora 44 and a dated Arch Linux container. Windows Server 2025 separately checks that the Windows Server 2022 Release artifact's bundled DLLs load. Smoke tests create a GLFW window and OpenGL context using Xvfb and Mesa software rendering; they do **not** render a full scene or validate every engine subsystem.

Linux bundled binaries were matched by SHA-256 to Ubuntu 22.04 packages (`libglfw3`, `libassimp5`, `liblua5.4-0`, `libdraco4`, `libminizip1`) during the initial audit. The build packages Ubuntu copyright files and provenance records; Windows binaries come from pinned vcpkg ports, with installed-package inventories and per-port copyright notices. The obsolete committed Windows DLLs were removed.

### Third-party licenses and provenance

Pingu Engine is MIT-licensed; bundled dependencies retain their own license terms. Windows builds use pinned vcpkg packages and collect installed-package copyright notices, package inventories and DLL hashes. Linux builds bundle the corresponding Ubuntu 22.04 package copyright notices and shared-library hashes. See [third-party license inventory](third_party/licenses/README.md) for the verified package provenance and redistribution notices.

**Future x86 (32-bit) builds:** Not implemented. The intended future interface is x86_64 by default and explicit x86 selection only once matching 32-bit Windows/Linux dependencies and CI tests exist. A CMake flag alone cannot make the current 64-bit binaries compatible with x86.

**Portability scope:** x86_64 only. Fedora and Arch images are pinned to a release/snapshot tag, but package-manager updates may still change installed dependencies. The smoke tests demonstrate initialization, not a guarantee of compatibility with every distribution or GPU.

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
