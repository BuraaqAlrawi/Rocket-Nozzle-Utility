// Rocket Nozzle Utility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double RadiusCalculation(double p, double P1, double T1) {
	//Area with respect to pressure, equation 3-25 in Rocket Propulsion Elements
	double k = constants::KNitrogen;

	double a = pow((k + 1) / 2, 1 / (k - 1));
	double b = pow((p / P1), 1 / k);

	double c = sqrt(((k + 1) / (k - 1)) * (1 - pow((p / P1), (k - 1) / k)));

	double At = sqrt(k*constants::R*T1);

	double Ay = (At / (a*b*c));
	double r = sqrt(Ay / constants::pi);
	return r;
}


void generator(double P1, double T1, int resolution) {
	//Defines at which increments calculations will be performed 
	long double stepsize = (constants::sealevelpressure - P1) / resolution;

	double * distance = new double[resolution];
	double *radius = new double[resolution];
	int iterate = 0;

	//Calculates distance from nozzle entrance using inverse square law, and nozzle radius at that distance
	if (P1 > constants::sealevelpressure) {

		long double stepsize = (P1 - constants::sealevelpressure) / resolution;

		for (double p = P1 - stepsize; p >= constants::sealevelpressure; p = p - stepsize) {
			distance[iterate] = sqrt(P1 / (p * 4 * constants::pi));
			radius[iterate] = RadiusCalculation(p, P1, T1);

			iterate++;
		}
	}
	else {
		cout << "Note: Your combustion pressure is less than atmospheric pressure!" << endl;
		long double stepsize = (constants::sealevelpressure - P1) / resolution;

		for (double p = P1 + stepsize; p >= constants::sealevelpressure; p = p + stepsize) {

			distance[iterate] = sqrt(P1 / (p * 4 * constants::pi));
			radius[iterate] = RadiusCalculation(p, P1, T1);
			iterate++;
		}
	}
	ofstream myfile("text.txt");

	for (int i = 0; i < resolution; i++) {
		cout << "Radius at distance " << distance[i] << " is " << radius[i] << endl;
		myfile << distance[i] << "   " << radius[i] << endl;
	}
	myfile.close();
}


int main()
{
	cout << "Input combustion chamber pressure, temperature, and number of points to be evaluated" << endl;

	double pressure;
	double temperature;
	int resolution;

	cin >> pressure;
	cin >> temperature;
	cin >> resolution;

	generator(pressure, temperature, resolution);

	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

