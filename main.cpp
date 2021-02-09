#include <iostream>
using namespace std;

class CSR {
	protected:
		int n; //The number rows of the original matrix
		int m; //The number of columns of the original matrix
		int nonZeros; //The number of non-zeros in the original matrix
		int* values; //value array assuming all are integers
		int* rowPtr; //Array that contains number of non-zero elements in each row of the original matrix
		int* colPos; //Array that contains the column number from the original matrix for the non-zero values.
		//There may be others you may need
	public:
		CSR ( ); //default or empty constructor
		CSR (CSR& martrixB); //copy constructor
		CSR (int rows, int cols, int numNonZeros);
		int getNumRows ( );
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
CSR::CSR ( ) {
	n = 0;
	m = 0;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}
CSR::CSR (int rows, int cols, int numNonZeros) {
	n = rows;
	m = cols;
	nonZeros = numNonZeros;
	values = new int [nonZeros];
	colPos = new int [nonZeros];
	rowPtr = new int [n];
}
int* CSR::matrixVectorMultiply (int* inputVector){
	int* outputVector = new int [n];
	
	for (int i=0; i < n; i++) outputVector[i] =0;

	for (int i=0; i < n; i++) 
	     for (int j=rowPtr[i]; j < rowPtr[i+1]; j++)
		outputVector[i] = outputVector[i] + values[j] * inputVector[colPos[j]];

	return outputVector;
}
CSR::~CSR ( ) {
	if (values != NULL) delete [ ] values;
	if (rowPtr != NULL) delete [ ] rowPtr;
	if (colPos != NULL) delete [ ] colPos;
	cout << "CSR Object Destroyed!!" << endl;
	n = 0;
	m = 0;
	nonZeros = 0;
}

int main ( ) {

   CSR* A;
   CSR* B;
   int* aVector;
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
   (*A).display ( );

   CSR* C = new CSR (*A); //calling the copy constructor
   (*C).display ( );

//read in the second matrix which is similar to the first into the CSR pointer object B and display; Write code for this
(*B).display ( );

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

// Call the destructors
     delete [ ] aVector;
     delete [ ] resultVector;
     delete A;
     delete B;
     delete C;
     delete resultMatrix; 

    return 0;
}

