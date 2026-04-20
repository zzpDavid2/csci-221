# C++ Intro Assignment — Writeup

---

## Q1: Hello World

Both parts are working.

**Tests:**

| Test | Expected output | Result |
|------|----------------|--------|
| Run program | `Hello, World!` | PASS |

---

## Q2: Pointers

All five parts are working. 

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| 2(a): `ptr == nullptr` check | prints "ptr is null" | PASS |
| 2(b): `*ptr` after `new uint32_t(42)` | prints `42` | PASS |
| 2(c): `delete ptr` | no crash | PASS |
| 2(d): `new uint32_t[17]` | no crash | PASS |
| 2(e): `delete[] ptr` | no crash | PASS |

---

## Q3: Functions

All three parts are working. 

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| 3(a): `add_to_int(&x=5, 3)` | `x = 8` | PASS |
| 3(b): `add_to_int(y=5, 3)` | `y = 8` | PASS |
| 3(c): `add_to_int(z=5)` (default arg) | `z = 6` | PASS |

---

## Q4: Namespaces

### Part (b)

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| 4(b): `ring_band()` | `1` | PASS |

### Part (a)

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| `Update(5, 3)` (first larger) | `5.0` | PASS |
| `Update(3, 5)` (average case) | `4.0` | PASS |

---

## Q5: Strings and IO

**Tests (manual input = `"41"`):**

| Test | Expected | Result |
|------|----------|--------|
| 5(a): direct `cin >> value` | prints `42` | PASS |
| 5(b): `stoi` conversion | prints `42` | PASS |
| 5(c): `stringstream` conversion | prints `42` | PASS |

---

## Q6: Objects

**Tests:**

| Test | Expected | Result |
|------|----------|--------|
| `count_characters("test string", cc("abcrst "))` | `0 0 0 1 2 3 1` | PASS |
| Default constructor compiles and runs | no crash | PASS |
| Copy constructor compiles and runs | no crash | PASS |
