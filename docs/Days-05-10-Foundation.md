## Day 5: Minimal GameObject Spec

`GameObject` is the engine's basic authored object unit.

It is the thing the editor will eventually:

- create
- delete
- rename
- select
- activate and deactivate
- save and load

It is also the runtime-side anchor for future component data.

Right now, `GameObject` only needs:

- `id`
- `name`
- `active`

Rules:

- `id` must stay stable inside the loaded scene document
- `name` is for humans and editor display, not identity
- `active` is the first coarse enable or disable switch shared by runtime and editor
- `GameObject` is not allowed to turn into a dumping ground just because components do not exist yet

Not in scope yet:

- transform hierarchy
- component storage
- render state
- physics state
- audio state
- AI state
- gameplay logic
- prefab system

Rule for adding fields later:

- If almost every object needs it because it is part of object identity or editor ownership, it might belong on `GameObject`
- If it belongs to a subsystem, it should probably become a component later

## Day 6: Engine Direction

The build order is:

1. application shell
2. renderer
3. editor shell
4. object and component authoring
5. scene serialization
6. asset pipeline
7. gameplay-specific authoring

The architecture direction is:

- `GameObject` is the stable authored object shell
- components hold subsystem-specific data
- systems operate on component data
- the editor manipulates `GameObject` and components directly
- runtime behavior should move toward ECS-style processing without requiring a giant gameplay inheritance tree

What that means:

- gameplay object subclasses should not become the main architecture
- rooms and triggers should not be defined before the editor and component model exist
- gameplay assumptions should not leak into the engine core too early

Near-term object model stance:

- keep `GameObject` small
- let future components attach by `GameObject::Id`
- prefer plain data first, richer behavior later

## Day 7: Project Conventions

### Folder Ownership

- `runtime/`
  Engine runtime code that both the game side and editor side will rely on
- `editor/`
  Editor application and tool-facing code
- `common/`
  Shared code only if it is actually shared for real, not as a utility bucket
- `docs/`
  Design notes, scope notes, conventions, and planning documents

### Naming

- Use `PascalCase` for types
- Use clear noun names for data types
- Use verb names for actions and functions
- Avoid vague names like `Manager`, `SystemBase`, `Helper2`, or anything else that says nothing

### Source Layout

- Keep headers and source files paired when a type has real implementation
- Prefer one main type per file right now
- Keep runtime core files in `runtime/core/`
- Keep debug-only helper code out of core bootstrap when possible

### Design Discipline

- Do not invent abstraction layers without pressure
- Do not add fields to `GameObject` just to dodge making a proper component later
- Do not let temporary editor hacks become permanent architecture
- Favor readable C++ over clever C++

### Build Discipline

- Keep the CMake setup explicit and easy to audit
- Prefer source lists that are easy to read quickly
- Only add third-party dependencies when the next implementation step actually needs them

## Day 8: Not Phase 1 Work

These are out of scope until the engine shell, renderer, and editor shell are in place:

- scripting
- networking
- prefab workflows
- advanced serialization frameworks
- hot reload systems
- gameplay-specific object inheritance trees
- rooms as a finalized gameplay container concept
- trigger authoring
- inventory systems
- save-game state systems
- enemy AI behavior trees
- console-port-specific runtime work
- D3D12 migration

Also out of scope:

- rewriting stable systems just because a fancier architecture exists in theory
- introducing ECS infrastructure before the editor and object model actually need it

## Day 9: Minimum Editor Goals

The first editor shell only needs to prove that authored objects can exist, be viewed, and be manipulated.

The minimum editor feature set is:

- dockspace
- menu bar
- hierarchy or outliner panel
- inspector panel
- viewport panel
- object selection
- object creation
- object deletion
- object rename
- active-state toggle

The editor does not need yet:

- polished UX
- full asset browser
- prefab tooling
- trigger authoring
- room authoring semantics
- advanced undo and redo
- custom gizmo framework beyond what existing middleware already solves

Editor success condition:

- a `GameObject` can be created, selected, inspected, renamed, and eventually persisted through save and load

## Day 10: Frozen First 30-Day Scope

### Absolute Priority Order

1. Win32 window and application loop
2. renderer bootstrap
3. editor shell
4. `GameObject` and first component path
5. scene save and load
6. asset import

Anything below that line waits.

### Days 11-30 Execution Target

Days 11-15:

- Win32 window
- message pump
- loop integration
- resize and activation handling
- input foundation

Days 16-20:

- stabilize the runtime shell
- lock in `GameObject` identity handling
- define the first object collection ownership model

Days 21-30:

- D3D11 renderer bootstrap
- clear screen and viewport path
- prepare for the first editor integration

### Definition Of Done For The Next Coding Stretch

Before moving into gameplay-specific data, the project should have:

- a native window
- a real application loop
- working input plumbing
- a minimal renderer path
- the first editor shell plan held steady

### Tomorrow's Goal

Tomorrow starts Win32 window work.

Today is done if:

- the object model is minimally defined
- scope is frozen
- there is no more time wasted inventing rooms, triggers, or gameplay containers before the engine shell exists
