#include "structures/heap_monitor.h"
#include "VolebnyAnalyzator.h"

int main(int argc, char* argv[]) {
	initHeapMonitor();

	VolebnyAnalyzator interactiveAnalyser;
	interactiveAnalyser.spusti();
	
	return 0;
}