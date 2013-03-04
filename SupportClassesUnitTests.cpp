#include "SupportClasses.cpp"

using namespace std;

class Vector3Test {
public:
	static void assertEmptyConstructor();
	static void assertConstructor();
	static void assertAdd();
	static void assertSubtract();
	static void assertScalar();
	static void assertDivide();
	static void assertNormalize();
	static void assertpointSubstraction();
	static void assertdotProduct();
};

class PointTest {
public:
	static void assertEmptyConstructor();
	static void assertConstructor();
	static void assertAdd();
	static void assertSubtract();
};

class NormalTest {
public:
	static void assertEmptyConstructor();
	static void assertConstructor();
	static void assertAdd();
	static void assertSubtract();
};

void Vector3Test::assertEmptyConstructor() {
	Vector3 test;
	if(test.x==0 && test.y==0 && test.z==0) {
		cout<<"assertEmptyConstructor passed."<<endl;
	} else {
		cout<<"assertEmptyConstructor FAILED."<<endl;
	}
}

void Vector3Test::assertConstructor() {
	Vector3 test(4.7, 5.0, 3.0);
	if(test.x==(float)4.7 && test.y==5.0 && test.z==3.0) {
		cout<<"assertConstructor passed."<<endl;
	} else {
		cout<<"assertConstructor FAILED."<<endl;
	}
}

void Vector3Test::assertAdd() {
	Vector3 add1(1.0, 2.0, 3.0);
	Vector3 add2(4.5, 4.5, 4.5);
	Vector3 result = add1+add2;
	if(result.x==(float)5.5 && result.y==(float)6.5 && result.z==(float)7.5) {
		cout<<"assertAdd passed."<<endl;
	} else {
		cout<<"assertAdd FAILED."<<endl;
	}
}

void Vector3Test::assertSubtract() {
	Vector3 add1(1.0, 2.0, 3.0);
	Vector3 add2(4.5, 4.5, 4.5);
	Vector3 result = add1-add2;
	if(result.x==(float)-3.5 && result.y==(float)-2.5 && result.z==(float)-1.5) {
		cout<<"assertSubtract passed."<<endl;
	} else {
		cout<<"assertSubtract FAILED."<<endl;
	}
}

void Vector3Test::assertScalar() {
	Vector3 add1(1.0, 0.0, 1.0);
	Vector3 result = add1*(float)4.5;
	if(result.x==(float)4.5 && result.y==0.0 && result.z==(float)4.5) {
		cout<<"assertScalar passed."<<endl;
	} else {
		cout<<"assertScalar FAILED."<<endl;
	}
}

void Vector3Test::assertDivide() {
	Vector3 add1(5.0, 0.0, 5.0);
	Vector3 result = add1/(float)2.5;
	if(result.x==(float)2.0 && result.y==0.0 && result.z==(float)2.0) {
		cout<<"assertDivide passed."<<endl;
	} else {
		cout<<"assertDIvide FAILED."<<endl;
	}
}

void Vector3Test::assertNormalize() {
	Vector3 test(1.0, 1.0, 1.0);
	Vector3 result = test.normalize();
	if(result.x==((float)(1.0/(float)sqrt(3))) && result.y==((float)(1.0/(float)sqrt(3))) && result.z==((float)(1.0/(float)sqrt(3)))) {
		cout<<"assertNormalize passed."<<endl;
	} else {
		cout<<"assertNormalize FAILED."<<endl;
	}
}

void Vector3Test::assertpointSubstraction() {
	Point p1(1.0, 1.0, 1.0);
	Point p2(3.0, 4.0, 5.0);
	Vector3 result = Vector3::pointSubtraction(p2, p1);
	if(result.x==(float)2.0 && result.y==3 && result.z==4) {
		cout<<"assertpointSubstraction passed."<<endl;
	} else {
		cout<<"assertpointSubstraction FAILED."<<endl;
	}
}

void Vector3Test::assertdotProduct() {
	Vector3 temp1(1.0, 1.0, 1.0);
	Vector3 temp2(2.0, 2.5, 2.0);
	float result = Vector3::dotProduct(temp1, temp2);
	if(result==(float)6.5) {
		cout << "assertdotProduct passed." << endl;
	} else {
		cout << "assertdotProduct FAILED." <<endl;
	}
}

void PointTest::assertEmptyConstructor() {
	Point test;
	if(test.x==0 && test.y==0 && test.z==0) {
		cout<<"assertEmptyConstructor passed."<<endl;
	} else {
		cout<<"assertEmptyConstructor FAILED."<<endl;
	}
}

void PointTest::assertConstructor() {
	Point test(4.7, 5.0, 3.0);
	if(test.x==(float)4.7 && test.y==5.0 && test.z==3.0) {
		cout<<"assertConstructor passed."<<endl;
	} else {
		cout<<"assertConstructor FAILED."<<endl;
	}
}

void PointTest::assertAdd() {
	Point add1(1.0, 2.0, 3.0);
	Point add2(4.5, 4.5, 4.5);
	Point result = add1+add2;
	if(result.x==(float)5.5 && result.y==(float)6.5 && result.z==(float)7.5) {
		cout<<"assertAdd passed."<<endl;
	} else {
		cout<<"assertAdd FAILED."<<endl;
	}
}

void PointTest::assertSubtract() {
	Point add1(1.0, 2.0, 3.0);
	Point add2(4.5, 4.5, 4.5);
	Point result = add1-add2;
	if(result.x==(float)-3.5 && result.y==(float)-2.5 && result.z==(float)-1.5) {
		cout<<"assertSubtract passed."<<endl;
	} else {
		cout<<"assertSubtract FAILED."<<endl;
	}
}

void NormalTest::assertEmptyConstructor() {
	Normal test;
	if(test.x==0 && test.y==0 && test.z==0) {
		cout<<"assertEmptyConstructor passed."<<endl;
	} else {
		cout<<"assertEmptyConstructor FAILED."<<endl;
	}
}

void NormalTest::assertConstructor() {
	/*Normal test(4.7, 5.0, 3.0);
	if(test.x==(float)4.7 && test.y==5.0 && test.z==3.0) {
		cout<<"assertConstructor passed."<<endl;
	} else {
		cout<<"assertConstructor FAILED."<<endl;
	}*/
}

void NormalTest::assertAdd() {
	/*Normal add1(1.0, 2.0, 3.0);
	Normal add2(4.5, 4.5, 4.5);
	Normal result = add1+add2;
	if(result.x==(float)5.5 && result.y==(float)6.5 && result.z==(float)7.5) {
		cout<<"assertAdd passed."<<endl;
	} else {
		cout<<"assertAdd FAILED."<<endl;
	}*/
}

void NormalTest::assertSubtract() {

}

int main(int argc, char *argv[]) {
	/*cout << "--------RUNNING UNIT TESTS--------"<< endl;

	cout << "RUNNING TESTS ON Vector3 CLASS..." << endl;
	Vector3Test::assertEmptyConstructor();
	Vector3Test::assertConstructor();
	Vector3Test::assertAdd();
	Vector3Test::assertSubtract();
	Vector3Test::assertScalar();
	Vector3Test::assertDivide();
	Vector3Test::assertNormalize();
	Vector3Test::assertpointSubstraction();
	Vector3Test::assertdotProduct();
	cout << "TESTS FINISHED ON Vector3 CLASS.\n"<<endl;

	cout << "RUNNING TESTS ON Point CLASS..."<<endl;
	PointTest::assertEmptyConstructor();
	PointTest::assertConstructor();
	PointTest::assertAdd();
	PointTest::assertSubtract();
	cout << "TESTS FINISHED ON Point CLASS.\n"<<endl;

	cout << "RUNNING TESTS ON Normal CLASS..." << endl;
	NormalTest::assertEmptyConstructor();
	NormalTest::assertConstructor();
	NormalTest::assertAdd();
	NormalTest::assertSubtract();
	cout << "TESTS FINISHED ON Normal CLASS.\n"<<endl;*/

	cout <<"CHECKING MATRIX METHODS.\n"<<endl;
	Matrix identity;
	cout<<"Creating Identity Matrix\n"<<endl;
	identity.mat[0][0] = 1.0f;
	identity.mat[1][1] = 1.0f;
	identity.mat[2][2] = 1.0f;
	identity.mat[3][3] = 1.0f;

	identity.printMatrix();

	cout<<"Multiplying Identity by 3.\n"<<endl;
	Matrix mul = identity*3.0f;
	mul.printMatrix();

	cout<<"Creating random Matrix\n"<<endl;
	Matrix random;
	random.mat[0][0] = 5.0f;
	random.mat[0][1] = 4.0f;
	random.mat[0][2] = 1.0f;
	random.mat[1][1] = -7.0f;
	random.mat[1][2] = 5.0f;
	random.mat[1][3] = 8.0f;
	random.mat[2][0] = 12.0f;
	random.mat[2][2] = 3.0f;
	random.mat[2][3] = -9.0f;
	random.mat[3][0] = -3.0f;
	random.mat[3][3] = 1.0f;

	random.printMatrix();

	cout<<"Creating Inverse of Matrix\n"<<endl;
	Matrix inv = random.inverse();
	inv.printMatrix();

	cout<<"Multiplying Identity by Random\n"<<endl;
	Matrix result = Matrix::matMult(identity, random);
	result.printMatrix();
	cout<<"Multiplying two Matrices\n"<<endl;
	identity.mat[2][3] = 4.0;
	identity.mat[1][3] = 3.0;
	cout<<"Identity is now: \n"<<endl;
	identity.printMatrix();


	cout<<"\n\n"<<endl;
	result = Matrix::matMult(identity, random);
	result.printMatrix();

	cout<<"Switching order of multiplicants\n\n"<<endl;

	result = Matrix::matMult(random, identity);
	result.printMatrix();
}