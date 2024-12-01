# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pthread

# Source files
SRCS = src/micro_philosophers.c

# Header files
HDRS = includes/micro_philosophers.h

# Output executable
TARGET = micro_philo

# Object files
OBJS = $(SRCS:.c=.o)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m # No Color

# Default target
all: $(TARGET)
	@echo "$(GREEN)Build complete!$(NC)"
	@echo "$(GREEN)███╗   ███╗██╗ ██████╗██████╗  ██████╗         ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗$(NC)"
	@echo "$(GREEN)████╗ ████║██║██╔════╝██╔══██╗██╔═══██╗        ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝$(NC)"
	@echo "$(GREEN)██╔████╔██║██║██║     ██████╔╝██║   ██║        ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗$(NC)"
	@echo "$(GREEN)██║╚██╔╝██║██║██║     ██╔══██╗██║   ██║        ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║$(NC)"
	@echo "$(GREEN)██║ ╚═╝ ██║██║╚██████╗██║  ██║╚██████╔╝███████╗██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║$(NC)"
	@echo "$(GREEN)╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝$(NC)"
	@echo "$(GREEN)                                         01/12/2024 - ismherna@student.42.fr - 42 Madrid & U-Tad- Ismael Hernández$(NC)"

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS)
	@echo -e "$(RED)Object files removed!$(NC)"

# Full clean up
fclean: clean
	rm -f $(TARGET)
	@echo -e "$(RED)Executable removed!$(NC)"

# Recompile the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re
