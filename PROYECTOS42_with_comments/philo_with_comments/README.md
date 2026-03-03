*This project has been created as part of the 42 curriculum by idiaz-ca.*

# Philosophers

## Description

**Philosophers** is a concurrency project from the 42 curriculum based on the classic *Dining Philosophers Problem*.

The objective of the project is to simulate a group of philosophers sitting at a round table who alternate between thinking, eating, and sleeping. To eat, a philosopher must pick up two forks (one on the left and one on the right). The challenge is to manage shared resources (forks) using threads and mutexes while avoiding:

- Deadlocks
- Race conditions
- Starvation
- Data corruption

Each philosopher is represented by a thread, and each fork is protected by a mutex. A monitoring thread continuously checks whether a philosopher has died (i.e., exceeded `time_to_die` since their last meal).

The simulation stops immediately when a philosopher dies.

---

## How It Works

- Each philosopher is a separate thread.
- Each fork is represented by a `pthread_mutex_t`.
- A global mutex protects printing to avoid mixed output.
- A monitoring thread checks for philosopher death.
- The simulation uses timestamps in milliseconds to track time.

The simulation ends when:
- A philosopher dies.

---

## Instructions

### Compilation

```bash

make
```

This will generate the executable:
```bash
./philo
```

### Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat 
```
All time values are in milliseconds.

### Example
```bash
./philo 5 800 200 200
```

#### Arguments:

- number_of_philosophers: Number of philosophers and forks.

- time_to_die: Time (ms) a philosopher can live without eating.

- time_to_eat: Time (ms) spent eating.

- time_to_sleep: Time (ms) spent sleeping.

### Example Output

```bash
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
300 1 died
```

#### Output format:

```bash
timestamp_in_ms philosopher_id action
```

#### Possible actions:

- has taken a fork

- is eating

- is sleeping

- is thinking

- died


### Technical Decisions
Mutexes are used to protect:

- Forks

- Printing

- Shared simulation state

- Access to last_meal

A dedicated monitor thread detects death conditions.

The special case of one philosopher is handled explicitly to avoid self-deadlock.

The simulation stops immediately after a death is detected.

### Edge Cases Handled
- Single philosopher (cannot eat, dies correctly).

- Exact boundary death timing (>= time_to_die).

- High contention scenarios.

- Clean thread termination using pthread_join.

## Resources
The following references were used while developing this project:

- POSIX Threads Documentation:
https://man7.org/linux/man-pages/man7/pthreads.7.html

- Mutex Documentation:
https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

- Dining Philosophers Problem:
https://en.wikipedia.org/wiki/Dining_philosophers_problem

- 42 Project Subject (Philosophers)

### Use of Artificial Intelligence
AI tools were used during development for:

- Clarifying conceptual doubts about thread synchronization.

- Reviewing concurrency logic and identifying potential deadlocks.

- Improving code structure and organization.

- Generating documentation structure for this README.

All implementation decisions, debugging, and final code were written and validated manually.