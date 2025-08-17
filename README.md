# Embassy Consulate Line System 🏛️

A compact, console-based C++ queue management simulator for an embassy/consulate visa processing workflow.  
Implements per-visa queues, four service counters with primary assignments, dynamic allocation to longest queues, daily limits, and a clear end-of-day report.

Badges:  
![C++](/) Language: C++ · Status: Completed · License: MIT

---

## Table of contents

- [Quick summary](#quick-summary)
- [Features](#features)
- [Design & data structures](#design--data-structures)
- [Build & run (Windows)](#build--run-windows)
- [Example session](#example-session)
- [Testing ideas](#testing-ideas)
- [Contributing & license](#contributing--license)

---

## Quick summary

- Four visa categories: TR (Tourist), MED (Medical), BS (Business), GO (Government Officials).
- Four counters, each primarily serving one visa type. If a counter's primary queue is empty it serves the longest non-empty queue.
- Limits: max 25 applicants per visa type, max 100 applicants daily.
- Outputs a daily summary showing served counts by visa type, per-counter served tokens, idle counters, and totals.

---

## Features

- Deterministic token generation with type prefix (e.g., `TR-1`, `MED-2`).
- Per-visa FIFO queues.
- Counters record each served token for reporting.
- Input validation and limit checks.
- Readable end-of-day summary.

---

## Design & data structures

- Token: struct containing visa type and global sequential number.
- Per-visa queue: FIFO (std::queue recommended).
- Counter: primary visa type and a vector/log of served tokens.
- Simple global counters for issued/served statistics.

---

## Build & run (Windows)

Open PowerShell or Command Prompt in the project folder.

PowerShell / CMD:

```powershell
g++ 23-54707-3.cpp -std=c++17 -O2 -o embassy_system.exe
.\embassy_system.exe
```

WSL / Linux:

```bash
g++ 23-54707-3.cpp -std=c++17 -O2 -o embassy_system
./embassy_system
```

Notes:

- Use -std=c++17 (or newer) for container and string conveniences.
- If you prefer MSVC (Visual Studio), create a console project and add the source file.

---

## Example session

1. Start program.
2. Select "Request Token" → choose visa type (1–4) → program prints token (e.g., `TR-1`).
3. Select "Call Next Customer" → enter counter number (1–4) → counter serves its primary queue or the longest available queue.
4. At end of day, select "Generate Daily Summary Report" to review served applicants.

Sample output (excerpt):

```
Your token: TR-12
Counter 1 please serve token TR-5
===== Daily Summary Report =====
TR (Tourist): 12
MED (Medical): 7
BS (Business): 9
GO (Government Officials): 6
Counter 1 (TR): TR-1, TR-5, TR-9
Counter 2 (MED): MED-2, MED-7
...
Total Applicants Served: 34
```

---

## Testing ideas

- Enqueue 25 tokens for one visa type and confirm the 26th is rejected.
- Issue >100 tokens across types to trigger the global limit.
- Simulate counters serving when primary queue is empty to verify longest-queue selection.
- Verify report matches the sequence of served tokens.

---

## Contributing & license

Contributions, issues and suggestions welcome — open a PR or issue in the repo.  
Licensed under the MIT License. See LICENSE for details.

---

If you want, I can:

- convert the queues to std::queue and replace C-style arrays with STL containers,
- add command-line flags for running automated simulations, or
- add unit tests that exercise limits and serving logic.
