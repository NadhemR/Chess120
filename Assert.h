// Defining an ASSERT Macro for debugging
#ifndef ASSRT_H
#define ASSRT_H

#define DEBUG

#ifndef DEBUG
	#define ASSERT(n)
#else
	#define ASSERT(n) \
	if(!(n)) { \
		printf("%s - Failed", #n); \
		printf("On %s ", __DATE__); \
		printf("At %s ", __TIME__); \
		printf("In File %s ", __FILE__); \
		printf("At Line %d \n", __LINE__); \
		system("PAUSE"); \
		exit(1); }
#endif // !DEBUG


#endif // !ASSRT_H