#include <stdio.h>

struct term {
	int power;
	float coeff;
};

void main() {
	
	int l1;
	printf("Enter number of non-zero terms in polynomial 1: ");
	scanf("%d",&l1);
	
	struct term poly1[l1];
	
	for (int i = 0; i < l1; i++) {
		int power;
		float coeff;
		
		printf("Enter power and coefficient: ");
		scanf("%d%f", &power, &coeff);
		
		poly1[i].power = power;
		poly1[i].coeff = coeff;
	}
	
	int l2;
	printf("Enter number of non-zero terms in polynomial 2: ");
	scanf("%d",&l2);
	
	struct term poly2[l2];
	
	for (int i = 0; i < l2; i++) {
		int power;
		float coeff;
		
		printf("Enter power and coefficient: ");
		scanf("%d%f", &power, &coeff);
		
		poly2[i].power = power;
		poly2[i].coeff = coeff;
	}
	
	// Display both polynomials
	for (int i = 0; i < l1; i++) {
		printf("%fx^%d + ", poly1[i].coeff, poly1[i].power);
	}
	printf("0\n");
	for (int i = 0; i < l2; i++) {
		printf("%fx^%d + ", poly2[i].coeff, poly2[i].power);
	}
	printf("0\nRESULT\n");
	
	struct term polyRes[l1+l2];
	
	int onec = 0, twoc = 0, resc = 0;
	while (onec < l1 && twoc < l2) {
		if (poly1[onec].power == poly2[twoc].power){
			polyRes[resc].power = poly1[onec].power;
			polyRes[resc].coeff = poly1[onec].coeff + poly2[twoc].coeff;
			onec++;
			twoc++;
			resc++;
		}
		else if (poly1[onec].power > poly2[twoc].power) {
			polyRes[resc].power = poly1[onec].power;
			polyRes[resc].coeff = poly1[onec].coeff;
			onec++;
			resc++;
		}
		else {
			polyRes[resc].power = poly2[twoc].power;
			polyRes[resc].coeff = poly2[twoc].coeff;
			twoc++;
			resc++;
		}
	}
	
	if (onec < l1) {
		for (int i = 0; onec < l1; onec++) {
			polyRes[resc++] = poly1[onec];
		}
	}
	else if (twoc < l2) {
		for (int i = 0; twoc < l2; twoc++) {
			polyRes[resc++] = poly2[twoc];
		}
	}
	
	for (int i = 0; i < resc; i++) {
		printf("%fx^%d + ", polyRes[i].coeff, polyRes[i].power);
	}
	
	printf("0\n");
}
