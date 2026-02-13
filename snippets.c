/*
 * Question #1: optimize the following operation
 */
uint32_t z = y / 8;


//Solution
uint32_t z = y>>3;// 8= 2^3


//Issues:

/*
 * Question #2: analyze incr() function and
 *  - find the issues
 *	- propose possible code improvements 
 */

int16_t incr(int16_t * in)
{
	int16_t rv = (*in);
	rv++;
	return rv; 
}

int32_t main(void)
{
	int16_t x = 32767;
	int16_t y = incr(&x);
}


// Solution

int16_t incr(int16_t *in){
		int16_t rv = (*in);
		rv++;
		return rv;
}
int32_t main(){
	int16_t c = 32767; // first check if the value fits in the int 16, which is 2^8 it does not overflow
	int16_t y = incr(&x);
}

//Issues:

/*
 * Question #3: is there any issue?
 */
#define M 9
#define N 10

int func_2(int * array, N)
{
	int a[M];
	for(int i = 0; i<N; i++)
	{
		a[i] = array[i];
	}
	return 0;
}

int func_1()
{
	int a[N] = {0};
	return(func_2(a, N);
}

// Solution

/* "Define" are preprocessor directives: processed before compiler
M and N are global not need to pass them as args
Array a[M] needs initialisation
Incompelete brackets

Function 2 returns 0 so the return in fucntion 1 can be 0 as well

#define M 9
#define N 10

int func_2(int * array, N)
{
	int a[M]= {0};
	for(int i = 0; i<N; i++)
	{
		a[i] = array[i];
	}
	return 0;
}

int func_1()
{
	int a[N] = {0};
	return(func_2(a, N));
}

*/


/*
 * Question #4: is there any issue?
 */
int* f()
{
	int a[2] = {1, 2};
	int * p = a;
	return p;
}

int main(void)
{
	int * p = f();
	int a, b, c = 4;

	printf("%p\n", p);
	return 0;
}
//Solution
// Dangling pointer issue; should retunr the address to a; 
// but it only lives in the scope of the function
// can't print the array like it



/*
 * Question #5: what are we trying to define here?
 */
typedef struct x_t {
	int val;
	struct x_t * next;
} x_t;

// Solution
//type def behaves like aliasing 
//aliasing the struct for x_t
