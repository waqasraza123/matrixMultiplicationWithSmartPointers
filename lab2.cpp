//STL implementation of linear and strassenImplementation algo for matrix multiplication
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


//defining max and min constants
#define MAX 100
#define MIN 1

int numberOfRows = 4, numberOfColumns = 4;

vector<vector <int> > simpleMultiplication(vector<vector <int> > vecAObj, vector<vector <int> > vecBObj)
{
	int numberOfRows = vecAObj.size();
	int numberOfColumns = vecAObj[0].size();
	int dimZ = vecBObj[0].size();

	vector<vector <int> > outputResult;
	outputResult.resize(numberOfRows, vector <int> (dimZ, 0));
	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < dimZ; j++) {
			int addElemOfBothMatrices = 0;
			for (int k = 0; k < numberOfColumns; k++)
				addElemOfBothMatrices = addElemOfBothMatrices + (vecAObj[i][k] * vecBObj[k][j]);
			outputResult[i][j] = addElemOfBothMatrices;
		}
	return outputResult;
}


//addElemOfBothMatrices the elements of both vectors
vector<vector <int> > addElemOfBothMatrices(vector<vector <int> > vecAObj, vector<vector <int> > vecBObj) {

	int n = vecAObj.size();
	vector<vector <int> > result;
	result.resize(n, vector <int> (n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = vecAObj[i][j] + vecBObj[i][j];
		}
	}
	return result;
}

vector<vector <int> > subtractElemOfBothMatrices(vector<vector <int> > vecAObj, vector<vector <int> > vecBObj) {

	int n = vecAObj.size();
	vector<vector <int> > result;
	result.resize(n, vector <int> (n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = vecAObj[i][j] - vecBObj[i][j];
		}
	}
	return result;
}

vector<vector <int> > strassenImplementation(vector<vector <int> > vecAObj, vector<vector <int> > vecBObj) {

	int n = vecAObj.size();

	vector<vector <int> > outputResult;
	outputResult.resize(n, vector <int> (n, 0));

	if (n == 1) {
		outputResult[0][0] = vecAObj[0][0] * vecBObj[0][0];
		return outputResult;
	}
	else {
		vector<vector <int> > a11, a12, a21, a22;
		vector<vector <int> > b11, b12, b21, b22;
		vector<vector <int> > c11, c12, c21, c22;
		vector<vector <int> > p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n/2, vector <int> (n/2, 0));
		a12.resize(n/2, vector <int> (n/2, 0));
		a21.resize(n/2, vector <int> (n/2, 0));
		a22.resize(n/2, vector <int> (n/2, 0));

		b11.resize(n/2, vector <int> (n/2, 0));
		b12.resize(n/2, vector <int> (n/2, 0));
		b21.resize(n/2, vector <int> (n/2, 0));
		b22.resize(n/2, vector <int> (n/2, 0));

		c11.resize(n/2, vector <int> (n/2, 0));
		c12.resize(n/2, vector <int> (n/2, 0));
		c21.resize(n/2, vector <int> (n/2, 0));
		c22.resize(n/2, vector <int> (n/2, 0));

		p1.resize(n/2, vector <int> (n/2, 0));
		p2.resize(n/2, vector <int> (n/2, 0));
		p3.resize(n/2, vector <int> (n/2, 0));
		p4.resize(n/2, vector <int> (n/2, 0));
		p5.resize(n/2, vector <int> (n/2, 0));
		p6.resize(n/2, vector <int> (n/2, 0));
		p7.resize(n/2, vector <int> (n/2, 0));

		vector<vector <int> > aResult;
		vector<vector <int> > bResult;
		aResult.resize(n/2, vector <int> (n/2, 0));
		bResult.resize(n/2, vector <int> (n/2, 0));


		int i, j;

		//dividing the matrices in 4 subtractElemOfBothMatrices-matrices:
		for (i = 0; i < n/2; i++) {
			for (j = 0; j < n/2; j++) {
				a11[i][j] = vecAObj[i][j];
				a12[i][j] = vecAObj[i][j + n/2];
				a21[i][j] = vecAObj[i + n/2][j];
				a22[i][j] = vecAObj[i + n/2][j + n/2];

				b11[i][j] = vecBObj[i][j];
				b12[i][j] = vecBObj[i][j + n/2];
				b21[i][j] = vecBObj[i + n/2][j];
				b22[i][j] = vecBObj[i + n/2][j + n/2];
			}
		}

		aResult = addElemOfBothMatrices(a11, a22); // a11 + a22
		bResult = addElemOfBothMatrices(b11, b22); // b11 + b22
		p1 = strassenImplementation(aResult, bResult); // p1 = (a11+a22) * (b11+b22)

		aResult = addElemOfBothMatrices(a21, a22); // a21 + a22
		p2 = strassenImplementation(aResult, b11); // p2 = (a21+a22) * (b11)

		bResult = subtractElemOfBothMatrices(b12, b22); // b12 - b22
		p3 = strassenImplementation(a11, bResult); // p3 = (a11) * (b12 - b22)

		bResult = subtractElemOfBothMatrices(b21, b11); // b21 - b11
		p4 = strassenImplementation(a22, bResult); // p4 = (a22) * (b21 - b11)

		aResult = addElemOfBothMatrices(a11, a12); // a11 + a12
		p5 = strassenImplementation(aResult, b22); // p5 = (a11+a12) * (b22)	

		aResult = subtractElemOfBothMatrices(a21, a11); // a21 - a11
		bResult = addElemOfBothMatrices(b11, b12); // b11 + b12
		p6 = strassenImplementation(aResult, bResult); // p6 = (a21-a11) * (b11+b12)

		aResult = subtractElemOfBothMatrices(a12, a22); // a12 - a22
		bResult = addElemOfBothMatrices(b21, b22); // b21 + b22
		p7 = strassenImplementation(aResult, bResult); // p7 = (a12-a22) * (b21+b22)

										 // calculating c21, c21, c11 e c22:

		c12 = addElemOfBothMatrices(p3, p5); // c12 = p3 + p5
		c21 = addElemOfBothMatrices(p2, p4); // c21 = p2 + p4

		aResult = addElemOfBothMatrices(p1, p4); // p1 + p4
		bResult = addElemOfBothMatrices(aResult, p7); // p1 + p4 + p7
		c11 = subtractElemOfBothMatrices(bResult, p5); // c11 = p1 + p4 - p5 + p7

		aResult = addElemOfBothMatrices(p1, p3); // p1 + p3
		bResult = addElemOfBothMatrices(aResult, p6); // p1 + p3 + p6
		c22 = subtractElemOfBothMatrices(bResult, p2); // c22 = p1 + p3 - p2 + p6

									 // Grouping the results obtained in vecAObj single matrix
		for (i = 0; i < n/2; i++) {
			for (j = 0; j < n/2; j++) {
				outputResult[i][j] = c11[i][j];
				outputResult[i][j + n/2] = c12[i][j];
				outputResult[i + n/2][j] = c21[i][j];
				outputResult[i + n/2][j + n/2] = c22[i][j];
			}
		}
	}
	return outputResult;
}



int randomNum() {
	srand(time(NULL));
	int randomNum = (rand() % ((MAX - MIN) + 1)) + MIN;
	return randomNum;
}


//main thread starts here
int main(){
	vector<vector <int> > vecAObj;
	vector<vector <int> > vecBObj;
    vector<vector <int> > outputResult;

	vecAObj.resize(numberOfRows, vector <int> (numberOfColumns, 0));
	vecBObj.resize(numberOfRows, vector <int> (numberOfColumns, 0));

	//fill the vectors with random numbers
	for (int i = 0; i < numberOfRows; i++) {
		for (int j = 0; j < numberOfColumns; j++) {
			vecAObj[i][j] = randomNum();
			vecBObj[i][j] = randomNum();
		}
	}

	//output
	//here i am outputting the linear mulitplication
    cout << "Linear Multiplication ========================"<<endl;
    outputResult = simpleMultiplication(vecAObj, vecBObj);
    int numberOfRows = outputResult.size();
	int numberOfColumns = outputResult[0].size();
	cout << endl;
	for (int i = 0; i < numberOfRows; i++) {
		cout << endl;
		for (int j = 0; j < numberOfColumns; j++) {
			if (j == numberOfColumns - 1)
				cout << outputResult[i][j];
			else
				cout << outputResult[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
    
    
    //output the result of strassenImplementation's algorightem
    cout << "strassenImplementations's Algorithem ======================="<<endl;
    outputResult = strassenImplementation(vecAObj, vecBObj);
    
	numberOfRows = outputResult.size();
	numberOfColumns = outputResult[0].size();
	cout << endl;
	for (int i = 0; i < numberOfRows; i++) {
		cout << endl;
		for (int j = 0; j < numberOfColumns; j++) {
			if (j == numberOfColumns - 1)
				cout << outputResult[i][j];
			else
				cout << outputResult[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
    
    return 0;
}
