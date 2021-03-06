//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//----------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//----------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] =
{ "No Ship", "Mine Sweeper", "Submarine", "Frigate",
"Battleship", "Aircraft Carrier" };
const int TOTALPIECES = 17;
// total pieces in all ships

//----------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by:	Mike Farrell, Jared Whitney
// 
// Date:	01/10/17
//
// Version:	1.01
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Calls: deleteMem()
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//		01/10/17 MF & JW completed v 1.02
//
//----------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for (short i = 0; i < NUMPLAYERS; ++i)
		{
			players[i].m_gameGrid[0] = nullptr;
			players[i].m_gameGrid[0] = new Ship*[numberOfRows];
			players[i].m_gameGrid[1] = nullptr;
			players[i].m_gameGrid[1] = new Ship*[numberOfRows];
			for (short j = 0; j < numberOfRows; ++j)
			{
				//-------------------------------------------------
				// set the pointers to NULL, then allocate the
				// memory for each row in each grid
				//--------------------------------------------------
				players[i].m_gameGrid[0][j] = nullptr;
				players[i].m_gameGrid[0][j] = new Ship[numberOfCols];
				players[i].m_gameGrid[1][j] = nullptr;
				players[i].m_gameGrid[1][j] = new Ship[numberOfCols];

				for (short k = 0; k < numberOfCols; ++k)
				{
					players[i].m_gameGrid[0][j][k] = NOSHIP;
					players[i].m_gameGrid[1][j][k] = NOSHIP;
				} // end for k
			} // end for j
		} // end for i
	}
	catch (exception e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}
}

//----------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer: Jared Whitney
// 
// Date:	01/26/17
//
// Version:	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//		01/26/17 JW completed v 1.0
//   
//----------------------------------------------------------------------------
void deleteMem(Player players[], char size)
{
	{
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
		for (short whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			if (players[whichPlayer].m_gameGrid[0] != nullptr)
			{
				for (short j = 0; j < numberOfRows; ++j)
				{
					delete[] players[whichPlayer].m_gameGrid[0][j];
					delete[] players[whichPlayer].m_gameGrid[1][j];
				} // end for j
				delete[] players[whichPlayer].m_gameGrid[0];
				delete[] players[whichPlayer].m_gameGrid[1];
			}
		}
		// be sure to check if the memory was allocated 
		//(!nullptr) BEFORE deleting
	}
}

//----------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
// modified by: Jared Whitney
// 
// Date:	01/26/17
//
// Version:	1.01
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Output:		three characters representing one ship to sout
//
// Calls:	N/A
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB completed v 1.0
//		01/26/17 JW completed v 1.01
//					-removed MISS output and break for MISSED switch
//     
//----------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{
	sout << ' ';
	switch (thisShip)
	{
	case NOSHIP: sout << ' ';
		break;
	case MINESWEEPER: sout << 'M';
		break;
	case SUB: sout << 'S';
		break;
	case FRIGATE: sout << 'F';
		break;
	case BATTLESHIP: sout << 'B';
		break;
	case CARRIER: sout << 'C';
		break;
	case HIT: sout << 'H';
		break;
	case MISSED:
	default: sout << 'X';
	}
	sout << VERT;
}

//----------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer: Paul Bladek
// modified by: Mike Farrell, Jared Whitney
// 
// Date:	01/10/17
//
// Version:	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Output:	a single grid to sout
//
// Calls:	n/a
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//		01/10/17 MF & JW completed v 1.0
//     
//----------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	int timesThrough = 0;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	system("cls");

	for (short j = 1; j <= numberOfCols; ++j)
	{
		if (j == 1)
		{
			sout << setw(4) << j;
		}
		else
		{
			sout << setw(3) << j;
		}
	}
	sout << endl;
	for (short i = 0; i <= numberOfCols; i++)
	{

		if (i == 0)
		{
			sout << HORIZ;
			sout << CL;
		}
		else
		{
			sout << HORIZ << HORIZ;
			sout << CR;
		}
	}
	sout << endl;

	//print rows beginning with char a-j
	int alphaChar = 65;
	for (int i = 0; i < numberOfRows; i++)
	{
		sout << (char)alphaChar++ << VERT;
		//print alpha character at start of every other row

		//print out each cell in the grid.
		for (int l = 0; l < numberOfCols; l++)
		{
			printShip(sout, grid[i][l]);
		}

		//start a new line
		sout << endl;

		//print out the extra horizontal line
		sout << HORIZ << CL;

		// regular line w/ no data
		for (int k = 0; k < numberOfCols; k++)
		{
			sout << HORIZ << HORIZ << CR;
		}

		//start new line
		sout << endl;

	}

}

//----------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_piecesLeft
// Programmer:	Paul Bladek
// modified by: Jared Whitney
// 
// Date:	01/31/17
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB completed v 1.0
//		01/31/17 JW completed v 1.01
//     
//----------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for (short j = 0; j < (SHIP_SIZE_ARRAYSIZE); j++)
		playerPtr->m_ships[j].m_piecesLeft = shipSize[j];

	playerPtr->m_piecesLeft = TOTALPIECES;
}

//----------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek
// modified by:	Mike Farrell, Jared Whitney
// 
// Date:	9/12/06
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main(), getGrid()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB completed v 0.5
//		01/12/17 MF & JW completed v 1.0
//		01/27/17 MF completed v 1.01
//     
//----------------------------------------------------------------------------
void setships(Player players[], char size, short whichPlayer)
{
	char input = 'V';
	char shipOK = 'Y';
	char use_ship = 'Y';
	char ok = 'Y';
	char save = 'N';
	Ship ship_type;
	string use_ship_string;
	Direction orientation;
	ostringstream outSStream;
	Cell location = { 0, 0 };

	for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		do {
			system("cls");
			shipOK = 'Y';
			printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
			use_ship_string = shipNames[j];
			use_ship_string += " ok?";
			use_ship = safeChoice(use_ship_string, 'Y', 'N');
			if (use_ship == 'Y')
			{
				outSStream.str("");
				outSStream << "Player " << whichPlayer + 1 << " Enter "
					<< shipNames[j] << " orientation";
				input = safeChoice(outSStream.str(), 'V', 'H');
				players[whichPlayer].m_ships[j].m_orientation
					= (input == 'V') ? VERTICAL : HORIZONTAL;
				orientation = players[whichPlayer].m_ships[j].m_orientation;
				cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[j] <<
					" bow coordinates <row letter><col #>: ";
				players[whichPlayer].m_ships[j].m_bowLocation = getCoord(cin, size);

				// if ok
				if (!validLocation(players[whichPlayer], j, size))
				{
					cout << "invalid location. Press <enter>";
					cin.get();
					j--; // redo
					continue;
				}



				location = players[whichPlayer].m_ships[j].m_bowLocation;
				ship_type = static_cast<Ship>(j);
				players[whichPlayer].m_gameGrid[0]
					[location.m_row][location.m_col] = ship_type;

				for (int i = 0; i < shipSize[j]; i++)
				{
					if (input == 'V')
					{
						players[whichPlayer].m_gameGrid[0]
							[location.m_row + i][location.m_col] = ship_type;
					}
					else
					{
						players[whichPlayer].m_gameGrid[0]
							[location.m_row][location.m_col + i] = ship_type;
					}
					//i++;
				}
				system("cls");
				printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
				shipOK = safeChoice("Is Ship Position ok?", 'Y', 'N');
				if (shipOK == 'N')
				{
					players[whichPlayer].m_gameGrid[0][location.m_row][location.m_col] = NOSHIP;
					for (int i = 0; i < shipSize[j]; i++)
					{
						if (input == 'V')
						{
							players[whichPlayer].m_gameGrid[0]
								[location.m_row + i][location.m_col] = NOSHIP;
						}
						else
						{
							players[whichPlayer].m_gameGrid[0]
								[location.m_row][location.m_col + i] = NOSHIP;
						}
						//i++;
					}
				}
			}//end of if(use_ship == Y)
			else
			{
				cout << "Not using [" << shipNames[j] << "]. Press <enter> to continue.." << endl;
				cin.get();
			}
		} while (shipOK == 'N');

		players[whichPlayer].m_ships[j].m_name = static_cast<Ship>(j);
		if (use_ship == 'Y')
		{
			players[whichPlayer].m_ships[j].m_piecesLeft = shipSize[j];
		}
		else
		{
			players[whichPlayer].m_ships[j].m_orientation = VERTICAL;
			players[whichPlayer].m_ships[j].m_bowLocation.m_row = -1;
			players[whichPlayer].m_ships[j].m_bowLocation.m_col = -1;
			players[whichPlayer].m_ships[j].m_piecesLeft = 0;
			players[whichPlayer].m_piecesLeft -= shipSize[j];
		}

		/*if (j == 1)
		{
		if (use_ship == 'Y')
		{
		players[whichPlayer].m_ships[j].m_name = MINESWEEPER;
		players[whichPlayer].m_ships[j].m_piecesLeft = 2;
		}
		else
		{
		players[whichPlayer].m_ships[j].m_name = MINESWEEPER;
		players[whichPlayer].m_ships[j].m_piecesLeft = 0;
		players[whichPlayer].m_piecesLeft -= shipSize[j];
		}
		}
		else if (j == 2)
		{
		if (use_ship == 'Y')
		{
		players[whichPlayer].m_ships[j].m_name = SUB;
		players[whichPlayer].m_ships[j].m_piecesLeft = 3;
		}
		else
		{
		players[whichPlayer].m_ships[j].m_name = SUB;
		players[whichPlayer].m_ships[j].m_piecesLeft = 0;
		players[whichPlayer].m_piecesLeft -= shipSize[j];
		}
		}
		else if (j == 3)
		{
		if (use_ship == 'Y')
		{
		players[whichPlayer].m_ships[j].m_name = FRIGATE;
		players[whichPlayer].m_ships[j].m_piecesLeft = 3;
		}
		else
		{
		players[whichPlayer].m_ships[j].m_name = FRIGATE;
		players[whichPlayer].m_ships[j].m_piecesLeft = 0;
		players[whichPlayer].m_piecesLeft -= shipSize[j];
		}
		}
		else if (j == 4)
		{
		if (use_ship == 'Y')
		{
		players[whichPlayer].m_ships[j].m_name = BATTLESHIP;
		players[whichPlayer].m_ships[j].m_piecesLeft = 4;
		}
		else
		{
		players[whichPlayer].m_ships[j].m_name = BATTLESHIP;
		players[whichPlayer].m_ships[j].m_piecesLeft = 0;
		players[whichPlayer].m_piecesLeft -= shipSize[j];
		}
		}
		else if (j == 5)
		{
		if (use_ship == 'Y')
		{
		players[whichPlayer].m_ships[j].m_name = CARRIER;
		players[whichPlayer].m_ships[j].m_piecesLeft = 5;
		}
		else
		{
		players[whichPlayer].m_ships[j].m_name = CARRIER;
		players[whichPlayer].m_ships[j].m_piecesLeft = 0;
		players[whichPlayer].m_piecesLeft -= shipSize[j];
		}
		}*/



	}
	printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if (save == 'Y')
		saveGrid(players, whichPlayer, size);
}

//----------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer: Paul Bladek
// modified by: Jared Whitney
// 
// Date:	01/12/17
//
// Version:	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Output:	grid to specified file
//
// Calls:	n/a
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//		01/12/17 JW completed v 1.0
//     
//----------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	ofstream out_file_handle;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	char which_player;
	which_player = (static_cast<char>(whichPlayer + '0')) + 1;
	char filename[FILENAME_MAX] = "default.txt";
	//filename[7] = which_player;
	cin >> filename;



	out_file_handle.open(filename);
	out_file_handle << (size) << endl;
	for (short i = 1; i < SHIP_SIZE_ARRAYSIZE; i++)
	{
		out_file_handle << players[whichPlayer].m_ships[i].m_orientation <<
			" " << static_cast<char>
			(players[whichPlayer].m_ships[i].m_bowLocation.m_row + '0') <<
			"," <<
			static_cast<char>
			(players[whichPlayer].m_ships[i].m_bowLocation.m_col + '0') <<
			endl;
	}
	out_file_handle << endl;
	out_file_handle.close();

}

//----------------------------------------------------------------------------
// Function:	getGrid()
// Title:	GetGrid 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek
// modified by:	Mike Farrell, Jared Whitney
// 
// Date:	01/29/17
//
// Version:	1.02
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls: allocMem(), deleteMem(), setships()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//		9/12/06 PB completed v 0.5
//		01/19/17 MF completed v 1.0
//					-successfully reading from file
//		01/27/17 MF completed v 1.01
//					-added name and pieces left to ship structs
//		01/29/17 JW completed v 1.02
//					-error handling for allocMem()
//     
//----------------------------------------------------------------------------
bool getGrid(Player players[], short whichPlayer,
	char& size, string fileName) {
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	char fsize = 'S';
	char use_ship = 'Y';
	Direction input = VERTICAL;
	short too_high = 0;
	unsigned short row = 0;
	unsigned short col = 0;
	char save = 'N';
	Ship ship_type = NOSHIP;
	Cell location = { 0, 0 };
	//short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS; 
	//short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		ifs.open(fileName);
		if (!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch (exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}

	fsize = ifs.get();
	ifs.ignore(FILENAME_MAX, '\n');

	if ((size == 'S') && (fsize == 'L'))
	{
		if (whichPlayer == 0)
		{
			deleteMem(players, 'S');
			allocMem(players, 'L');
			size = 'L';
		}
		else
		{
			//does not allow the second player to have a larger 
			//grid than the first player, due to allocation method.
			//this prompts player 2 to use the setships() function 
			//to enter their grid.
			system("cls");
			cout << "PLAYER 2 MAY NOT HAVE A LARGER GRID THAN PLAYER 1." <<
				endl;
			cout << "Press <enter> to set your ships." << endl;
			cin.get();
			setships(players, size, whichPlayer);
			return true;
		}
	}


	short numberOfRows = (toupper(fsize) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(fsize) == 'L') ? LARGECOLS : SMALLCOLS;

	for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		use_ship = 'Y';
		location.m_col = 0;
		location.m_row = 0;
		//too_high = 0;
		getline(ifs, line);
		input = static_cast<Direction>(line.at(0) - '0');
		players[whichPlayer].m_ships[j].m_orientation
			= (input == 1) ? VERTICAL : HORIZONTAL;

		row = (line.at(2));
		col = (line.at(4));

		if (((row - '0') < (-1)) || ((row - '0') > numberOfRows) ||
			((col - '0') < (-1)) || ((col - '0') > numberOfCols))
		{
			cout << "[" << shipNames[j] << "] is out of bounds. " <<
				"This ship will not be loaded." << endl;
			continue;
		}


		//call validLocation()

		if ((row == '/') || (col == '/'))
		{
			use_ship = 'N';
		}
		else
		{
			row -= '0';
			col -= '0';
			location.m_col = col;
			location.m_row = row;
			players[whichPlayer].m_ships[j].m_bowLocation = location;

			ship_type = static_cast<Ship>(j);
			players[whichPlayer].m_gameGrid[0]
				[location.m_row][location.m_col] = ship_type; //break point
		}


		players[whichPlayer].m_ships[j].m_name = static_cast<Ship>(j);
		if (use_ship == 'Y')
		{
			for (int i = 0; i < shipSize[j]; i++)
			{
				if (input == VERTICAL)
				{
					players[whichPlayer].m_gameGrid[0]
						[location.m_row + i][location.m_col] = ship_type;
				}
				else
				{
					players[whichPlayer].m_gameGrid[0]
						[location.m_row][location.m_col + i] = ship_type;
				}
			}
			players[whichPlayer].m_ships[j].m_piecesLeft = shipSize[j];
		}
		else
		{
			cout << "File does not contain [" << shipNames[j] << "] " << endl;
			players[whichPlayer].m_ships[j].m_piecesLeft = 0;
			players[whichPlayer].m_piecesLeft -= shipSize[j];
		}

	} // end for j

	  /*save = safeChoice("\nSave starting grid?", 'Y', 'N');
	  if (save == 'Y')
	  saveGrid(players, whichPlayer, fsize);*/
	cout << endl << "Successfully loaded save file." << endl << "Press <enter> to continue.." << endl;
	cin.get();
	return true;
}

//----------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//		9/12/06 PB completed v 1.0
//     
//----------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row = 'A';
	short col = 0;
	Cell location = { 0, 0 };
	do
	{
		col = 0;
		cout << endl << "Row must be a letter from A to " << highChar
			<< " and column must be  from 1 to " << numberOfCols << ": ";
		while ((row = toupper(sin.get())) < 'A' || row > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar
				<< " and column must be  from 1 to " << numberOfCols
				<< ": ";
		}
		sin >> col;
		if (!sin)
			sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
	} while (col < 1 || col > numberOfCols);

	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

//----------------------------------------------------------------------------
// Function:	validLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer: Paul Bladek
// modified by: Jared Whitney
// 
// Date:	01/19/17
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//		shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//		size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//				or cross another ship;
//			false otherwise
//
// History Log:
//		12/20/05 PB completed v 0.1
//		01/19/17 JW completed v 1.0
//     
//----------------------------------------------------------------------------
bool validLocation(const Player& player, short shipNumber, char size)
{
	bool r_val = true;
	Cell location = player.m_ships[shipNumber].m_bowLocation;
	Ship ship_type = static_cast<Ship>(shipNumber);
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	if ((player.m_ships[shipNumber].m_orientation == VERTICAL) &
		(location.m_row <= ((numberOfRows)-shipSize[shipNumber])))
	{
		for (short i = 0; i < shipSize[ship_type]; i++)
		{
			if (!player.m_gameGrid[0]
				[location.m_row + i][location.m_col] == NOSHIP)
			{
				r_val = false;
			}
		}
	}
	else if ((player.m_ships[shipNumber].m_orientation == HORIZONTAL) &
		(location.m_col <= ((numberOfCols)-shipSize[shipNumber])))
	{
		for (short i = 0; i < shipSize[ship_type]; i++)
		{
			if (!player.m_gameGrid[0]
				[location.m_row][location.m_col + i] == NOSHIP)
			{
				r_val = false;
			}
		}
	}
	else
	{
		r_val = false;
	}

	return r_val;
}

//----------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek
// modified by: Jared Whitney
// 
// Date:	01/10/17
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB completed v 1.0
//		01/10/17 JW completed v 1.01
//     
//----------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	const string group_name("by MFJW");
	const string by("Edmonds Community College CS 132");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink, BOXWIDTH, 'C');
	boxLine(sout, group_name, BOXWIDTH, 'C');
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//----------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//----------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str(), BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}
