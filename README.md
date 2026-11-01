# Linux Input Event Reader (Basic Keylogger)

This repository contains a low-level C utility that demonstrates how to interact directly with the Linux kernel's event delivery subsystem (`evdev`). It captures and parses raw hardware input events from a specified device node, acting as a rudimentary keylogger for educational system programming purposes.

## Overview

The program reads byte streams from a Linux input device file (typically located in `/dev/input/`) and maps the raw binary data into structured `input_event` formats. It filters the event stream to isolate key press actions and translates a specific subset of hardware keycodes into human-readable terminal output. 

## Architecture & Logic

The utility relies on standard POSIX system calls and Linux-specific headers:
1. **Device Access:** Uses `open()` to read a device node passed as a command-line argument.
2. **Event Polling:** Enters an infinite `while(1)` loop, utilizing the `read()` system call to populate a `struct input_event` (defined in `<linux/input.h>`).
3. **Event Filtering:** 
   * Checks `ie.type == EV_KEY` to ignore mouse movements, synchronization events, or other hardware signals.
   * Checks `ie.value == 1` to isolate the exact moment a key is depressed (ignoring key releases or long-press repeats).
4. **Keycode Translation:** Maps Linux hardware keycodes 2 through 10 directly to the numeric characters '1' through '9', printing them to `stdout`.

## Limitations

* **Restricted Scope:** The current keycode translation logic is hardcoded strictly for the number row (1-9). It does not map alphabetical characters, special symbols, or handle shift-state modifiers.
* **Privilege Requirements:** Because it reads directly from `/dev/input/` hardware nodes, the compiled executable requires root (`sudo`) privileges to run.
* **Foreground Execution:** The process runs in the foreground and outputs directly to standard out; it lacks daemonization or stealth mechanics.

## Usage

1. **Compile:** Compile the code using GCC:
   ```bash
   gcc keylogger.c -o keylogger
2. **Run:** Locate your keyboard's event file (e.g., event3) by inspecting /proc/bus/input/devices.
   ```bash
   sudo ./keylogger /dev/input/event3
   
