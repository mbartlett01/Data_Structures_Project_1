#include <iostream>
using namespace std;

class CSR {
	protected:
		int numRows; //The number rows of the original matrix
		int numCols; //The number of columns of the original matrix
		int nonZeros; //The number of non-zeros in the original matrix
		int* values; //value array assuming all are integers
		int* rowPtr; //Array that contains number of non-zero elements in each row of the original matrix
		int* colPos; //Array that contains the column number from the original matrix for the non-zero values.
		//There may be others you may need
	public:
		CSR ( ); //default or empty constructor
		CSR (CSR& matrixB); //copy constructor
		CSR (int rows, int cols, int numNonZeros); //non-default constructor
		int getNumRows ( ); //return the number of rows
		int* getRowVec (int row); //Return a single row of the matrix as an array
		void addValue (int value); //add a new value in the values array
		void addColumn (int col);//add a column in the colPos array
		void addRow (int row); //add a row in the rowPtr array
		void display (); //print the contents of the three arrays. Each array must be on a different line (separated by a 
                                      //new line character) and you have exactly a single space between each value printed.
		int* matrixVectorMultiply (int* intputVector); //matrix-vector multiplication
		CSR* matrixMultiply (CSR& matrixB); //matrix-matrix multiplication
		~CSR(); //destructor
		//You may have other methods		
};
//some of the methods – Sridhar Radhakrishnan
//Default constructor which sets all values to null or zero
CSR::CSR ( ) {
	numRows = 0;
	numCols = 0;
	nonZeros = 0;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}
//Copy constructor that creates a copy of an existing CSR object
CSR::CSR (CSR& matrixB){
	numRows = 0;	//TEMP VALUES FIXME!!!!!
	numCols = 0;
	nonZeros = 0;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}
//Non-defualt constructor that sets up the size of the arrays, but does not fill them in
CSR::CSR (int rows, int cols, int numNonZeros) {
	numRows = rows;
	numCols = cols;
	nonZeros = numNonZeros;
	values = new int [nonZeros];
	colPos = new int [nonZeros];
	rowPtr = new int [numRows];
}
//Return the NumRows Variable
int CSR::getNumRows(){
	return numRows;
}
//Return a single row of the the matrix as an array
int* CSR::getRowVec(int row){
	int* vector = new int[numRows];
	for(int i = 0; i < numRows; i++){
		vector[i] = 0;
	}
	if(row < numRows - 1){
		for(int i = rowPtr[row]; i < rowPtr[row + 1]; i++){
			for(int j = 0; j < numCols; j++){
				if(colPos[i] == j){
					vector[j] = values[i];
				}
			}
		}
	} else {
		for(int i = rowPtr[row]; i < nonZeros; i++){
			for(int j = 0; j < numCols; j++){
				if(colPos[i] == j){
					vector[j] = values[i];
				}
			}
		}
	}
	return vector;
}
//Add a value to the values array
void CSR::addValue(int value){
	//find the first 0 value in the values array
	int openPos = 0;
	while(values[openPos] != NULL)
	{
		openPos += 1;
	}
	//Replace the NULL value with the given value
	values[openPos] = value;
}
//Add a column to the colPos array
void CSR::addColumn(int col){
	//find the first 0 value in the values array
	int openPos = 0;
	while(colPos[openPos] != NULL)
	{
		openPos += 1;
	}
	//Replace the NULL value with the given value
	colPos[openPos] = col;
}
//Add the row value to the row array if needed
void CSR::addRow(int row){
	//Check to see if the row is already filled and return if it is
	if(rowPtr[row] != NULL)
	{
		return;
	}
	//Fill in the position with the last added value array position
	//Find the first null value of the value array
	int openPos = 0;
	while(values[openPos] != NULL)
	{
		openPos += 1;
	}
	//Add the position before the open position to the row array
	rowPtr[row] = openPos - 1;
}
//Display the information about the array
void CSR::display(){
	//Display the actual values of the array
	//Loop over the rows
	int* temp;
	for(int i = 0; i < numRows; i++)
	{
		//Get the row
		temp = getRowVec(i);
		//Print the values in the row
		for(int j = 0; j < numCols; j++)
		{
			cout << temp[j] << " ";
		}
		//Add a new line character
		cout << endl;
		//delete the row array to prevent creating trash
		delete temp;
	}
	//Display the rowPtr array by looping over its values
	cout << "rowPtr: ";
	for(int i = 0; i < numRows; i++)
	{
		cout << rowPtr[i] << " ";
	}
	cout << endl;
	//Display the colPos array by looping over its values
	cout << "colPos: ";
	for(int i = 0; i < nonZeros; i++)
	{
		cout << colPos[i] << " ";
	}
	cout << endl;
	//Display the values array by looping over its values
	cout << "values: ";
	for(int i = 0; i < nonZeros; i++)
	{
		cout << values[i] << " ";
	}
	cout << endl;
}
int* CSR::matrixVectorMultiply (int* inputVector){
	int* outputVector = new int [numRows];
	
	for (int i=0; i < numRows; i++){
		outputVector[i] =0;
	}

	int sum = 0;
	int start, end;
	for(int i = 0; i < numRows; i++)
	{
		sum = 0;
		start = rowPtr[i];
		if((i + 1) == numRows){
			end = nonZeros;
		} else {
			end = rowPtr[i + 1];
		}
		for(int j = start; j < end; j++){
			sum = sum + (values[j] * inputVector[colPos[j]]);
		}
	}
	return outputVector;
}
//Destructor in order to remove pointer variables in class
CSR::~CSR ( ) {
	if (values != NULL) delete [ ] values;
	if (rowPtr != NULL) delete [ ] rowPtr;
	if (colPos != NULL) delete [ ] colPos;
	cout << "CSR Object Destroyed!!" << endl;
	numRows = 0;
	numCols = 0;
	nonZeros = 0;
}

int main ( ) {

   CSR* A;
   CSR* B;
   //int* aVector;
   int numRows, numColumns, numNonZeros;
   int row, col, value;

   //read in the first matrix
   cin >> numRows >> numColumns;
   cin >> numNonZeros;

   A = new CSR (numRows, numColumns, numNonZeros);
   for (int i=0; i < numNonZeros; i++) {
	cin >> row >> col >> value;
	(*A).addValue (value);
	(*A).addRow (row);//needs to be done cleverly in the method
	(*A).addColumn (col);
   }
   //Display Matrix A
   cout << "Matrix A:" << endl;
   (*A).display ( );

   CSR* C = new CSR (*A); //calling the copy constructor
   (*C).display ( );

//read in the second matrix which is similar to the first into the CSR pointer object B and display; Write code for this
/*(*B).display ( );

//read in the vector
    cin >> numColumns;
    aVector = new int [numColumns];
    for (int i=0; i < numColumns; i++) 
	cin >> aVector[i];

//Matrix-Vector Multiplication
    int* resultVector = (*A).matrixVectorMultiply (aVector);
    for (int i=0; i < (*A).getNumRows ( ); i++) 
		cout << resultVector [i] << " ";
    cout << endl;

//Matrix-Matrix Multiplication
    CSR* resultMatrix = (*C).matrixMultiply (*B);
    (*resultMatrix).display ( );
*/
// Call the destructors
     //delete [ ] aVector;
     //delete [ ] resultVector;
     delete A;
     delete B;
     delete C;
     //delete resultMatrix;

    return 0;
}

