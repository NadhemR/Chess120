/*	File: Assert.h
 *	Purpose:	Redefine the assert macro for detailed debugging (as opposed to one in standard library)
				ASSERT() is used to check conditions ex. ASSERT(num == 5)
				Prints a detailed error message if condition is FALSE
 */

#ifndef ASSRT_H
#define ASSRT_H

#define DEBUG		// Comment this line out to disable macro

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
			exit(1); \
		}
#endif // !DEBUG


#endif // !ASSRT_H