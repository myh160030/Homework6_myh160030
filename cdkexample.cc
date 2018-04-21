// Name: Matthew Huang
// Email: myh160030@utdallas.edu
// Course number: CS 3377.501

#include <iostream>
#include <fstream>
#include <stdint.h>
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


class BinaryFileHeader
{
 public:

 uint32_t magicNumber;		/* Should be 0xFEEDFACE */
 uint32_t versionNumber;
 uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:

 uint8_t strLength;
 char 	 stringBuffer[maxRecordStringLength];
};

int main()
{
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);
  
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myHeader = new BinaryFileHeader();

  ifstream binaryInputFile ("cs3377.bin", ios::in | ios::binary);

  binaryInputFile.read((char *) myHeader, sizeof(BinaryFileHeader));
  /*
   * Display a message
   */
  char text[256]; 
  
  sprintf(text, "Magic: 0x%0X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, text);
  
  sprintf(text, "Version: %d", myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, text);

  sprintf(text, "NumRecords: %ld", myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, text);

  drawCDKMatrix(myMatrix, true);    /* required  */

  BinaryFileRecord *myRecords = new BinaryFileRecord();

  for (int i = 0; i < (int)myHeader->numRecords; i++)
     {
	binaryInputFile.read((char *) myRecords, sizeof(BinaryFileRecord));

	sprintf(text, "strlen: %d", myRecords->strLength);
	setCDKMatrixCell(myMatrix, i + 2, 1, text);

	setCDKMatrixCell(myMatrix, i + 2, 2, myRecords->stringBuffer);
     }

  drawCDKMatrix(myMatrix, true);    /* required */   

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  binaryInputFile.close();
  endCDK();
}
