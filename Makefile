EXECUTABLE = test

INSTALL_PATH = /usr/local/bin

SOURCE_FILES = main.c Queue/QueueManipulation.c CPU_Scheduling_Algorithms/FIFO/FIFO.c CPU_Scheduling_Algorithms/RR/RR.c CPU_Scheduling_Algorithms/SRT/SRT.c CPU_Scheduling_Algorithms/Priority/Priority.c CPU_Scheduling_Algorithms/Multilevel/MultiLevel.c GanttChart/GanttChart.c

CC = gcc

CFLAGS = -Wall -Wextra -g

all: $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

Queue/QueueManipulation.o: Queue/QueueManipulation.c
	$(CC) $(CFLAGS) -c $< -o $@

FIFO.o: CPU_Scheduling_Algorithms/FIFO/FIFO.c
	$(CC) $(CFLAGS) -c $< -o $@

RR.o: CPU_Scheduling_Algorithms/RR/RR.c
	$(CC) $(CFLAGS) -c $< -o $@

SRT.o: CPU_Scheduling_Algorithms/SRT/SRT.c
	$(CC) $(CFLAGS) -c $< -o $@

Priority.o: CPU_Scheduling_Algorithms/Priority/Priority.c
	$(CC) $(CFLAGS) -c $< -o $@

Multilevel.o: CPU_Scheduling_Algorithms/Multilevel/MultiLevel.c
	$(CC) $(CFLAGS) -c $< -o $@

GanttChart.o: GanttChart/GanttChart.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): main.o Queue/QueueManipulation.o FIFO.o RR.o SRT.o Priority.o Multilevel.o GanttChart.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o Queue/*.o CPU_Scheduling_Algorithms/FIFO/*.o CPU_Scheduling_Algorithms/RR/*.o CPU_Scheduling_Algorithms/SRT/*.o CPU_Scheduling_Algorithms/Priority/*.o CPU_Scheduling_Algorithms/Multilevel/*.o GanttChart/*.o $(EXECUTABLE)

install:
	@if [ -w $(INSTALL_PATH) ]; then \
		cp $(EXECUTABLE) $(INSTALL_PATH); \
		echo "$(EXECUTABLE) has been installed to $(INSTALL_PATH)"; \
	else \
		cp $(EXECUTABLE) ./; \
		echo "Insufficient permissions to install $(EXECUTABLE) in $(INSTALL_PATH). Installed in the current directory instead."; \
	fi

uninstall:
	rm -f $(INSTALL_PATH)/$(EXECUTABLE)
	echo "$(EXECUTABLE) has been uninstalled from $(INSTALL_PATH)"
