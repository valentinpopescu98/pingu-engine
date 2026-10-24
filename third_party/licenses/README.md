# Third-party binary redistribution notices

Pingu Engine is MIT-licensed (see `LICENSE.md`). This does **not** replace
the licenses of bundled third-party libraries.

## Bundled Windows and Linux binaries

| Component | Bundled paths | License / notes |
| --- | --- | --- |
| GLFW | Windows: vcpkg `glfw3`; Linux: `deps/linux/x86_64/lib/libglfw.so.3` | zlib/libpng-style; upstream notice copied in `GLFW-LICENSE.txt` |
| Assimp | Windows: vcpkg `assimp`; Linux: `deps/linux/x86_64/lib/libassimp.so.5` | BSD-3-Clause; includes additional third-party acknowledgements; see `ASSIMP-LICENSE.txt` |
| Lua | Windows: vcpkg `lua`; Linux: `deps/linux/x86_64/lib/liblua5.4.so.0` | MIT; see `LUA-LICENSE.txt` |
| Draco | `deps/linux/x86_64/lib/libdraco.so.4` | Apache-2.0; see `DRACO-LICENSE.txt`; verify whether upstream NOTICE applies to packaged binary |
| Minizip | `deps/linux/x86_64/lib/libminizip.so.1` | Ubuntu 22.04 `libminizip1` is from source package `minizip` 1.1-8build1; see `MINIZIP-LICENSE.txt` (upstream information) and check Debian/Ubuntu packaged copyright for exact terms |

## Source/header dependencies

GLAD, GLM, Dear ImGui, pugixml and stb are vendored as source/header files under
`deps/`. Their upstream license texts have been preserved here as
`GLAD-LICENSE.txt`, `GLM-LICENSE.txt`, `IMGUI-LICENSE.txt`,
`PUGIXML-LICENSE.txt`, and `STB-LICENSE.txt`. The checked-in versions were identified from source headers on 2026-10-24:

| Dependency | Checked-in version / evidence |
| --- | --- |
| GLAD | Generator 0.1.34, generated 2021-11-12 for OpenGL 3.3 core (`deps/include/glad/glad.h`) |
| GLM | 0.9.9.9 (`deps/include/glm/detail/setup.hpp`) |
| Dear ImGui | 1.86 (`deps/include/imgui/imgui.h`) |
| pugixml | 1.11 (`deps/include/pugixml/pugixml.hpp`) |
| stb_image | 2.27 (`deps/include/stb/stb_image.h`) |

These versions are identified. The Dear ImGui 1.86 and pugixml 1.11 license files
have been replaced with their exact upstream tagged license texts (2014-2021 and
2006-2020 copyright ranges, respectively). The remaining vendored license files
still require snapshot-by-snapshot verification before the audit is final.

## Windows vcpkg migration and license inventory (2026-10-24)

Windows Debug and Release builds, and Windows Server 2025 DLL-load smoke test,
passed in [GitHub Actions run #64](https://github.com/valentinpopescu98/pingu-engine/actions/runs/40127444242).
The legacy Windows DLLs and import libraries have been removed from the repository;
current Windows build artifacts use vcpkg dependencies.

The runner installs GLFW, Assimp and Lua via vcpkg. At the time of run #60,
the selected versions were GLFW 3.5.1, Assimp 6.0.5 and Lua 5.5.1.
The registry baseline and vcpkg tool checkout are now pinned to
`0c2a9ace1964b818b15f7ae50ba1c42404918a7b` using `vcpkg.json` and CI.
The latest pinned-manifest run [#40133549602](https://github.com/valentinpopescu98/pingu-engine/actions/runs/40133549602)
passed all eight jobs. Package versions and exact artifact contents should still
be checked independently for each release.
The exact package set for each new Windows artifact is recorded in
`licenses/VCPKG-INSTALLED-PACKAGES.txt`, and the checkout revision in
`licenses/BINARY-PROVENANCE.txt`.

The CI workflow collects the actual `share/<port>/copyright` file for
each installed vcpkg package, including transitive dependencies, into
`licenses/vcpkg-packages/`. The collection job passed in run #66; inspect a published artifact independently
before final release. The project-level
license texts under `third_party/licenses/` are also packaged.

## Outstanding checks before public release

1. The vcpkg notice-collection workflow passed in run #66 and pinned-manifest run #40133549602; inspect a fresh
   release artifact to independently verify the complete notice inventory.
2. [Done] Pin the vcpkg registry baseline and tool revision for reproducible Windows dependency resolution.
3. [Partially done] ImGui 1.86 and pugixml 1.11 notices now match upstream
   release tags. Verify GLAD 0.1.34, GLM 0.9.9.9 and stb_image 2.27.
4. Review additional attribution/NOTICE requirements (including Draco and
   transitive dependencies) and verify every release artifact includes `licenses/`.

This is an engineering compliance inventory, not legal certification.

## Verified CI artifact audit (2026-10-24)

GitHub Actions run [#54](https://github.com/valentinpopescu98/pingu-engine/actions/runs/40121301707), Ubuntu 22.04 Release artifact `pingu-engine-ubuntu-22.04-Release`:

| Library | Ubuntu 22.04 package | Binary comparison |
| --- | --- | --- |
| Lua | `liblua5.4-0` `5.4.4-1` | SHA-256 match |
| Assimp | `libassimp5` `5.2.2~ds0-1` | SHA-256 match |
| Minizip | `libminizip1` `1.1-8build1` | SHA-256 match |
| GLFW | `libglfw3` `3.3.6-1` | SHA-256 match |
| Draco | `libdraco4` `1.5.2+dfsg-2` | SHA-256 match |

The exact Debian/Ubuntu copyright notices are bundled under `licenses/ubuntu-packages/`. `libminizip1-copyright` explicitly identifies the zlib license and copyright holders. All four build artifacts include a `licenses/` directory.

The original run #54 Windows artifact contained legacy DLLs of unresolved origin. New Windows artifacts use vcpkg-built DLLs instead; see the migration section above.

This audit establishes Linux package provenance and notice inclusion, not legal certification or exhaustive review of every transitive/static component.

## Follow-up audit — 2026-10-25 (PR #9 branch)

**Status: open / partially verified.** The latest checked run, [#40140129145](https://github.com/valentinpopescu98/pingu-engine/actions/runs/40140129145), at commit `785ac1ce7da7f0842bdffef854085b916baf9731`, completed successfully: all four Windows/Linux Debug/Release build jobs and all four compatibility-smoke jobs passed. GitHub's artifacts API reports four non-expired archives:

| Artifact | Artifact ID | Archive size (bytes) |
| --- | ---: | ---: |
| `pingu-engine-ubuntu-22.04-Release` | 12578436417 | 6880702 |
| `pingu-engine-ubuntu-22.04-Debug` | 12578391516 | 7755280 |
| `pingu-engine-windows-2022-Release` | 12578211970 | 5612199 |
| `pingu-engine-windows-2022-Debug` | 12578416522 | 9277377 |

**Important limitation:** GitHub's available repository connector lists these artifacts but cannot download/decode their binary ZIP payloads. Therefore the exact `licenses/` contents of these four archives **have not been independently inspected** in this follow-up. CI success confirms packaging steps executed, not an independent archive-by-archive audit. This remains a release blocker for declaring the audit complete.

### Vendored source/header notices

- **GLAD:** `deps/include/glad/glad.h` identifies generator **0.1.34**. The upstream [`Dav1dde/glad` `v0.1.34` LICENSE](https://github.com/Dav1dde/glad/blob/v0.1.34/LICENSE) contains MIT terms plus Khronos Apache-2.0 and EGL/header attribution. Our `GLAD-LICENSE.txt` includes those sections, **but differs from the upstream tag in the David Herberth copyright end year (local: 2022; upstream tag: 2020)**. Restore the exact upstream-tagged notice or document a source-backed reason for the difference. Do not reduce the license to MIT only.
- **GLM:** `deps/include/glm/detail/setup.hpp` identifies **0.9.9.9**; local `GLM-LICENSE.txt` includes both MIT and Happy Bunny alternatives. An exact upstream 0.9.9.9 tag/license comparison was **not completed** (the queried `0.9.9.9` ref was unavailable); snapshot-specific match remains open.
- **stb_image:** `deps/include/stb/stb_image.h` identifies **2.27**, and local `STB-LICENSE.txt` contains the MIT/public-domain alternatives. Upstream current `master` is **2.30**, so comparing against current master would not prove an exact 2.27 snapshot match. A matching historical revision and the vendored header's end-of-file notice still require comparison.

### Draco and transitive obligations

- `DRACO-LICENSE.txt` includes Apache-2.0, whose section 4(d) requires preserving relevant attribution from an upstream NOTICE file **if one exists**. The queried upstream `google/draco` `1.5.2` root `NOTICE` path returned 404; that is **not proof** no NOTICE or third-party notices exist in the distribution or Ubuntu source package. Verify the actual Ubuntu `libdraco4` source/package copyright and any embedded third-party notices before release.
- The workflow collects Ubuntu package copyrights and all installed Windows vcpkg port copyright notices, but a legal/attribution review of **every transitive and statically linked component** remains open. In particular, the locally bundled Minizip upstream summary does not replace the verified Ubuntu `libminizip1` package copyright notice.

### Remaining release gate

1. Obtain and inspect the four ZIP artifacts above; enumerate `licenses/` and compare against bundled ELF/DLLs, `VCPKG-INSTALLED-PACKAGES.txt`, `BINARY-PROVENANCE.txt`, Ubuntu package copyright files, and all vcpkg transitive port notices.
2. Correct GLAD's copyright-year discrepancy using the exact tagged upstream notice; verify exact GLM 0.9.9.9 and stb_image 2.27 license snapshots.
3. Resolve Draco/NOTICE and transitive-component obligations using the shipped Ubuntu and vcpkg package inventories.
4. Record inspection evidence and only then mark [issue #21](https://github.com/valentinpopescu98/pingu-engine/issues/21) complete.

### Source snapshot verification — 2026-10-25

- **GLAD:** replaced `GLAD-LICENSE.txt` with the exact upstream `Dav1dde/glad` `v0.1.34` `LICENSE` text, correcting the David Herberth copyright range from 2013–2022 to 2013–2020. The Khronos notices are preserved. Source: https://github.com/Dav1dde/glad/blob/v0.1.34/LICENSE
- **stb_image:** the entire checked-in `deps/include/stb/stb_image.h` matches upstream `nothings/stb` commit `5ba0baaa269b3fd681828e0e3b3ac0f1472eaf40` (2021-07-26), including its end-of-file MIT/public-domain alternatives. The local `STB-LICENSE.txt` reproduces that notice. Source: https://github.com/nothings/stb/blob/5ba0baaa269b3fd681828e0e3b3ac0f1472eaf40/stb_image.h
- **GLM:** `GLM-LICENSE.txt` matches byte-for-byte the upstream `g-truc/glm` `0.9.9.8` `copying.txt` (MIT / Happy Bunny alternatives). The vendored headers report `0.9.9.9`, for which a matching tagged release was not identified; this verifies the license wording against the preceding official release, **not** exact provenance of the vendored `0.9.9.9` header snapshot. Source: https://github.com/g-truc/glm/blob/0.9.9.8/copying.txt

**Still open:** GLM header snapshot provenance, Draco/NOTICE and transitive obligations, and independent inspection of all four generated artifact ZIPs. Earlier open-check descriptions above are historical and superseded where this subsection documents completed verification.

### Draco Ubuntu package cross-check — 2026-10-25

Ubuntu Jammy identifies `libdraco4` version `1.5.2+dfsg-2` as a binary of source package `draco` version `1.5.2+dfsg-2` (https://packages.ubuntu.com/jammy/libs/libdraco4 and https://packages.ubuntu.com/source/jammy/misc/draco). Its runtime package dependencies are glibc, libgcc and libstdc++; these are system-provided, not bundled by Pingu Engine. The source package also lists build dependencies such as Eigen, stb, tinygltf, nlohmann-json and googletest; being a build dependency alone does **not** establish that its code is linked into the shipped `libdraco.so.4`.

The CI bundles `licenses/ubuntu-packages/libdraco4-copyright` from the Ubuntu binary package and the project `DRACO-LICENSE.txt`. **NOTICE review is not yet closed:** upstream Apache-2.0 section 4(d) is conditional on the upstream distribution containing relevant NOTICE attribution. The package-specific copyright text and source distribution's relevant third-party notices must be inspected before asserting whether additional attribution is required. An unsuccessful attempt to retrieve the Debian source packaging archive in the audit environment is not evidence of absence. Keep this as an explicit release gate.
