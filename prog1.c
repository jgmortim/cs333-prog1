/* ----------------------------------------------------------- */
/* NAME : John Mortimroe                     User ID: jgmortim */
/* DUE DATE : 02/11/2019                                       */
/* PROGRAM ASSIGNMENT 1                                        */
/* FILE NAME : prog1.c                                         */
/* PROGRAM PURPOSE :                                           */
/*    This program forks four children, which run concurrently.*/
/*    Child 1 computes a fibonacci number. Child 2 simulates   */
/*    the Buffon's Neddle Problem. Child 3 approximates the    */
/*    integral of sin(x) from o to pi. Child 4 approximates e  */
/*    using Bernoulli's method. After every child exits, the   */ 
/*    main program also exits.                                 */
/*                                                             */
/*    Tested with Valgrind 2/8/19: no memory leaks or errors.  */
/* ----------------------------------------------------------- */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h> 
#include <stdio.h>

void first(long n);
void second(long r);
void third(long s);
void fourth(long m);
int sizeI(int number);
int sizeL(long number);
long fib(long n);
double buffon(long r);
double bernoulli(long i);

/* ----------------------------------------------------------- */
/* FUNCTION : main                                             */
/*    The main method for the program.                         */
/* PARAMETER USAGE :                                           */
/*    argc {int} - number of argument.                         */
/*    argv {char**} - list of arguments.                       */
/* FUNCTIONS CALLED :                                          */
/*    atol(), exit(), first(), fork(), fourth(), free()        */
/*    malloc(), second(), sizeL(), sizeof(), sprintf(),        */
/*    strlen(), third(), wait(), write()                       */
/* ----------------------------------------------------------- */
int main(int argc, char** argv) {
	long m, n, r, s;
	int status, expectedArgc=5;
	pid_t pid1=-1, pid2=-1, pid3=-1, pid4=-1;
	char* line1, *line2, *line3;
	char* text1="Main Process Started\n";
	char* text2="Buffon's Needle Iterations = ";
	char* text3="Integration Iterations     = ";
	char* text4="Approx. e Iterations       = ";
	char* text5="Fibonacci Process Created\n";
	char* text6="Buffon's Needle Process Created\n";
	char* text7="Integration Process Created\n";
	char* text8="Approximation of e Process Created\n";
	char* text9="Main Process Waits\n";
	char* text10="Main Process Exits\n";
	char* textn="\n";
	char* error1="prog1 <m> <n> <r> <s> \n";
	char* error2="fork failed, program terminated.\n";

	if (argc != expectedArgc) { 			/* If incorrect input, */
		write(1, error1, strlen(error1));	/* print the proper syntax, */
		return 1; 				/* and exit. */
    	}
	/* Print start message. */
	write(1, text1, strlen(text1));
	/* Read the arguments. */
	m= atol(argv[1]);
	n= atol(argv[2]);
	r= atol(argv[3]);
	s= atol(argv[4]);
	/* Print Buffon Needle info. */
	line1 = malloc(sizeof(char)*(strlen(text2)+sizeL(r)+strlen(textn)));
	sprintf(line1, "%s%ld%s", text2, r, textn);
	write(1, line1, strlen(line1));	
	free(line1);
	/* Print integration info. */
	line2 = malloc(sizeof(char)*(strlen(text3)+sizeL(s)+strlen(textn)));
	sprintf(line2, "%s%ld%s", text3, s, textn);
	write(1, line2, strlen(line2));
	free(line2);
	/* Print e approximation info. */
	line3 = malloc(sizeof(char)*(strlen(text4)+sizeL(m)+strlen(textn)));
	sprintf(line3, "%s%ld%s", text4, m, textn);
	write(1, line3, strlen(line3));
	free(line3);

	/* Create child 1 and print result. */
	if ((pid1=fork())==0) {
		first(n);
	} else if (pid1<0) {
		write(1, error2, strlen(error2));
		return 1;
	} else {
		write(1, text5, strlen(text5));
	}
	/* Create child 2 and print result. */
	if ((pid2=fork())==0) {
		second(r);
	} else if (pid2<0) {
		write(1, error2, strlen(error2));
		return 1;
	} else {
		write(1, text6, strlen(text6));
	}
	/* Create child 3 and print result. */
	if ((pid3=fork())==0) {
		third(s);
	} else if (pid3<0) {
		write(1, error2, strlen(error2));
		return 1;
	} else {
		write(1, text7, strlen(text7));
	}
	/* Create child 4 and print result. */
	if ((pid4=fork())==0) {
		fourth(m);
	} else if (pid4<0) {
		write(1, error2, strlen(error2));
		return 1;
	} else {
		write(1, text8, strlen(text8));
	}
	/* Print wait message. */
	write(1, text9, strlen(text9));
	/* Wait for 4 children to end. */
	wait(&status);
	wait(&status);
	wait(&status);
	wait(&status);
	/* Print exit message and exit. */
	write(1, text10, strlen(text10));
	exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION : first                                            */
/*    Performs the tasks of the first child. See               */
/*    www.csl.mtu.edu/cs3331.ck/www/PROG/PG1/prog1.html        */
/*    for complete specifications.                             */
/* PARAMETER USAGE :                                           */
/*    n {long} - fibonacci number to calculate.                */
/* FUNCTIONS CALLED :                                          */
/*    exit(), fib(), free(), malloc(), sizeL(), sizeof(),      */
/*    sprintf(), strlen(), write()                             */
/* ----------------------------------------------------------- */
void first(long n) {
	char* text1="      Fibonacci Process Started\n";
	char* text2="      Input Number ";
	char* text3="      Fibonacci Number f(";
	char* text4=") is ";
	char* text5="      Fibonacci Process Exits\n";
	char* textn="\n";
	char* line2, *line3;
	long result;

	/* Print line 1. */
	write(1, text1, strlen(text1));
	/* Print line 2. */
	line2 = malloc(sizeof(char)*(strlen(text2)+sizeL(n)+strlen(textn)));
	sprintf(line2, "%s%ld%s", text2, n, textn);
	write(1, line2, strlen(line2));
	free(line2);
	/* Calculate fibonacci number and print line 3. */
	result = fib(n);
	line3 = malloc(sizeof(char)*(strlen(text3)+sizeL(n)+strlen(text4)+sizeL(result)+strlen(textn)));
	sprintf(line3, "%s%ld%s%ld%s", text3,n,text4,result,textn);
	write(1, line3, strlen(line3));
	free(line3);
	/* Print line 4 and exit. */
	write(1, text5, strlen(text5));
	exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION : second                                           */
/*    Performs the tasks of the second child. See              */
/*    www.csl.mtu.edu/cs3331.ck/www/PROG/PG1/prog1.html        */
/*    for complete specifications.                             */
/* PARAMETER USAGE :                                           */
/*    r {long} - number of needle throws to simulate.          */
/* FUNCTIONS CALLED :                                          */
/*    buffon(), exit(), free(), malloc(), sizeL(), sizeof(),   */
/*    sprintf(), strlen(), write()                             */
/* ----------------------------------------------------------- */
void second(long r) {
	char* text1="         Buffon's Needle Process Started\n";
	char* text2="         Input Number ";
	char* text3="         Estimated Probability is ";
	char* text4="         Buffon's Needle Process Exits\n";
	char* textn="\n";
	char* line2, *line3;
	double result;
	int SizeForFloats=50; /* Floats/doubles will never print with more than 50 digits. */
	

	/* Print line 1. */
	write(1, text1, strlen(text1));
	/* Print line 2. */
	line2 = malloc(sizeof(char)*(strlen(text2)+sizeL(r)+strlen(textn)));
	sprintf(line2, "%s%ld%s", text2, r, textn);
	write(1, line2, strlen(line2));
	free(line2);
	/* Calculate probability and print line 3. */
	result = buffon(r);
	line3 = malloc(sizeof(char)*(strlen(text3)+SizeForFloats+strlen(textn)));
	sprintf(line3, "%s%1.5f%s", text3, result, textn);
	write(1, line3, strlen(line3));
	free(line3);
	/* Print line 4 and exit. */
	write(1, text4, strlen(text4));	
	exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION : third                                            */
/*    Performs the tasks of the third child. See               */
/*    www.csl.mtu.edu/cs3331.ck/www/PROG/PG1/prog1.html        */
/*    for complete specifications.                             */
/* PARAMETER USAGE :                                           */
/*    s {long} - number of random points.                      */
/* FUNCTIONS CALLED :                                          */
/*    acos(), exit(), free(), malloc(), rand(), sin(),         */
/*    sizeI(), sizeL(), sizeof(), sprintf(), srand(),          */
/*    strlen(), time(), write()                                */
/* ----------------------------------------------------------- */
void third(long s) {
	char* text1="            Integration Process Started\n";
	char* text2="            Input Number ";
	char* text3="            Total Hit ";
	char* text4="            Estimated Area is ";
	char* text5="            Integration Process Exits\n";
	char* textn="\n";
	char* line2, *line3, *line4;
	double a, b, result;
	const double pi=acos(-1.0);
	int i, t=0;
	int SizeForFloats=50; /* Floats/doubles will never print with more than 50 digits. */
	/* Print line 1. */
	write(1, text1, strlen(text1));
	/* Print line 2 */
	line2 = malloc(sizeof(char)*(strlen(text2)+sizeL(s)+strlen(textn)));
	sprintf(line2, "%s%ld%s", text2, s, textn);
	write(1, line2, strlen(line2));
	free(line2);
	/* Calculate number of hits and print line 3 */
	srand(time(0));
	for (i=0; i<s; i++) {					/* For s points: */
		a=(double) rand()*pi/(RAND_MAX+1.0);		/* a = random number [0,pi). */
		b=(double) rand()/(RAND_MAX+1.0);		/* b = random number [0,1). */
		if (b <= sin(a)) {				/* If point in under curve, */
			t++;					/* increase the number of hits. */
		}
	}
	line3 = malloc(sizeof(char)*(strlen(text3)+sizeI(t)+strlen(textn)));
	sprintf(line3, "%s%d%s", text3, t, textn);
	write(1, line3, strlen(line3));
	free(line3);
	/* Calculate the estimated area and print line 4 */
	result= (double) t*pi/s;				/* Area calculation. */
	line4 = malloc(sizeof(char)*(strlen(text4)+SizeForFloats+strlen(textn)));
	sprintf(line4, "%s%1.7f%s", text4, result, textn);
	write(1, line4, strlen(line4));
	free(line4);
	/* Print line 5 and exit. */
	write(1, text5, strlen(text5));	
	exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION : fourth                                           */
/*    Performs the tasks of the fourth child. See              */
/*    www.csl.mtu.edu/cs3331.ck/www/PROG/PG1/prog1.html        */
/*    for complete specifications.                             */
/* PARAMETER USAGE :                                           */
/*    m {long} - exponent in Bernoulli's method.               */
/* FUNCTIONS CALLED :                                          */
/*    bernoulli(), exit(), exp(), fabs(), free(), malloc(),    */
/*    realloc(), sizeof(), sprintf(), strlen(), write()        */
/* ----------------------------------------------------------- */
void fourth(long m) {
	const double e = exp(1.0);
	char* text1="   Approximation of e Process Started\n";
	char* text2="   Maximum of the Exponent ";
	char* textn="\n";
	char* text3s="   ";
	char* text4s="    ";
	char* line2, *line3;
	double result, difference;
	long i;
	int SizeForFloats=50;  /* Floats/doubles will never print with more than 50 digits. */
	/* Print line 1. */
	write(1, text1, strlen(text1));
	/* Print line 2. */
	line2 = malloc(sizeof(char)*(strlen(text2)+SizeForFloats+strlen(textn)));
	sprintf(line2, "%s%ld%s", text2, m, textn);
	write(1, line2, strlen(line2));
	free(line2);
	/* Approximate e with different exponents and print results. */
	line3=malloc(1);
	for (i=1; i<=m;) {
		result = bernoulli(i);				/* Calculate approximation. */
		difference = fabs(e - result);			/* Calculate difference. */
		/* Contains 3 strings and 3 floats. */
		line3 = realloc(line3, sizeof(char)*(strlen(text3s)+3*SizeForFloats+strlen(text4s)+strlen(text4s)+strlen(textn)));
		sprintf(line3, "%s%18lu%s%1.15f%s%1.15f%s", text3s, i, text4s, result, text4s, difference, textn);
		write(1, line3, strlen(line3));
		if (i < 10) {
			i++;
		} else if (i == 10) {
			i=16;
		} else {
			i=i*2;
		}		
	}
	free(line3);
	exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION : sizeI                                            */
/*    Computes the number of char's needed to print an int.    */
/* PARAMETER USAGE :                                           */
/*    number {int} - the number to measure.                    */
/* FUNCTIONS CALLED :                                          */
/*    sprintf()                                                */
/* ----------------------------------------------------------- */
int sizeI(int number) {
	int JustInCase=10; /* Extra space just in case. */
	char buffer[100];
	int size = sprintf(buffer, "%d", number)+JustInCase;
	return size;
}

/* ----------------------------------------------------------- */
/* FUNCTION : sizeL                                            */
/*    Computes the number of char's needed to print a Long.    */
/* PARAMETER USAGE :                                           */
/*    number {long} - the number to measure                    */
/* FUNCTIONS CALLED :                                          */
/*    sprintf()                                                */
/* ----------------------------------------------------------- */
int sizeL(long number) {
	int JustInCase=10; /* Extra space just in case. */
	char buffer[100];
	int size = sprintf(buffer, "%lu", number)+JustInCase;
	return size;	
}

/* ----------------------------------------------------------- */
/* FUNCTION : fib                                              */
/*    Recursively computes Fibonacci numbers.                  */
/* PARAMETER USAGE :                                           */
/*    n {long} - the Fibonacci number to compute.              */
/* FUNCTIONS CALLED :                                          */
/*    fib()                                                    */
/* ----------------------------------------------------------- */
long fib(long n) {
	if (n <= 1) {
		return n;
	} else {
		return fib(n-1) + fib(n-2);
	}
}

/* ----------------------------------------------------------- */
/* FUNCTION : buffon                                           */
/*    Calculates the probabilty for Buffon's Neddle Problem    */
/*    by simulating needle throws. Let G=L=1.                  */
/* PARAMETER USAGE :                                           */
/*    r {long} - number of needle throws.                      */
/* FUNCTIONS CALLED :                                          */
/*    acos(), rand(), sin(), srand(), time()                   */
/* ----------------------------------------------------------- */
double buffon(long r) {
	const int G=1;
	const int L=1;
	int i, t=0;
	double result, random_d, random_a;
	const double pi=acos(-1.0);
	srand(time(0));
	for (i=0; i<r; i++) {				/* Throw r needles. */
		random_d=(double) rand()/(RAND_MAX+1.0);	/* d = random number [0,1). */
		random_a=(double) 2*rand()*pi/(RAND_MAX+1.0);	/* a = random number [0,2pi). */
		result = random_d+L*sin(random_a);		/* Calculate result. */
		if (result < 0 || result > G) {			/* If result is < 0 or > G, */
			t++;					/* needle crosses line. */
		}
	}
	return (double) t/r;				/* Return the ratio of hits to misses. */
}

/* ----------------------------------------------------------- */
/* FUNCTION : bernoulli                                        */
/*    Uses Bernoulli's Method to approximate e.                */
/* PARAMETER USAGE :                                           */
/*    i {long} - used in (1+1/i)^i.                            */
/* FUNCTIONS CALLED :                                          */
/*    pow()                                                    */
/* ----------------------------------------------------------- */
double bernoulli(long i) {
	double e = (double) 1/i +1;
	e = (double) pow(e, i);
	return e;
}

