# Micro Philosophers

This project, developed as part of the **Philosophers** project at 42 Madrid and a systems programming activity at U-Tad, is a multithreading and multiprocessing simulation of the famous **Dining Philosophers Problem**. It showcases advanced synchronization techniques using **semaphores**, **threads**, and **processes** to solve concurrency challenges.

---

## 🎯 **Learning Goals**

### **1. Synchronization with Semaphores**

Semaphores are a fundamental tool in managing concurrent access to shared resources. This project demonstrates their use to:

- Prevent **race conditions** when philosophers attempt to pick up shared forks.
- Ensure mutual exclusion when writing log messages to the console.

### **2. Threads vs. Processes**

Understanding the distinction between threads and processes is key:

- **Threads** are lightweight, sharing the same memory space, making inter-thread communication faster but requiring careful synchronization.
- **Processes**, in contrast, run in isolated memory spaces, providing better fault tolerance but making communication more complex.

This simulation uses **processes** to simulate each philosopher as an independent unit and **threads** for monitoring mechanisms.

### **3. Practical Application**

- Hands-on experience with **POSIX semaphores** and **pthread libraries**.
- Implementation of **concurrency-safe algorithms** for real-time simulations.

---

## 🛠️ **How to Use the Code**

### **1. Clone the Repository**

```bash

git clone https://github.com/your-repo/micro-philosophers.git
cd micro-philosophers

```

### **2. Build the Project**

The project uses a custom `Makefile` for compilation:

```bash

make

```

### **3. Run the Simulation**

To run the executable, use the following syntax:

```bash

./micro_philo [num_philos] [time_to_die] [time_to_eat] [time_to_sleep] [num_meals]

```

**Parameters:**

- `num_philos`: Number of philosophers (and forks).
- `time_to_die`: Time (in ms) before a philosopher dies without eating.
- `time_to_eat`: Time (in ms) it takes for a philosopher to eat.
- `time_to_sleep`: Time (in ms) for a philosopher to sleep after eating.
- `num_meals` (optional): Number of meals each philosopher must eat before the simulation ends.

**Example:**

```bash

./micro_philo 5 800 200 200 3

```

### **4. Clean Up**

To remove the compiled files:

```bash
make clean

```

---

## 📖 **Explanation of Concepts**

### **The Dining Philosophers Problem**

This classic problem in computer science demonstrates the challenges of resource allocation and synchronization. Philosophers alternately think and eat, requiring forks (shared resources) to eat. The key is to avoid **deadlock** (where all philosophers wait indefinitely) and **starvation** (where some philosophers never get to eat).

### **Processes and Threads in the Project**

- **Processes for Philosophers:**
    
    Each philosopher runs as an independent process. This allows for better isolation and makes it easier to terminate a specific philosopher without affecting others.
    
- **Threads for Monitoring:**
    - A **death monitor thread** checks if any philosopher has exceeded the `time_to_die` without eating.
    - A **meals monitor thread** ensures all philosophers have eaten the required number of meals (if specified).

### **Synchronization with Semaphores**

- **`forks` Semaphore:**
    
    Controls access to the forks. A philosopher must acquire two forks (two semaphore locks) to eat.
    
- **`write_lock` Semaphore:**
    
    Ensures that log messages are written to the console in a thread-safe manner.
    
- **`meals_done` Semaphore:**
    
    Tracks how many philosophers have completed the required meals.
    
- **`stop` Semaphore:**
    
    Signals when the simulation should end, either due to all philosophers eating or a philosopher dying.
    

---

## ✨ **Key Features**

1. **Real-Time Simulation:**
    
    Logs the actions of philosophers in real-time, including thinking, eating, sleeping, and dying.
    
2. **Highly Modular Codebase:**
    - `init_args`: Initializes arguments and semaphores.
    - `start_philosophers`: Forks processes and starts the simulation.
    - `take_forks_and_eat` and `sleep_and_think`: Define the philosopher's lifecycle.
    - `monitor_death` and `monitor_meals`: Handle monitoring in separate threads.
3. **Extensible Design:**
    
    Easy to modify for experimenting with different synchronization mechanisms or philosopher behaviors.
    

---

## 🎨 **Code Structure**

### **Files**

- `src/micro_philosophers.c`: Main logic of the program.
- `includes/micro_philosophers.h`: Header file containing type definitions and function prototypes.
- `Makefile`: Build automation script.

### **Functions**

- **`main`**: Entry point for argument validation and simulation control.
- **`init_semaphores`**: Sets up semaphores for resource management.
- **`philosopher_routine`**: Defines the lifecycle of a philosopher.
- **`monitor_death` and `monitor_meals`**: Implement monitoring logic.

---

## 💡 Extras

This project is inspired by the **Philosophers** project at [42](https://42.fr/) and a **systems programming activity** at [U-TAD](https://u-tad.com/). Special thanks to the instructors and peers for their guidance in mastering the art of concurrent programming.

Enjoy the code.