<h1 align="center">🏛️ Embassy Consulate Line System</h1>

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/Passport_control_sign.svg/512px-Passport_control_sign.svg.png" alt="project-logo" width="150">
</p>

<p align="center">
  A <b>C++ console-based queue management system</b> that simulates the daily operations of an embassy consulate's visa application process.
  <br>
  Handles multiple visa categories, dynamic counter allocation, daily applicant limits, and generates detailed end-of-day reports.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge" alt="status">
  <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="license">
</p>

---

## 📌 Features

### Visa Categories
- **TR** – Tourist Visa
- **MED** – Medical Visa
- **BS** – Business Visa
- **GO** – Government Officials Visa

### System Capabilities
- **Token System** – Generates unique, sequential tokens with visa type prefix (e.g., `TR-1`, `MED-2`) to ensure fairness.
- **Queue Management** – Four independent queues (one per visa type) using FIFO logic.
- **Counter Management** – Four counters, each primarily serving a specific visa type.
- **Dynamic Allocation** – If a counter's primary queue is empty, it automatically serves from the longest remaining queue.
- **Daily Limits** – Maximum 25 applicants per visa type and 100 total applicants per day.
- **End-of-Day Summary** – Detailed report including:
  - Applicants served per visa type
  - Breakdown of tokens served by each counter
  - Idle counters
  - Total applicants served

---

## 🛠️ Data Structures Used
| Concept | Purpose |
|---------|---------|
| **Queue** | Maintain FCFS order for each visa type |
| **Structs** | `Token` for applicant info, `Counter` for tracking service history |
| **Array** | Store tokens and served token logs efficiently |
| **Global Counter** | Ensure sequential token numbering across all visa types |

---

## 🎯 How It Works

1. **System Initialization**
   - Creates empty queues for each visa type.
   - Sets up counters with their primary visa types.
   - Resets the global token number.

2. **Token Request Flow**
   - Applicant selects a visa type.
   - System checks visa-type and total limits.
   - Generates a token (e.g., `TR-1`) and enqueues it.

3. **Serving Customers**
   - Counter serves from its primary visa queue first.
   - If empty, serves from the longest non-empty queue.
   - Updates service logs and statistics.

4. **Daily Summary Report**
   - Aggregates all counters' served data.
   - Shows visa type statistics, counter breakdown, idle counters, and total served.

---

## 💻 Installation & Usage

1. **Clone Repository**
```bash
git clone https://github.com/<your-username>/embassy-consulate-line-system.git

2. Compile Code
g++ 23-54707-3.cpp -o embassy_system

3. Run Program
./embassy_system
