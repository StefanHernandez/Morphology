#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class Morphology{

	int numRowsIMG, numColsIMG, minValIMG, maxValIMG;
	int numRowsSE, numColsSE, minValSE, maxValSE;
	int rowOrigin, colOrigin;
	
	int** zeroFramedAry;
	int** morphFramedAry;
	int** structEleAry;
	int** tempFramedAry;
	
	int rowFrameSize, colFrameSize;
	
	public:
	Morphology(ifstream& infile1, ifstream& infile2){
		
		infile1>>numRowsIMG>>numColsIMG>>minValIMG>>maxValIMG;
		infile2>>numRowsSE>>numColsSE>>minValSE>>maxValSE>>rowOrigin>>colOrigin;
		
			
		rowFrameSize = numRowsSE-1;
		colFrameSize = numColsSE-1;
		
		zeroFrame(infile1);
		morphFrame();
		
		structEle(infile2);
	
	
	
	
	consolePrintIMG();
	
	consolePrintSE();
	
	
	}
	
	void consolePrintIMG(){
		cout<<"IMAGE: "<<endl;
		cout<<numRowsIMG<<" "<<numColsIMG<<" "<<minValIMG<<" "<<maxValIMG<<endl;
	
		for(int i=rowFrameSize; i<numRowsIMG+rowFrameSize; i++ ){
			for(int j=colFrameSize; j<numColsIMG+colFrameSize; j++){
			
				cout<<zeroFramedAry[i][j]<<" ";
			}
		 cout<<endl;	
		}
	cout<<endl<<endl;
	}
	
	void consolePrintSE(){
		cout<<"Structuring Element:"<<endl;
		cout<<numRowsSE<<" "<<numColsSE<<" "<<minValSE<<" "<<maxValSE<<endl;
		cout<<rowOrigin<<" "<<colOrigin<<endl;
	
		for(int i=0; i<numRowsSE; i++ ){
			for(int j=0; j<numColsSE; j++){
				cout<<structEleAry[i][j]<<" ";
			}
		 cout<<endl;	
		}
	cout<<endl<<endl;
	}
	
	void consolePrintMorph(){
		
		
		cout<<numRowsIMG<<" "<<numColsIMG<<" "<<minValIMG<<" "<<maxValIMG<<endl;
	
	
	
		for(int i=rowFrameSize; i<numRowsIMG+rowFrameSize; i++ ){
			for(int j=colFrameSize; j<numColsIMG+colFrameSize; j++){
				cout<<morphFramedAry[i][j]<<" ";
			}
		 cout<<endl;	
		}
	cout<<endl<<endl;
		
	}
	
	
	
	
	
	/////////////////
	// Framing Image /
	/////////////////
	void zeroFrame(ifstream& infile1){
	
	zeroFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
		for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
			zeroFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
		}
		
		for(int k = 0; k<numRowsIMG+(2*rowFrameSize); k++){
			for(int l =0; l<rowFrameSize; l++){
	  
			zeroFramedAry[k][l]=0;
			zeroFramedAry[k][numColsIMG+(colFrameSize*2)-1-l]=0;
			}
	  }
	

	
	  for(int j = 0; j<=numColsIMG+(2*colFrameSize); j++){
		  for(int m = 0; m<colFrameSize; m++){
			zeroFramedAry[m][j]=0;
			zeroFramedAry[numRowsIMG+(rowFrameSize*2)-1-m][j]= 0;
		  }
	  }
    
	    //Load image
		int data;
		for(int r=rowFrameSize; r<numRowsIMG+rowFrameSize; r++){
		  for(int c=colFrameSize; c<numColsIMG+colFrameSize; c++){
		    infile1>>data;
			zeroFramedAry[r][c]=data;
		  }
		}
	
	}
	
	/////////////////
	// Framing Morph /
	/////////////////
	void morphFrame(){
		
		morphFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
		for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
			morphFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
		}
		
		for(int i=0; i<(numRowsIMG+ (2*rowFrameSize)); i++){
		  for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
			morphFramedAry[i][j]=0;
		  }
		}
		
		//We also set up the temp for opening/closing
		tempFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
		for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
			tempFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
		}
		
		for(int i=0; i<(numRowsIMG+ (2*rowFrameSize)); i++){
		  for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
			tempFramedAry[i][j]=0;
		  }
		}
	}
	
	//////////////////
	// Struct Element /
	//////////////////
	void structEle(ifstream& infile2){
	
		structEleAry = new int*[numRowsSE];
		 for(int r=0; r<(numRowsSE); r++){
			structEleAry[r] = new int[numColsSE];
		 }
		 
	    //Load image
		int data;
		for(int r=0; r<numRowsSE; r++){
		  for(int c=0; c<numColsSE; c++){
		    infile2>>data;
			structEleAry[r][c]=data;
		  }
		}
		
		
		 
		 

	
	
	}
	
	
	//////////////////
	//   EROSION     /
	//////////////////
	
	void Erosion(ofstream& outfile){
	
		morphFrameZERO();
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(zeroFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Erosion /
			   ////////////////////
			   
			   int flag = 1; // Will use this as a boolean flag for whether it passes or not
			   
			   int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					
					if(structEleAry[seRow][seCol]==1){
					
						if(zeroFramedAry[i][j] != structEleAry[seRow][seCol]){
							flag=0;
						}
					}
				  
				  
				  
				  }
			   }
			   //cout<<endl<<endl;
			   
			   morphFramedAry[currentRow][currentCol] = flag;
			
			}
		  
		  }
		}
		cout<<"Erosion Result "<<endl;
		consolePrintMorph();
		
		prettyPrint(outfile);
		
		
	
	}
	
	///////////////
	//This version is for OPENING operations, does not zeroing at start
	// edits temp and passes it to DilationOpening
	///////////////
	void ErosionO(){
	
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(zeroFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Erosion /
			   ////////////////////
			   
			   int flag = 1; // Will use this as a boolean flag for whether it passes or not
			   
			   int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					
					if(structEleAry[seRow][seCol]==1){
					
						if(zeroFramedAry[i][j] != structEleAry[seRow][seCol]){
							flag=0;
						}
					}
				  
				  
				  
				  }
			   }
			   //cout<<endl<<endl;
			   
			   tempFramedAry[currentRow][currentCol] = flag;
			
			}
		  
		  }
		}
		
		
		
		
	
	}
	//Closing for Erosion, no zeroing, and edits morphFrame using temp
	void ErosionC(){
		
		//Should start from row = rowOrigin and end at <(numRowsIMG+2)-(numRowsSE-1 = colOrigin until 
	
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(tempFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Erosion /
			   ////////////////////
			   
			   int flag = 1; // Will use this as a boolean flag for whether it passes or not
			   
			    int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					
					if(structEleAry[seRow][seCol]==1){
					
						if(tempFramedAry[i][j] != structEleAry[seRow][seCol]){
							flag=0;
						}
					}
				  
				  
				  
				  }
			   }
			   
			   
			   morphFramedAry[currentRow][currentCol] = flag;
			
			}
		  
		  }
		}
		
		
		
		
	
	}
	
	void Dilation(ofstream& outfile){
		
		morphFrameZERO();
		
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(zeroFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Dilation /
			   ////////////////////
			   
			   
			   
			    int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					if(structEleAry[seRow][seCol]==1){
						morphFramedAry[i][j] = structEleAry[seRow][seCol];
					}	
					
				  
				  
				  
				  }
			   }
			
			}//end if
		  
		  }
		}
		
		cout<<"Dilation Result "<<endl;
		consolePrintMorph();
		
		prettyPrint(outfile);
		
	}
	
	//Dilation for Opening-  no zeroframing needed AND we create morphAry, working with temp
	void DilationO(){
		
		
		
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(tempFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Dilation /
			   ////////////////////
			   
			   
			   
			    int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					if(structEleAry[seRow][seCol]==1){
						morphFramedAry[i][j] = structEleAry[seRow][seCol];
					}	
					
				  
				  
				  
				  }
			   }
			
			}//end if
		  
		  }
		}
		
	}
	
	//Dilation for Closing
	//We generate the tempAry for erosionC to use afterwards
	void DilationC(){
		
		
		
		for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
		  for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
		  
			if(zeroFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
			
			   ////////////////////
			   // Test for Dilation /
			   ////////////////////
			   
			   
			   
			   int rowStart = (currentRow-rowOrigin);
			   int rowEnd = (rowStart+numRowsSE);
			   int colStart = (currentCol-colOrigin);
			   int colEnd = (colStart + numColsSE);
			   
			   int seRow;
			   int seCol;
			   
			   for(int i = rowStart; i< rowEnd; i++){
			      for(int j = colStart; j< colEnd; j++){
				  
					seRow =  (numRowsSE-(rowEnd-i));
					seCol =  (numColsSE-(colEnd-j));
					
					if(structEleAry[seRow][seCol]==1){
						tempFramedAry[i][j] = structEleAry[seRow][seCol];
					}	
					
				  
				  
				  
				  }
			   }
			
			}//end if
		  
		  }
		}
		
	}
	
	void prettyPrint(ofstream& outfile){
		
		outfile<<numRowsIMG<<" "<<numColsIMG<<" "<<minValIMG<<" "<<maxValIMG<<endl;
	
		for(int i=1; i<numRowsIMG+1; i++ ){
			for(int j=1; j<numColsIMG+1; j++){
				outfile<<morphFramedAry[i][j]<<" ";
			}
		 outfile<<endl;	
		}
	
	}
	
	void morphFrameZERO(){
		
		for(int i=0; i<(numRowsIMG+(2*rowFrameSize)); i++){
		  for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
			morphFramedAry[i][j]=0;
		  }
		}
		
	}
	
	
	void Opening(ofstream& outfile){
		
		morphFrameZERO();
		
		ErosionO();
		DilationO();
		
		cout<<"Opening Result "<<endl;
		consolePrintMorph();
		
		prettyPrint(outfile);
		
	}
	
	void Closing(ofstream& outfile){
		
		morphFrameZERO();
		
		DilationC();
		ErosionC();
		
		
		cout<<"Closing Result "<<endl;
		consolePrintMorph();
		
		prettyPrint(outfile);
		
	}
	
	void setSE(ifstream & infile){
		
	}
	
	
	
	
	

};



int main(int argc, char* argv[]){

	ifstream infile1, infile2;
	infile1.open(argv[1]);
	infile2.open(argv[2]);
	
	char operation = *argv[3];
	
	
	//create a generic output file that can be used
	ofstream outfile1;
	outfile1.open("output.txt");
	//outfile2.open(argv[4]);
	//outfile3.open(argv[5]);
	//outfile4.open(argv[6]);
	
	Morphology morph(infile1, infile2);
	
		
	if(operation =='D') morph.Dilation(outfile1);
	
	if(operation =='E') morph.Erosion(outfile1);
		
	if(operation =='O') morph.Opening(outfile1);
	
	if(operation =='C') morph.Closing(outfile1);
	
	int flag = 0;
	string SE;
	ifstream infile3;
	
	cout<<"Choose Q to quit else hit any key: ";
	cin>>operation;
	if(operation =='Q') flag = 1;
	
	while(flag == 0){
		
		cout<<"Choose structuring element file name: ";
		cin>>SE;
		cout<<endl;
		
		infile3.open(SE.c_str());
		morph.structEle(infile3);
		
		cout<<"Choose Operation (E/D/O/C) or Q to quit: ";
		cin>>operation;
		cout<<endl;
		
	if(operation =='D') morph.Dilation(outfile1);
	
	if(operation =='E') morph.Erosion(outfile1);
		
	if(operation =='O') morph.Opening(outfile1);
	
	if(operation =='C') morph.Closing(outfile1);
	
	if(operation =='Q') flag = 1; 
	
	infile3.close();
	
	
	outfile1.close();
	infile3.open("output.txt");
	//reset image for next round
	morph.zeroFrame(infile3);
	infile3.close();
	outfile1.open("output.txt");
	
	
	
	}

	infile1.close();
	infile2.close();
	outfile1.close();
	//outfile2.close();
	//outfile3.close();
	//outfile4.close();
	
}