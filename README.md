# IT 204 Operating Systems

This repository keeps track of projects from the course.

-Members of the group:
1. Basar Carovac
2. Orhan Huseinbegovic

-List of all files/directories:
1. it-204-operating-systems
    1.1. PROJECT-1
        1.1.1. shell
        1.1.2. shell.C
    1.2. README.md    

-Answers to the questions in the assignment:

Task 1.5:
    Question 1.5.1: What does the mmap() function do?

    Answer: In Linux, the mmap() function is commonly used for memory mapping files or devices into the virtual memory address space of a process. It provides a flexible and efficient way to work with large files, shared memory, and memory-mapped I/O.

    Question 1.5.2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.

    Answer: Context switching is the process of switching the CPU from one process, task or thread to another. In a multitasking operating system, such as Linux, the CPU has to switch between multiple processes or threads in order to keep the system running smoothly. This is necessary because each CPU core without hyperthreading can only execute one process or thread at a time. If there are many processes or threads running simultaneously, and very few CPU cores available to handle them, the system is forced to make more context switches to balance the CPU resources among them.

    Context switching is an essential function of any multitasking operating system, but it also comes at a cost. The whole process is computationally intensive, and the more context switches that occur, the slower the system becomes. This is because each context switch involves saving the current state of the CPU, loading the state of the new process or thread, and then resuming execution of the new process or thread. This takes time and consumes CPU resources, which can slow down the system.

    The impact of context switching on system performance can be significant, especially in systems with many processes or threads running simultaneously.

    Question 1.5.3: What is the output of the following code snippet? You are given that the exec system call in the child does not succeed.
    
    Answer: Assuming exec(some_binary_that_does_not_exec); fails as stated, the child process won't execute the printf("child\n"); statement because exec would replace the child process with the specified binary. 
    Since the execution of exec fails, the child process won't print anything, and it will terminate due to the failed exec.

    The parent process will wait for the child process to terminate using wait(). Once the child process terminates (even if it fails to execute exec), the parent process continues execution. Therefore, the output of the code snippet will be:
    parent

-Outline of what we did for the assignment:

-Instructions for compiling our programs/scripts:

-Challenges we have encountered along the way:

-Sources/tutorials that we have used:
    1. https://blog.netdata.cloud/understanding-context-switching-and-its-impact-on-system-performance/
    2. 
    3.

