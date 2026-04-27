# C++ Intro Evaluation — Writeup

---

## Q1: Cars

### Part (a): Car class

The `Car` class stores a `Location`, `mpg`, `fuel_capacity`, and `fuel_level`. It has a default constructor (all zeros), a parameterized constructor (starts full), and a copy constructor. `move_to` computes the straight-line distance, checks if there is enough fuel, and either deducts fuel and updates position (returning `true`) or leaves the car unchanged (returning `false`).

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| Default constructor: location, mpg, capacity, level | all `0` | PASS |
| Parameterized constructor `({1,2}, 30, 15)`: starts full | `fuel_level == 15` | PASS |
| Copy constructor: mpg and fuel_level copied | `30`, `10` | PASS |
| `move_to({3,4})` from origin, 30 mpg, 10 gal | returns `true`, fuel decreases by `5/30` | PASS |
| `move_to({100,0})` from origin, 30 mpg, 0.1 gal | returns `false`, stays at `{0,0}` | PASS |

### Part (b): move_cars (no gas stations)

Iterates over a copy of each car, calls `move_to`, and only includes cars that successfully reach the destination.

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| 2 cars with full fuel to `{3,4}` | output size `2` | PASS |
| 1 car with fuel, 1 with no fuel | output size `1` | PASS |

### Part (c): GasStation class

`GasStation` stores a `Location` and `dollars_per_gallon` with a parameterized constructor and copy constructor.

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| Constructor `({5,5}, 3.50)`: location and price | `x=5`, `y=5`, `dpg=3.50` | PASS |

### Part (d): move_cars (with gas stations)

Cars that cannot reach the destination directly try each gas station in order. If the car can reach a station, it drives there, fully refuels (recording the cost), then attempts the destination. Cars that still cannot reach are excluded.

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| Car (10 mpg, 5 gal = 50 mi), station at mile 40, dest at mile 90 | reaches via station, output size `1`, cost > `0` | PASS |

---

## Q2: SortedList

The `SortedList` class maintains a singly-linked list of strings in sorted order. It supports two sort modes (`LEXICOGRAPHIC` and `LENGTH`) controlled by a `SortOrder` enum. The copy constructor rebuilds the list via `get_strings()` + `insert()` to ensure a proper deep copy. The destructor calls `clear()` which walks the list and deletes each node, preventing memory leaks.

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| (a) Default constructor | `size == 0`, `is_sorted_lexicographically()` | PASS |
| (b) Copy constructor: insert apple+banana, copy | `size == 2`, order apple/banana | PASS |
| (c) Sort order constructor with `LENGTH` | `is_sorted_by_length()` | PASS |
| (d) Lexicographic insert: cherry/apple/banana | apple/banana/cherry | PASS |
| (d) Length insert: banana(6)/hi(2)/apple(5) | hi/apple/banana | PASS |
| (e) Remove middle: remove banana from apple/banana/cherry | apple/cherry, `size == 2` | PASS |
| (e) Remove head: remove apple from apple/banana | banana, `size == 1` | PASS |
| (e) Remove nonexistent: remove cherry from {apple} | `size == 1` | PASS |
| (f) Clear: apple/banana then clear | `size == 0` | PASS |
| (g) `is_sorted_by_length()` on LENGTH list | `true` | PASS |
| (h) `is_sorted_lexicographically()` on LEXICOGRAPHIC list | `true` | PASS |
| (i) Size increments on insert | `0` → `1` → `2` | PASS |
| (j) `get_strings()`: insert banana+apple | `[apple, banana]` | PASS |
| (k) `get_string(i)`: insert banana+apple | `[0]=apple`, `[1]=banana` | PASS |
| (k) `get_string(5)` on 1-element list | throws `out_of_range` | PASS |
| (l) `sort_by_length()`: banana/hi/apple (lexico order) | hi/apple/banana | PASS |
| (m) `sort_lexicographically()`: banana/hi/apple (length order) | apple/banana/hi | PASS |

---

## Known Issues

None. All tests pass.
