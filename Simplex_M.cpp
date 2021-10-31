// Simplex_M.cpp//simplex
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

#define Limit 3                           //limit of fnction
int Lola_R = 0;                           //row of Lola
int Lola_C = 0;                           //column of Lola
int RHS = 0;                              //Right Hand Side
int First_Friend = 0;                     //The row that is up or down of Lola
int Second_Friend = 0;                    //The row that is up or down of Lola
int First_Child_Friend = 0;              //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int Second_Child_Friend = 0;             //-+-+- +-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int thirdChildFriend = 0;                //-+-+- +-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int fourthChildFriend = 0;               //-+-+- +-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int fifthChildFriend = 0;                //-+-+- +-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int MAX = 0;                              //MAX Function 
int Min = 0;                              //min Function
int L = 0, R = 0, V = 0, Q = 0;
char BaseVar[3][2];
int key = 1;

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
float insert() {
	gotoxy(0, 0);
	float num;
	cin >> num;
	return num;
}
bool CheckRHS(float rhs, float lo) {
	if (lo == 0)return false;
	else if ((rhs / lo) <= 0)return false;
	else return true;
}

class Simplex_M {//for MAx 3
	float lola, grid[3][4] = { 0 }, limit[3][3] = { 0 }, R_[3][2] = { 0 };
	double z[18] = { 0 };
	int j, i;
	//RHS, First_Friend, Second_Frirnd, First_Child_Friend, Second_Child_Friend
	const int address00[8] = { 3,1,2,1,2,0,1,2 };//lola is 0,0
	const int address01[8] = { 3,1,2,0,2,0,1,2 };//lola is 0,1
	const int address02[8] = { 3,1,2,0,1,0,1,2 };//lola is 0,2
	const int address03[8] = { 3,1,2,0,1,2,1,2 };//lola is 0,3
	const int address04[8] = { 3,1,2,0,1,2,0,2 };//lola is 0,4
	const int address05[8] = { 3,1,2,0,1,2,0,1 };//lola is 0,5

	const int address10[8] = { 3,0,2,1,2,0,1,2 };//lola is 1,0
	const int address11[8] = { 3,0,2,0,2,0,1,2 };//lola is 1,1
	const int address12[8] = { 3,0,2,0,1,0,1,2 };//lola is 1,2
	const int address13[8] = { 3,0,2,0,1,2,1,2 };//lola is 1,3
	const int address14[8] = { 3,0,2,0,1,2,0,2 };//lola is 1,4
	const int address15[8] = { 3,0,2,0,1,2,0,1 };//lola is 1,5

	const int address20[8] = { 3,0,1,1,2,0,1,2 };//lola is 2,0
	const int address21[8] = { 3,0,1,0,2,0,1,2 };//lola is 2,1
	const int address22[8] = { 3,0,1,0,1,0,1,2 };//lola is 2,2
	const int address23[8] = { 3,0,1,0,1,2,1,2 };//lola is 2,3
	const int address24[8] = { 3,0,1,0,1,2,0,2 };//lola is 2,4
	const int address25[8] = { 3,0,1,0,1,2,0,1 };//lola is 2,5
public:
	void find_min_target_M() {
		int temp;
		int M = 1000;
		int Z[6] = { 0 };
		for (int i = 0; i < (V + L); i++) {
			Z[i] = z[2 * i] * M + z[2 * i + 1];
		}
		//////////
		double valu = Z[0];
		temp = 0;
		for (int i = 1; i < (V + L); i++) {
			if (Z[i] < valu) {
				valu = Z[i];
				temp = i;
			}
		}
		//set lola column
		Lola_C = temp;
	}
	void find_MAX_target_M() {
		int temp;
		int M = 1000;
		int Z[6] = { 0 };
		for (int i = 0; i < (V + L); i++) {
			Z[i] = z[2 * i] * M + z[2 * i + 1];
		}
		//////////
		double valu = Z[0];
		temp = 0;
		for (int i = 1; i < (V + L); i++) {
			if (Z[i] > valu) {
				valu = Z[i];
				temp = i;
			}
		}
		//set lola column
		Lola_C = temp;
	}
	void find_min_RHS() {
		int temp;
		float _RHS[3];
		_RHS[0] = 9999;
		_RHS[1] = 9999;
		_RHS[2] = 9999;
		if (Lola_C < V) {
			if (CheckRHS(grid[0][3], grid[0][Lola_C]))_RHS[0] = grid[0][3] / grid[0][Lola_C];
			if (CheckRHS(grid[1][3], grid[1][Lola_C]))_RHS[1] = grid[1][3] / grid[1][Lola_C];
			if (Q == 3) {
				if (CheckRHS(grid[2][3], grid[2][Lola_C]))_RHS[2] = grid[2][3] / grid[2][Lola_C];
				if (_RHS[0] == 9999 && _RHS[1] == 9999 && _RHS[2] == 9999) {
					cout << "\n\n******ERROR! All RHS Are Smaller Than Zero!******\n";
					exit(0);
				}
			}
			else if (_RHS[0] == 9999 && _RHS[1] == 9999) {
				cout << "\n\n******ERROR! All RHS Are Smaller Than Zero!******\n";
				exit(0);
			}
		}
		else if (Lola_C >= V) {
			 if (CheckRHS(grid[0][3], limit[0][Lola_C - 3]))_RHS[0] = grid[0][3] / limit[0][Lola_C - 3];
			 if (CheckRHS(grid[1][3], limit[1][Lola_C - 3]))_RHS[1] = grid[1][3] / limit[1][Lola_C - 3];
			 if (Q == 3) {
				 if (CheckRHS(grid[2][3], limit[2][Lola_C - 3]))_RHS[2] = grid[2][3] / limit[2][Lola_C - 3];
				 if (_RHS[0] == 9999 && _RHS[1] == 9999 && _RHS[2] == 9999) {
					 cout << "\n\n******ERROR! All RHS Are Smaller Than Zero!******\n";
					 exit(0);
				 }
			 }
			 else if (_RHS[0] == 9999 && _RHS[1] == 9999) {
				 cout << "\n\n******ERROR! All RHS Are Smaller Than Zero!******\n";
				 exit(0);
			 }
		}

		temp = _RHS[0] <= _RHS[1] ? 0 : 1;
		if (Q == 3) {
			if (temp)
				temp = _RHS[1] <= _RHS[2] ? 1 : 2;

			else temp = _RHS[1] <= _RHS[2] ? 0 : 2;
		}
		Lola_R = temp;
	}
	void set_address() {
		find_lola();
		//Lola_R is 0
		if (Lola_R == 0 && Lola_C == 0) {
			RHS = address00[0];
			First_Friend = address00[1];
			Second_Friend = address00[2];
			First_Child_Friend = address00[3];
			Second_Child_Friend = address00[4];
			thirdChildFriend = address00[5];
			fourthChildFriend = address00[6];
			fifthChildFriend = address00[7];
		}
		if (Lola_R == 0 && Lola_C == 1) {
			RHS = address01[0];
			First_Friend = address01[1];
			Second_Friend = address01[2];
			First_Child_Friend = address01[3];
			Second_Child_Friend = address01[4];
			thirdChildFriend = address01[5];
			fourthChildFriend = address01[6];
			fifthChildFriend = address01[7];
		}
		if (Lola_R == 0 && Lola_C == 2) {
			RHS = address02[0];
			First_Friend = address02[1];
			Second_Friend = address02[2];
			First_Child_Friend = address02[3];
			Second_Child_Friend = address02[4];
			thirdChildFriend = address02[5];
			fourthChildFriend = address02[6];
			fifthChildFriend = address02[7];
		}
		if (Lola_R == 0 && Lola_C == 3) {
			RHS = address03[0];
			First_Friend = address03[1];
			Second_Friend = address03[2];
			First_Child_Friend = address03[3];
			Second_Child_Friend = address03[4];
			thirdChildFriend = address03[5];
			fourthChildFriend = address03[6];
			fifthChildFriend = address03[7];
		}
		if (Lola_R == 0 && Lola_C == 4) {
			RHS = address04[0];
			First_Friend = address04[1];
			Second_Friend = address04[2];
			First_Child_Friend = address04[3];
			Second_Child_Friend = address04[4];
			thirdChildFriend = address04[5];
			fourthChildFriend = address04[6];
			fifthChildFriend = address04[7];
		}
		if (Lola_R == 0 && Lola_C == 5) {
			RHS = address05[0];
			First_Friend = address05[1];
			Second_Friend = address05[2];
			First_Child_Friend = address05[3];
			Second_Child_Friend = address05[4];
			thirdChildFriend = address05[5];
			fourthChildFriend = address05[6];
			fifthChildFriend = address05[7];
		}
		//Lola_R is 1
		if (Lola_R == 1 && Lola_C == 0) {
			RHS = address10[0];
			First_Friend = address10[1];
			Second_Friend = address10[2];
			First_Child_Friend = address10[3];
			Second_Child_Friend = address10[4];
			thirdChildFriend = address10[5];
			fourthChildFriend = address10[6];
			fifthChildFriend = address10[7];
		}
		if (Lola_R == 1 && Lola_C == 1) {
			RHS = address11[0];
			First_Friend = address11[1];
			Second_Friend = address11[2];
			First_Child_Friend = address11[3];
			Second_Child_Friend = address11[4];
			thirdChildFriend = address11[5];
			fourthChildFriend = address11[6];
			fifthChildFriend = address11[7];
		}
		if (Lola_R == 1 && Lola_C == 2) {
			RHS = address12[0];
			First_Friend = address12[1];
			Second_Friend = address12[2];
			First_Child_Friend = address12[3];
			Second_Child_Friend = address12[4];
			thirdChildFriend = address12[5];
			fourthChildFriend = address12[6];
			fifthChildFriend = address12[7];
		}
		if (Lola_R == 1 && Lola_C == 3) {
			RHS = address13[0];
			First_Friend = address13[1];
			Second_Friend = address13[2];
			First_Child_Friend = address13[3];
			Second_Child_Friend = address13[4];
			thirdChildFriend = address13[5];
			fourthChildFriend = address13[6];
			fifthChildFriend = address13[7];
		}
		if (Lola_R == 1 && Lola_C == 4) {
			RHS = address14[0];
			First_Friend = address14[1];
			Second_Friend = address14[2];
			First_Child_Friend = address14[3];
			Second_Child_Friend = address14[4];
			thirdChildFriend = address14[5];
			fourthChildFriend = address14[6];
			fifthChildFriend = address14[7];
		}
		if (Lola_R == 1 && Lola_C == 5) {
			RHS = address15[0];
			First_Friend = address15[1];
			Second_Friend = address15[2];
			First_Child_Friend = address15[3];
			Second_Child_Friend = address15[4];
			thirdChildFriend = address15[5];
			fourthChildFriend = address15[6];
			fifthChildFriend = address15[7];
		}
		//Lola_R is 2
		if (Lola_R == 2 && Lola_C == 0) {
			RHS = address20[0];
			First_Friend = address20[1];
			Second_Friend = address20[2];
			First_Child_Friend = address20[3];
			Second_Child_Friend = address20[4];
			thirdChildFriend = address20[5];
			fourthChildFriend = address20[6];
			fifthChildFriend = address20[7];
		}
		if (Lola_R == 2 && Lola_C == 1) {
			RHS = address21[0];
			First_Friend = address21[1];
			Second_Friend = address21[2];
			First_Child_Friend = address21[3];
			Second_Child_Friend = address21[4];
			thirdChildFriend = address21[5];
			fourthChildFriend = address21[6];
			fifthChildFriend = address21[7];
		}
		if (Lola_R == 2 && Lola_C == 2) {
			RHS = address22[0];
			First_Friend = address22[1];
			Second_Friend = address22[2];
			First_Child_Friend = address22[3];
			Second_Child_Friend = address22[4];
			thirdChildFriend = address22[5];
			fourthChildFriend = address22[6];
			fifthChildFriend = address22[7];
		}
		if (Lola_R == 2 && Lola_C == 3) {
			RHS = address23[0];
			First_Friend = address23[1];
			Second_Friend = address23[2];
			First_Child_Friend = address23[3];
			Second_Child_Friend = address23[4];
			thirdChildFriend = address23[5];
			fourthChildFriend = address23[6];
			fifthChildFriend = address23[7];
		}
		if (Lola_R == 2 && Lola_C == 4) {
			RHS = address24[0];
			First_Friend = address24[1];
			Second_Friend = address24[2];
			First_Child_Friend = address24[3];
			Second_Child_Friend = address24[4];
			thirdChildFriend = address24[5];
			fourthChildFriend = address24[6];
			fifthChildFriend = address24[7];
		}
		if (Lola_R == 2 && Lola_C == 5) {
			RHS = address25[0];
			First_Friend = address25[1];
			Second_Friend = address25[2];
			First_Child_Friend = address25[3];
			Second_Child_Friend = address25[4];
			thirdChildFriend = address25[5];
			fourthChildFriend = address25[6];
			fifthChildFriend = address25[7];
		}
	}
	void eval_z() {
		///////////////////////////////////////////////////////////////////////First Child Friend
		z[First_Child_Friend * 2] = -(z[Lola_C * 2] / lola) *
			grid[Lola_R][First_Child_Friend] + z[First_Child_Friend * 2];

		z[First_Child_Friend * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
			grid[Lola_R][First_Child_Friend] + z[First_Child_Friend * 2 + 1];

		//////////////////////////////////////////////////////////////////////Second Child Friend
		if (V == 3) {
			z[Second_Child_Friend * 2] = -(z[Lola_C * 2] / lola) *
				grid[Lola_R][Second_Child_Friend] + z[Second_Child_Friend * 2];

			z[Second_Child_Friend * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
				grid[Lola_R][Second_Child_Friend] + z[Second_Child_Friend * 2 + 1];
		}
		///////////////////////////////////////////////////////////////////////Third Child Friend
		if (Lola_C < 3) {//Lola_C < 3 limit
			z[(thirdChildFriend + V) * 2] = -(z[Lola_C * 2] / lola) *
				limit[Lola_R][thirdChildFriend] + z[(thirdChildFriend + V) * 2];

			z[(thirdChildFriend + V) * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
				limit[Lola_R][thirdChildFriend] + z[(thirdChildFriend + V) * 2 + 1];
		}
		if (Lola_C > 2) {//Lola_C > 2 grid
			z[thirdChildFriend * 2] = -(z[Lola_C * 2] / lola) *
				grid[Lola_R][thirdChildFriend] + z[thirdChildFriend * 2];

			z[thirdChildFriend * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
				grid[Lola_R][thirdChildFriend] + z[thirdChildFriend * 2 + 1];
		}
		///////////////////////////////////////////////////////////////////////Fourth Child Friend

		z[(fourthChildFriend + V) * 2] = -(z[Lola_C * 2] / lola) *
			limit[Lola_R][fourthChildFriend] + z[(fourthChildFriend + V) * 2];

		z[(fourthChildFriend + V) * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
			limit[Lola_R][fourthChildFriend] + z[(fourthChildFriend + V) * 2 + 1];

		///////////////////////////////////////////////////////////////////////Fifth Child Friend
		if (L == 3) {
			z[(fifthChildFriend + V) * 2] = -(z[Lola_C * 2] / lola) *
				limit[Lola_R][fifthChildFriend] + z[(fifthChildFriend + V) * 2];

			z[(fifthChildFriend + V) * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) *
				limit[Lola_R][fifthChildFriend] + z[(fifthChildFriend + V) * 2 + 1];
		}
		/////////////////////////////////////////////////////////RHS
		z[(V + L + R) * 2] = -(z[Lola_C * 2] / lola) * grid[Lola_R][3] + z[(V + L + R) * 2];
		z[(V + L + R) * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) * grid[Lola_R][3] + z[(V + L + R) * 2 + 1];
	}
	void eval_R() {
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Lola_C > 2) {//Lola_C > 2 limit

			R_[First_Friend][0] = -(limit[First_Friend][Lola_C - 3] / lola) * R_[Lola_R][0] + R_[First_Friend][0];
			R_[Second_Friend][0] = -(limit[Second_Friend][Lola_C - 3] / lola) * R_[Lola_R][0] + R_[Second_Friend][0];

			if (R == 2) {
				R_[First_Friend][1] = -(limit[First_Friend][Lola_C - 3] / lola) * R_[Lola_R][1] + R_[First_Friend][1];
				R_[Second_Friend][1] = -(limit[Second_Friend][Lola_C - 3] / lola) * R_[Lola_R][1] + R_[Second_Friend][1];
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Lola_C < 3) {//Lola_C < 3 grid
			R_[First_Friend][0] = -(grid[First_Friend][Lola_C] / lola) * R_[Lola_R][0] + R_[First_Friend][0];
			R_[Second_Friend][0] = -(grid[Second_Friend][Lola_C] / lola) * R_[Lola_R][0] + R_[Second_Friend][0];

			if (R == 2)
				R_[First_Friend][1] = -(grid[First_Friend][Lola_C] / lola) * R_[Lola_R][1] + R_[First_Friend][1];
			R_[Second_Friend][1] = -(grid[Second_Friend][Lola_C] / lola) * R_[Lola_R][1] + R_[Second_Friend][1];
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (j = V + L; j < (V + L + R); j++)
			z[j * 2] = -(z[Lola_C * 2] / lola) * R_[Lola_R][j - (V + L)] + z[j * 2];

		for (j = V + L; j < (V + L + R); j++)
			z[j * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) * R_[Lola_R][j - (V + L)] + z[j * 2 + 1];
	}
	void eval_limit() {
		if (Lola_C < 3) {
			for (j = 0; j < Limit; j++)
				limit[First_Friend][j] = -(grid[First_Friend][Lola_C] / lola) * limit[Lola_R][j] + limit[First_Friend][j];
			for (j = 0; j < Limit; j++)
				limit[Second_Friend][j] = -(grid[Second_Friend][Lola_C] / lola) * limit[Lola_R][j] + limit[Second_Friend][j];
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Lola_C > 2) {
			for (j = 0; j < Limit; j++)
				limit[First_Friend][j] = -(limit[First_Friend][Lola_C - 3] / lola) * limit[Lola_R][j] + limit[First_Friend][j];
			for (j = 0; j < Limit; j++)
				limit[Second_Friend][j] = -(limit[Second_Friend][Lola_C - 3] / lola) * limit[Lola_R][j] + limit[Second_Friend][j];
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (j = V; j < V + 2; j++)
			z[j * 2] = -(z[Lola_C * 2] / lola) * limit[Lola_R][j - V] + z[j * 2];

		for (j = V; j < V + 2; j++)
			z[j * 2 + 1] = -(z[Lola_C * 2 + 1] / lola) * limit[Lola_R][j - V] + z[j * 2 + 1];
		/////////////////////////////////////////////////////////////////////////////////////
		for (j = 0; j < Limit; j++)//must be in the last of funtion
			limit[Lola_R][j] = limit[Lola_R][j] / lola;
	}
	void eval_simplex() {

		////////////////////////////////////////////////////////////////////////////////////////
		if (Lola_C < 3) {
			grid[First_Friend][First_Child_Friend] = -(grid[First_Friend][Lola_C] / lola) *
				grid[Lola_R][First_Child_Friend] + grid[First_Friend][First_Child_Friend];

			grid[First_Friend][Second_Child_Friend] = -(grid[First_Friend][Lola_C] / lola) *
				grid[Lola_R][Second_Child_Friend] + grid[First_Friend][Second_Child_Friend];

			limit[First_Friend][thirdChildFriend] = -(grid[First_Friend][Lola_C] / lola) *
				limit[Lola_R][thirdChildFriend] + limit[First_Friend][thirdChildFriend];

			limit[First_Friend][fourthChildFriend] = -(grid[First_Friend][Lola_C] / lola) *
				limit[Lola_R][fourthChildFriend] + limit[First_Friend][fourthChildFriend];

			limit[First_Friend][fifthChildFriend] = -(grid[First_Friend][Lola_C] / lola) *
				limit[Lola_R][fifthChildFriend] + limit[First_Friend][fifthChildFriend];

			grid[First_Friend][RHS] = -(grid[First_Friend][Lola_C] / lola) * grid[Lola_R][RHS] + grid[First_Friend][RHS];
			/////////////////////////////////////////////////**///////////////////////////////////////////////////////////////////
			grid[Second_Friend][First_Child_Friend] = -(grid[Second_Friend][Lola_C] / lola) *
				grid[Lola_R][First_Child_Friend] + grid[Second_Friend][First_Child_Friend];

			grid[Second_Friend][Second_Child_Friend] = -(grid[Second_Friend][Lola_C] / lola) *
				grid[Lola_R][Second_Child_Friend] + grid[Second_Friend][Second_Child_Friend];

			limit[Second_Friend][thirdChildFriend] = -(grid[Second_Friend][Lola_C] / lola) *
				limit[Lola_R][thirdChildFriend] + limit[Second_Friend][thirdChildFriend];

			limit[Second_Friend][fourthChildFriend] = -(grid[Second_Friend][Lola_C] / lola) *
				limit[Lola_R][fourthChildFriend] + limit[Second_Friend][fourthChildFriend];

			limit[Second_Friend][fifthChildFriend] = -(grid[Second_Friend][Lola_C] / lola) *
				limit[Lola_R][fifthChildFriend] + limit[Second_Friend][fifthChildFriend];

			grid[Second_Friend][RHS] = -(grid[Second_Friend][Lola_C] / lola) * grid[Lola_R][RHS] + grid[Second_Friend][RHS];
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (Lola_C > 2) {
			grid[First_Friend][First_Child_Friend] = -(limit[First_Friend][Lola_C - 3] / lola) *
				grid[Lola_R][First_Child_Friend] + grid[First_Friend][First_Child_Friend];

			grid[First_Friend][Second_Child_Friend] = -(limit[First_Friend][Lola_C - 3] / lola) *
				grid[Lola_R][Second_Child_Friend] + grid[First_Friend][Second_Child_Friend];

			grid[First_Friend][thirdChildFriend] = -(limit[First_Friend][Lola_C - 3] / lola) *
				grid[Lola_R][thirdChildFriend] + grid[First_Friend][thirdChildFriend];

			limit[First_Friend][fourthChildFriend] = -(limit[First_Friend][Lola_C - 3] / lola) *
				limit[Lola_R][fourthChildFriend] + limit[First_Friend][fourthChildFriend];

			limit[First_Friend][fifthChildFriend] = -(limit[First_Friend][Lola_C - 3] / lola) *
				limit[Lola_R][fifthChildFriend] + limit[First_Friend][fifthChildFriend];

			grid[First_Friend][RHS] = -(limit[First_Friend][Lola_C - 3] / lola) * grid[Lola_R][RHS] + grid[First_Friend][RHS];
			/////////////////////////////////////////////////**///////////////////////////////////////////////////////////////////
			grid[Second_Friend][First_Child_Friend] = -(limit[Second_Friend][Lola_C - 3] / lola) *
				grid[Lola_R][First_Child_Friend] + grid[Second_Friend][First_Child_Friend];

			grid[Second_Friend][Second_Child_Friend] = -(limit[Second_Friend][Lola_C - 3] / lola) *
				grid[Lola_R][Second_Child_Friend] + grid[Second_Friend][Second_Child_Friend];

			grid[Second_Friend][thirdChildFriend] = -(limit[Second_Friend][Lola_C - 3] / lola) *
				limit[Lola_R][thirdChildFriend] + grid[Second_Friend][thirdChildFriend];

			limit[Second_Friend][fourthChildFriend] = -(limit[Second_Friend][Lola_C - 3] / lola) *
				limit[Lola_R][fourthChildFriend] + limit[Second_Friend][fourthChildFriend];

			limit[Second_Friend][fifthChildFriend] = -(limit[Second_Friend][Lola_C - 3] / lola) *
				limit[Lola_R][fifthChildFriend] + limit[Second_Friend][fifthChildFriend];

			grid[Second_Friend][RHS] = -(limit[Second_Friend][Lola_C - 3] / lola) * grid[Lola_R][RHS] + grid[Second_Friend][RHS];
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		eval_z();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//eval_limit();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		eval_R();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for (j = 0; j < 3; j++) {
			grid[Lola_R][j] = grid[Lola_R][j] / lola;
			limit[Lola_R][j] = limit[Lola_R][j] / lola;
		}

		for (j = 0; j < R; j++)
			R_[Lola_R][j] = R_[Lola_R][j] / lola;

		grid[Lola_R][RHS] = grid[Lola_R][RHS] / lola;
		//******************************************************************************************
		if (Lola_C < 3) {
			for (i = 0; i < 3; i++)
				grid[i][Lola_C] = 0;
		}
		if (Lola_C > 2) {
			for (i = 0; i < 3; i++)
				limit[i][Lola_C - 3] = 0;
		}

		z[Lola_C * 2] = z[Lola_C * 2 + 1] = 0;

		if (Lola_C < 3)
			grid[Lola_R][Lola_C] = 1;

		if (Lola_C > 2)
			limit[Lola_R][Lola_C - 3] = 1;
		//end*********************************************************************
	}
	bool find_lola() {
		if (MAX)find_min_target_M();
		if (Min)find_MAX_target_M();
		////////////////////////////
		find_min_RHS();
		if (Lola_C < 3)
			lola = grid[Lola_R][Lola_C];
		else if (Lola_C > 2)
			lola = limit[Lola_R][Lola_C - 3];
		return true;
	}
	void set_M() {
		for (int i = 0; i < Q; i++) {
			if (R_[i][0] == 1) {
				for (int j = 0; j < V; j++)
					z[j * 2] = z[j * 2] + grid[i][j] * z[(V + L) * 2];
				for (int j = 0; j < L; j++)
					z[(j + V) * 2] = z[(j + V) * 2] + limit[i][j] * z[(V + L) * 2];
				z[(V + L + R) * 2] = z[(V + L + R) * 2] + grid[i][3] * z[(V + L) * 2];
			}
		}
		z[(V + L) * 2] = 0;
		if (R == 2) {
			for (int i = 0; i < Q; i++) {
				if (R_[i][1] == 1) {
					for (int j = 0; j < V; j++)
						z[j * 2] = z[j * 2] + grid[i][j] * z[(V + L) * 2 + 2];
					for (int j = 0; j < L; j++)
						z[(j + V) * 2] = z[(j + V) * 2] + limit[i][j] * z[(V + L) * 2 + 2];
					z[(V + L + R) * 2] = z[(V + L + R) * 2] + grid[i][3] * z[(V + L) * 2 + 2];
				}
			}
			z[(V + L) * 2 + 2] = 0;
		}
	}
	void set_grid() {
		for (int i = 0; i < 4; i++)
			switch (i)
			{
			case 0:for (int j = 0; j < Q + 2; j++) {
				gotoxy(40, 5 + j);
				for (int k = 0; k < V; k++) {
					if (j == 0) cout << "|x" << k + 1 << " ";
					else cout << "|   ";
				}
			}
				  break;
			case 1:for (int j = 0; j < Q + 2; j++) {
				gotoxy(40 + 4 * V, 5 + j);
				for (int k = 0; k < L; k++) {
					if (j == 0) cout << "|S" << k + 1 << " ";
					else cout << "|   ";
				}
			}
				  break;
			case 2:for (int j = 0; j < Q + 2; j++) {
				gotoxy(40 + 4 * (V + L), 5 + j);
				for (int k = 0; k < R; k++) {
					if (j == 0) cout << "|R" << k + 1 << " ";
					else cout << "|   ";
				}
			}
				  break;
			case 3:for (int j = 0; j < Q + 2; j++) {
				gotoxy(40 + 4 * (V + L + R), 5 + j);
				if (j == 0) cout << "|RHS";
				else cout << "|   ";
			}
				  break;
			default:
				break;
			}

		for (int i = 0; i < 5; i++)
			switch (i)
			{
			case 0:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < V; k++) {
					gotoxy(41 + (k * 4), 6 + j);
					cout << "?";
					grid[j][k] = insert();
					gotoxy(41 + (k * 4), 6 + j);
					cout << grid[j][k];
				}
			}
				  break;
			case 1:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < L; k++) {
					gotoxy(41 + 4 * V + 4 * k, 6 + j);
					cout << "?";
					limit[j][k] = insert();
					gotoxy(41 + 4 * V + 4 * k, 6 + j);
					cout << limit[j][k];
					if (limit[j][k] == 1) { gotoxy(38, 6 + j); cout << "S" << k + 1; }
				}
			}
				  break;
			case 2:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < R; k++) {
					gotoxy(41 + 4 * (V + L) + 4 * k, 6 + j);
					cout << "?";
					R_[j][k] = insert();
					gotoxy(41 + 4 * (V + L) + 4 * k, 6 + j);
					cout << R_[j][k];
					if (R_[j][k] == 1) { gotoxy(38, 6 + j); cout << "R" << k + 1; }
				}
			}
				  break;
			case 3:for (int j = 0; j < Q; j++) {
				gotoxy(41 + 4 * (V + L + R), 6 + j);
				cout << "?";
				grid[j][3] = insert();
				gotoxy(41 + 4 * (V + L + R), 6 + j);
				cout << grid[j][3];
			}
				  break;
			case 4:gotoxy(39, Q + 6); cout << "Z";
				for (int k = 0; k < 4; k++)
					switch (k)
					{
					case 0:for (int j = 0; j < V; j++) {
						gotoxy(41 + j * 4, Q + 6);
						cout << "?";
						z[j * 2 + 1] = insert();
						gotoxy(41 + j * 4, Q + 6);
						cout << z[j * 2 + 1];
					}
						  break;
					case 1:for (int j = 0; j < L; j++) {
						gotoxy(41 + (j + V) * 4, Q + 6);
						cout << "?";
						z[(j + V) * 2 + 1] = insert();
						gotoxy(41 + (j + V) * 4, Q + 6);
						cout << z[(j + V) * 2 + 1];
					}
						  break;
					case 2:for (int j = 0; j < R; j++) {
						gotoxy(41 + (V + L + j) * 4, Q + 6);
						cout << "?";
						z[(j + V + L) * 2] = insert();
						gotoxy(41 + (V + L + j) * 4, Q + 6);
						cout << z[(j + V + L) * 2];
					}
						  break;
					case 3:
						gotoxy(41 + (V + L + R) * 4, Q + 6);
						cout << "?";
						z[(V + L + R) * 2 + 1] = insert();
						gotoxy(41 + (V + L + R) * 4, Q + 6);
						cout << z[(V + L + R) * 2 + 1];
						break;
					default:
						break;
					}
				break;
			default:
				break;
			}
		//////////////////Limit
		for (int i = 0; i < Q; i++) {
			for (int j = 0; j < L; j++)
				if (limit[i][j] == 1) {
					BaseVar[i][0] = 'S';
					BaseVar[i][1] = (char)j + 49;
				}
		}
		////////////////////////////////R
		for (int i = 0; i < Q; i++) {
			for (int j = 0; j < R; j++)
				if (R_[i][j] == 1) {
					BaseVar[i][0] = 'R';
					BaseVar[i][1] = (char)j + 49;
				}
		}
	}
	void PrintBaseVaribles() {
		///////////////////////////////Xi
		if (!key) {
			BaseVar[Lola_R][0] = 'X';
			BaseVar[Lola_R][1] = (char)Lola_C + 49;
		}
		key = 0;
		/////////////////////////////////
		for (int i = 0; i < Q; i++) {
			gotoxy(28, i + 6);
			cout << BaseVar[i][0] << BaseVar[i][1];
		}
	}
	void display() {
		for (int i = 0; i < 4; i++)
			switch (i)
			{
			case 0:for (int j = 0; j <= Q + 1; j++) {
				for (int k = 0; k < V; k++) {
					gotoxy(30 + k * 10, 5 + j);
					if (j == 0) cout << "|   x" << k + 1;
					else cout << "|";
				}
			}
				  break;
			case 1:for (int j = 0; j <= Q + 1; j++) {
				for (int k = 0; k < L; k++) {
					gotoxy(30 + (k + V) * 10, 5 + j);
					if (j == 0) cout << "|   S" << k + 1;
					else cout << "|";
				}
			}
				  break;
			case 2:for (int j = 0; j <= Q + 1; j++) {
				for (int k = 0; k < R; k++) {
					gotoxy(30 + 10 * (V + L + k), 5 + j);
					if (j == 0) cout << "|   R" << k + 1;
					else cout << "|";
				}
			}
				  break;
			case 3:for (int j = 0; j <= Q + 1; j++) {
				gotoxy(30 + 10 * (V + L + R), 5 + j);
				if (j == 0) cout << "|   RHS";
				else cout << "|";
			}
				  break;
			default:
				break;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 5; i++)
			switch (i)
			{
			case 0:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < V; k++) {
					gotoxy(31 + k * 10, 6 + j);
					cout << grid[j][k];
				}
			}
				  break;
			case 1:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < L; k++) {
					gotoxy(31 + (k + V) * 10, 6 + j);
					cout << limit[j][k];
				}
			}
				  break;
			case 2:for (int j = 0; j < Q; j++) {
				for (int k = 0; k < R; k++) {
					gotoxy(31 + 10 * (V + L + k), 6 + j);
					cout << R_[j][k];
				}
			}
				  break;
			case 3:for (int j = 0; j < Q; j++) {
				gotoxy(31 + 10 * (V + L + R), 6 + j);
				cout << grid[j][3];
			}
				  break;
			case 4:gotoxy(29, Q + 6); cout << "Z";
				for (int k = 0; k < 4; k++)
					switch (k)
					{
					case 0:for (int j = 0; j < V; j++) {
						gotoxy(31 + j * 10, Q + 6);
						if (z[2 * j]) {
							printf("%2.1fM", z[2 * j]);
							if (z[j * 2 + 1] >= 0)
								cout << "+";
						}
						printf("%2.1f", z[j * 2 + 1]);
					}
						  break;
					case 1:for (int j = 0; j < L; j++) {
						gotoxy(31 + (j + V) * 10, Q + 6);
						if (z[(j + V) * 2]) {
							printf("%2.1fM", z[(j + V) * 2]);
							if (z[(j + V) * 2 + 1] >= 0)
								cout << "+";
						}
						printf("%2.1f", z[(j + V) * 2 + 1]);
					}
						  break;
					case 2:for (int j = 0; j < R; j++) {
						gotoxy(31 + (V + L + j) * 10, Q + 6);
						if (z[(j + V + L) * 2]) {
							printf("%2.1fM", z[(j + V + L) * 2]);
							if (z[(j + V + L) * 2 + 1] >= 0)
								cout << "+";
						}
						printf("%2.1f", z[(j + V + L) * 2 + 1]);
					}
						  break;
					case 3:
						gotoxy(31 + (V + L + R) * 10, Q + 6);
						if (z[(V + L + R) * 2]) {
							printf("%2.1fM", z[(V + L + R) * 2]);
							if (z[(V + L + R) * 2 + 1] >= 0)
								cout << "+";
						}
						printf("%2.1f", z[(V + L + R) * 2 + 1]);
						break;
					default:
						break;
					}
				break;
			}
	}
	bool Menu() {
		set_grid();
		system("cls");
		set_M();
		display();
		PrintBaseVaribles();
		_getch();
	Agian:	if (!find_lola())return false;
		set_address();
		eval_simplex();
		system("cls");
		display();
		PrintBaseVaribles();
		gotoxy(0, 10);
		cout << "\nFor See The Next Solution Grid Press Enter\nPress \"ESC\" For Exit";
		if (_getch() == 27)
			return true;
		else goto Agian;
	}
};


int main()
{
	int H;
	Simplex_M simplex;
	cout << "\nSet The Grid\nFor MAX press 1 For min press 2 : ";
	cin >> H;
	if (H == 1) { MAX = 1; Min = 0; }
	else if (H == 2) { MAX = 0; Min = 1; }
	cout << "\nHow many Adverbs does the function have? (#2 OR #3) : ";
	cin >> H;
	if (H == 2)Q = 2;
	if (H == 3)Q = 3;
	cout << "\nHow many variables does the function have? (#2 OR #3) : ";
	cin >> H;
	if (H == 2)V = 2;
	if (H == 3)V = 3;
	cout << "\nHow many limitions does the function have? (#2 OR #3) : ";
	cin >> H;
	if (H == 2)L = 2;
	if (H == 3)L = 3;
	cout << "\nHow many R does the function have? (#1 OR #2) : ";
	cin >> H;
	if (H == 1)R = 1;
	if (H == 2)R = 2;
	system("cls");
	if (simplex.Menu())cout << "\nSuccessfully Done!" << endl;


	cout << "\n";
	return 0;
}