# LogicSim

Nanotekspice is a **C++ digital circuit simulator** that emulates logic gates and integrated circuits.
It reads a circuit description file (`.nts`), builds the corresponding component graph, and simulates the circuit tick by tick.

The goal of the project is to reproduce the behavior of simple **logic gates**, **chips**, and **sequential components** while allowing interactive simulation through a command-line interface.

---

# Features

* Logic gate simulation
* Integrated circuit emulation
* Tick-based simulation engine
* Interactive command interface
* Support for clocks and sequential components
* Continuous simulation mode

---

# Build

Example using `make`:

```bash
make re
```

This produces the executable:

```
./nanotekspice
```

---

# Usage

```bash
./nanotekspice <circuit.nts>
```

Example:

```bash
./nanotekspice or_gate.nts
```

---

# Circuit File Format (`.nts`)

A circuit file contains two sections:

```
.chipsets:
    component_type name
    component_type name

.links:
    component:pin component:pin
```

### Example

```
.chipsets:
input   a
input   b
4071    or
output  s

.links:
a:1     or:1
b:1     or:2
or:3    s:1
```

This describes:

```
a ----\
       OR ---- s
b ----/
```

---

# Simulation Commands

Once the program is running, you can control the simulation using these commands:

| Command       | Description                                                    |
| ------------- | -------------------------------------------------------------- |
| `exit`        | Exit the program                                               |
| `display`     | Print the current tick and the value of all inputs and outputs |
| `simulate`    | Simulate one tick of the circuit                               |
| `input=value` | Change the value of an input or clock (`0`, `1`, or `U`)       |
| `loop`        | Continuously simulate and display until `CTRL+C`               |

---

# Example Session

```
~/B-OOP-400> ./nanotekspice or_gate.nts
> b=0
> a=1
> simulate
> display
tick: 1
input(s):
  a: 1
  b: 0
output(s):
  s: 1
> exit
```

---

# Clock Example

```
.chipsets:
clock   cl
output  out

.links:
out:1   cl:1
```

Simulation:

```
> display
tick: 0
input(s):
  cl: U
output(s):
  out: U

> cl=0
> simulate
> display
tick: 1
input(s):
  cl: 0
output(s):
  out: 0
```

The display command shows the **state at the end of the last simulation tick**.

---

# Implemented Components

## Input / Output

| Component | Description                          |
| --------- | ------------------------------------ |
| `input`   | User-controlled input                |
| `output`  | Circuit output (seen in display)     |
| `true`    | Constant logic `1`                   |
| `false`   | Constant logic `0`                   |
| `clock`   | Clock signal that toggles every tick |


---

## Elementary Gates

| Component | Description             |
| --------- | ----------------------- |
| `and`     | Single AND gate         |
| `or`      | Single OR gate          |
| `xor`     | Single XOR gate         |
| `not`     | Single inverter         |
| `logger`  | Debug logging component |

---

## Logic Gate ICs

| Chip   | Description        |
| ------ | ------------------ |
| `4001` | Four NOR gates     |
| `4011` | Four NAND gates    |
| `4030` | Four XOR gates     |
| `4069` | Six inverter gates |
| `4071` | Four OR gates      |
| `4081` | Four AND gates     |

---

## Advanced Components

| Chip       | Description                  |
| ---------- | ---------------------------- |
| `4008`     | 4-bit full adder             |
| `4512`     | 8-channel data selector      |
| `4013`     | Dual D-type flip-flop        |
| `4040`     | 12-bit binary counter        |
| `2716`     | rom 2058 bytes               |
| `flipflop` | Internal flip-flop component |

---

# Signal Values

Signals in the simulator use **three-state logic**:

| Value | Meaning   |
| ----- | --------- |
| `0`   | False     |
| `1`   | True      |
| `U`   | Undefined |

---

# Program Behavior

* The `display` command shows the **snapshot of the circuit after the last tick**.
* Clocks toggle their value at every simulation tick.

---

# Exit Codes

| Code | Meaning                                   |
| ---- | ----------------------------------------- |
| `0`  | Successful execution                      |
| `84` | Error (invalid file, parsing issue, etc.) |

---

You can see the gate documentation in the directory called documentation in the root.

There are also many preconfigured nts files to play around with in the Tests directory.

