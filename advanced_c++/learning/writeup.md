# Advanced C++ Writeup

## Inheritance

**(e)** It can't, because `x` and `y` are private in `Location`.

**(f)** When `x` and `y` are protected in `Location`, `Building` can access them directly in its own methods.

**(g)** A client function (e.g. `main`) can't access `x` or `y` through a `Building` object — they are protected.

**(i)** When `Building` protectedly inherits from `Location`, a client function can't access `Location`'s public getters/setters through a `Building` object, and can't convert `Building*` to `Location*`.

**(j)** `OfficeBuilding` can still access `Location`'s public functions because protected inheritance makes them protected in `Building`, and `OfficeBuilding` inherits from `Building`.

**(k)** With private inheritance, `OfficeBuilding` can't access `Location`'s functions — they become private to `Building`.

**(m)** Calling `print` on a `Building` calls `Building::print`, which prints the location, area, and number of floors.

**(n)** With public inheritance and a non-virtual `print`, calling `print` on a `Location*` that points to a `Building` calls `Location::print` — it only prints the location fields. The output confirmed this: the pointer called the base class version.

**(o)** After making `print` virtual, calling `print` on a `Location*` pointing to a `Building` calls `Building::print` (dynamic dispatch). The test output shows both `b.print()` and `loc->print()` produce `Building(1, 2, My Building, 1000, 5)`.

## STL and Smart Pointers

### (b) Array of 16 Tracers

Each Tracer is default-constructed exactly once. IDs 0–15, one construction per element. No copies.

### (c) STL vector of 16 Tracers

`std::vector<Tracer> v(16)` default-constructs 16 elements in-place. Each constructed exactly once, IDs 16–31. No copies — vector allocates space up front.

### (d) STL set of 16 Tracers

Each `tracers_set.insert(Tracer())` creates a temporary Tracer, then the set copies it in. The copy gets the next ID from `head`. The temporary is then destroyed, decrementing `head`. Because of the decrement, every subsequent temporary gets the same ID as the one already in the set, so every insert after the first is rejected. The set ends up with **only 1 Tracer** instead of 16 — this demonstrates the ID-uniqueness problem with the decrement approach.

### (e) STL sort on the vector

No construction or copy output. The vector elements (IDs 16–31) were already in ascending order, so `std::sort` required no swaps and `operator=` was never called.

### (f) STL set_union on two sets

Building `tracers_set2`: same pattern as (d) — only 1 Tracer ends up in the set. `set_union` then copies elements from both sets into `tracers_union`, calling the copy constructor for each unique element merged.

### (g) STL set of 16 unique_ptrs to Tracers

Each Tracer is constructed exactly once (IDs 35–50), no copies. The `unique_ptr` is moved into the set — the Tracer itself is never copied. The set orders by pointer address (not Tracer ID), so ordering is arbitrary.

### (h) STL set of 16 shared_ptrs to Tracers

Same as (g) — each Tracer constructed exactly once (IDs 51–66), no copies. `shared_ptr` is copyable but the Tracer underneath is not duplicated. Destruction order follows the set's internal tree structure, so IDs are destroyed non-sequentially.

### (i) Why not weak_ptrs?

`std::weak_ptr` doesn't keep the object alive and can't be dereferenced without first locking it into a `shared_ptr`. A set needs to compare its elements, which would require dereferencing — but that's unsafe with a weak_ptr since the object may have already been destroyed.

## Templates

**`duplicate<T>`** allocates a copy of any object on the heap using its copy constructor and returns a raw pointer. Works for any type with a copy constructor.

**Tests:**
- `duplicate<std::string>("hello")` → returns a new `std::string*` equal to `"hello"` ✓
- `duplicate<int>(42)` → returns a new `int*` equal to `42` ✓

**`CountedCopies<T>`** wraps an object and tracks an abstract copy count. `copy()` decrements the count and returns a heap-allocated duplicate; returns `nullptr` when count reaches 0.

**Tests:**
- `CountedCopies<std::string> cc("hello")`: `add_copy_count(3)` → count = 3 ✓
- `remove_copy_count(1)` → count = 2 ✓
- `cc.copy()` → returns `"hello"`, count decremented to 1 ✓
