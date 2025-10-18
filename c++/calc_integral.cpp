#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>

double eq1(double x) {
	return 1.0 / (x * x);
}
double eq2(double x) {
	return exp(x);
}
double eq3(double x) {
	return 2 / (1 + x * x);
}

int main() {
	double a, b, c;
	double fa, fb, fc;
	double kai, sum, h, x, gosa_p;
	int i, n;

	/*kai = 0.5;
	a = 1;
	b = 2;

	for (n = 2; n <= 1024; n *= 2) {
		h = (b - a) / (double)n;
		sum = 0.0;

		for (i = 0; i < n; i++) {
			x = a + (double)i*h;

			sum += eq1(x);
		}
		sum *= h;
		if (n == 2) {
			printf("%d ;%f, %f, %.14e,--------------- \n", n, sum, kai, fabs(sum - kai));
		}
		else if(n !=2){
			printf("%d ;%f, %f, %.14e,%.14e, \n", n, sum, kai, fabs(sum - kai), -log(fabs(sum - kai) / gosa_p) / log(2.0));
		}
		gosa_p = fabs(sum - kai);
	}


	printf("\n\n");
	kai = 1.71828182845904;
	a = 0;
	b = 1;

	for (n = 2; n <= 1024; n *= 2) {
		h = (b - a) / (double)n;
		sum = 0.0;

		for (i = 0; i < n; i++) {
			x = a + (double)i*h;

			sum += eq2(x);
		}
		sum *= h;
		if (n == 2) {
			printf("%d ;%f, %f, %.14e,--------------- \n", n, sum, kai, fabs(sum - kai));
		}
		else if (n != 2) {
			printf("%d ;%f, %f, %.14e,%.14e, \n", n, sum, kai, fabs(sum - kai), -log(fabs(sum - kai) / gosa_p) / log(2.0));
		}
		gosa_p = fabs(sum - kai);
	}
	printf("\n\n");*/

	kai = 3.14159265358979;
	a = -1;
	b = 1;

	for (n = 2; n <= 1024; n *= 2) {
		h = (b - a) / (double)n;
		sum = 0.0;

		for (i = 0; i < n; i++) {
			x = a + (double)i * h;

			sum += eq3(x);
		}
		sum *= h;
		if (n == 2) {
			printf("%d ;%f, %f, %.14e,--------------- \n", n, sum, kai, fabs(sum - kai));
		}
		else if (n != 2) {
			printf("%d ;%f, %f, %.14e,%.14e, \n", n, sum, kai, fabs(sum - kai), -log(fabs(sum - kai) / gosa_p) / log(2.0));
		}
		gosa_p = fabs(sum - kai);
	}
	return 0;

}