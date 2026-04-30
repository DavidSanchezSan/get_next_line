*This project has been created as part of the 42 curriculum by dasanche.*

# Philosophers

## Description
**Philosophers** This project is an implementation of the classic **Dijkstra’s Dining Philosophers** problem using POSIX threads in C. N philosophers alternate between thinking, eating and sleeping, sharing N forks. If a philosopher does not eat within `time_to_die` ms, they die and the simulation ends.

## Instructions

### Requirements
* Unix-like operating system (Linux or macOS)
* `gcc` or `cc`
* pthreads.h library
* Make

### Compilation
Clone the repository and compile the project using:

`make`

This will produce an executable named philo.

#### Available Makefile rules:
* `make` or `make all` – compile the project
* `make clean` – remove object files
* `make fclean` – remove object files and the executable
* `make re` – recompile everything

### Execution
Run philo with:
`./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep>`

Optionally, a final argument can be passed: [must_eat_count]

**Example of execution:**

./philo 5 800 200 200

**Arguments:**
- `num_philos`: Number of philosophers (and forks) at the table. Must be ≥ 1.
- `time_to_die`: Maximum number of milliseconds without eating before death. Must be ≥ 1.
- `time_to_eat`: Duration of the eating action in milliseconds. Must be ≥ 1.
- `time_to_sleep`: Duration of the sleep action in milliseconds. Must be ≥ 1.
- `must_eat_count`: [OPTIONAL] The number of times each philosopher must eat before the game ends. If not specified, the simulation continues until someone dies.

## Resources

### Concurrency strategy

- Mutexes are used to protect access to forks and avoid race conditions
- All philosophers take forks in a specific order to prevent deadlocks
- A monitor thread checks for death conditions and completion conditions

### Technical References Used for the Philosophers Project

The following resources were used to understand and implement the project:

* [Full playlist on threads](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

* [Explanation of monitors](https://www.youtube.com/watch?v=ufdQ0GR855M&t=235s)

* [How to get current time and date](https://www.youtube.com/watch?v=i1MeXMciy6Q)

* [Deadlocks](https://www.youtube.com/watch?v=-eOOlZFsmOg)

* Linux man pages

### Use of Artificial Intelligence
Artificial Intelligence tools were used responsibly and selectively during the development of this project, in accordance with the 42 guidelines.

Specifically, AI assistance was used for:
* Clarifying Threads concepts (deadlock, race conditions, data races, monitors...),
* Identifying edge cases and asking for expected behaviour,
* Detecting and reasoning about potential errors, overflows, and undefined behaviour,
* Support with the initial planning of the project (understanding how printf and write work, thundering herd...),
* Understanding how the system works so any possible error can be handle (like the usleep minimal errors),
* Designing manual tests cases to validate the philosophers behaviours,
* Implementation of short sleeps in critical loops to improve thread scheduling and CPU ussage
* Code refactoring,
* Improving code readability and documentation.

AI was not used to blindly generate complete solutions.

---

### Authors
* dasanche