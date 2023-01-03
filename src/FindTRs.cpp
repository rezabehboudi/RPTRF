 using namespace std;

#include <omp.h>
#include <set>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <string.h>
#include <boost/algorithm/string.hpp>
#include <stdint.h>
class TandemRepeatsFinder{
	public:
struct potential_List {
int Start_point;
potential_List *Next_Start;
};

struct Interval
{
    int low, high, core;
};

struct ITNode
{
    Interval *i;
    ITNode *left, *right;
};

ITNode * newNode(Interval i, int c)
{
    ITNode *temp = new ITNode;

    temp->i = new Interval(i);

    temp->left = temp->right = NULL;
    return temp;
};

ofstream MyExcelFile;
/*
ITNode *Handel_Interval(ITNode *root, Interval i, int c);
ITNode *Reshape_Tree(ITNode *root);
void inorder(ITNode *root);
int Is_Subset(Interval j, Interval i);


void Seq_Hasher(char n);
void Fill_Hash_Matrix();
void Report_TRs();
potential_List* Check_If_Repeat(int Temp_Count_Of_Potentials, potential_List *Temp_Pointer, potential_List *Temp_End_Pointer,int Distance);
void Create_Output_File(string Output_File_Path);
void Write_Line_To_File(string Output_Line);
string End_of_Repeat(int Start_point, int Distance, int repeatnumbers);
bool Str_Cmpr( const std::string& str1, const std::string& str2 );
void Push_To_Trs_List(int start, int last,int distance, int count );
void Write_Tr(int start, int end,int distance );
*/



const int Hash_Matrix_Rows = 260 , Hash_Matrix_colnums = 3, Minimum_Size_Of_Repeats = 3, Window_Size = 3;

string  Line;
ifstream Input_File;
ofstream Output_File;
int End_Counter = 0, listcounter=0;
int Array_Of_Lists[65536];
//unsigned short int Hash;
uint8_t Hash;
 int MAX_MOTIF_SIZE = 15, MIN_MOTIF_SIZE = 1, TR_SIZE = 10;


potential_List *Pointer_To_potentials[260][2];// First column is Head of list and second is Tail of it.

queue<int> Cores_List;
string title="";
ITNode *root = NULL;

void initiate(string ID, string seq, int Max_Motif, int Min_Motif)
{
	TR_SIZE = Min_Motif;
	MAX_MOTIF_SIZE = Max_Motif;
	Line = seq;
	
	Create_Output_File("./result-"+ ID );
	Line = seq;
	Fill_Hash_Matrix();
	cout<<"\nFinding TRs ...\n";
	Report_TRs();
	cout<<"\nReporting TRs...\n";
	inorder(root);
	Output_File.close();  
  
}





string End_of_Repeat(int Start_point, int Distance, int repeatnumbers)
{
  End_Counter = 0;
  string s1 = "", s2 = "",s="";
  try
  {
   s1 = Line.substr(Start_point,1);
   s2 = Line.substr(Start_point + (Distance * repeatnumbers),1);
  }
  catch (const std::out_of_range& oor)
  {
    return s;
  }

  while (Str_Cmpr(s1, s2))
  {
    End_Counter++;
    s += Line.substr(Start_point + (Distance * repeatnumbers),1);
    Start_point++;
    try
    {
    s1 = Line.substr(Start_point,1);
    s2 = Line.substr(Start_point + (Distance * repeatnumbers),1);
    }
    catch (const std::out_of_range& oor)
    {
      return s;
    }
  }
  return s;
}


bool Str_Cmpr( const std::string& str1, const std::string& str2 ) {
    std::string str1Cpy( str1 );
    std::string str2Cpy( str2 );
    std::transform( str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower );
    std::transform( str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower );
    return ( str1Cpy == str2Cpy );
}



void Push_To_Trs_List(int start, int last,int distance, int count )
{
//Lock

#pragma omp critical
{
  Interval i;
  string end = End_of_Repeat(start, distance, count);
  i.low = start;
  i.high = last + End_Counter ;
  // i.high = last ;

  i.core = distance;
  if((i.high - i.low) >= 9)
  {
    root = Handel_Interval(root, i , distance);
  }
  End_Counter = 0;
}
  //Unluck
}

void Create_Output_File(string Output_File_Path)
{
 Output_File.open(Output_File_Path+".txt",ios::out);

 Write_Line_To_File("**********************************TRs Found by RPTRF**********************************\n");
 Write_Line_To_File("Start            End            Len        Motif Size( Sequence )\n");
}
void Write_Tr(int start, int end,int distance )
{

  Write_Line_To_File(to_string( start + 1 ) + "      " + to_string(end)
  + "         " + to_string(end-start) +
  "  " + to_string(distance) + "(" + Line.substr(start,distance) + ")  " + Line.substr(start, (end-start) )
  );


}
void Write_Line_To_File(string Output_Line)
{
  Output_File <<"\n" << Output_Line;
}


void Fill_Hash_Matrix()
{
	for(int i =0; i< 260;i++)
	{
		Pointer_To_potentials[i][0] = Pointer_To_potentials[i][1] = 0;
	}
Hash = 0;
  			
listcounter = 0;
int Trimed_Index =0;

cout<<"\nIndexing the sequence...\n";
while (Line[Trimed_Index] == 'N'){
 Trimed_Index++;
}
for(int i =Trimed_Index; i<= Trimed_Index + Window_Size ; i++ )
 Seq_Hasher(Line[i]);


int i = Trimed_Index + Window_Size;



while ( i < Line.size())
{
	
 if(Pointer_To_potentials[Hash][0] == 0)
 {
	
   Cores_List.push(Hash);
   Array_Of_Lists[listcounter] = Hash;
   listcounter++;
   Pointer_To_potentials[Hash][0] = new potential_List;
   Pointer_To_potentials[Hash][0]->Start_point = i-Window_Size;
   Pointer_To_potentials[Hash][0]->Next_Start = NULL;
   Pointer_To_potentials[Hash][1] = Pointer_To_potentials[Hash][0];
 }
 else
 {

   Pointer_To_potentials[Hash][1]->Next_Start = new potential_List;
   Pointer_To_potentials[Hash][1]->Next_Start->Start_point = i-Window_Size;
   Pointer_To_potentials[Hash][1]->Next_Start->Next_Start = NULL;
   Pointer_To_potentials[Hash][1] = Pointer_To_potentials[Hash][1]->Next_Start;
   Pointer_To_potentials[Hash][1]->Next_Start = NULL;
 }
 
 i++;
 
 
 if(Line[i] == 'N')
 {
   int j = i, l=0;
   while (Line[j] == 'N')
     j++;
   Trimed_Index = j - i;
   for(l = j; l <= Window_Size + j; l++ )
     Seq_Hasher(Line[l]);
   i = l;
 }
 
 Seq_Hasher(Line[i]);
}



}


void Seq_Hasher(char n)
{

 Hash = Hash << 2;

 switch (n)
  {
   case 'A':
   case 'a':
   Hash += 0;
   break;
   case 'T':
   case 't':
   Hash += 1;
   break;
   case 'C':
   case 'c':
   Hash += 2;
   break;
   case 'G':case 'g':
   Hash += 3;
   break;
 }

}

potential_List* Check_If_Repeat(int Temp_Count_Of_Potentials, potential_List *Temp_Pointer, potential_List *Temp_End_Pointer,int Distance)
{
	
  string s1 = "",s2 = "";
  int Repeats_Counter = 1;
  potential_List *Temp_Start_Pointer,*current_Pointer;
  Temp_Start_Pointer = Temp_Pointer;
  current_Pointer = Temp_Start_Pointer;
  if(Distance <= Window_Size + 1)
  {
    Push_To_Trs_List(Temp_Start_Pointer->Start_point, Temp_Start_Pointer->Start_point + (Distance)*Temp_Count_Of_Potentials, Distance, Temp_Count_Of_Potentials);
    return Temp_End_Pointer;//END REPORT *
  }
  else if(Distance > Window_Size + 1 && Distance <= MAX_MOTIF_SIZE)
  {
    s1 = Line.substr((Temp_Start_Pointer->Start_point) + (Window_Size + 1),  Distance - (Window_Size + 1));
    while (Temp_Count_Of_Potentials >= Minimum_Size_Of_Repeats-1)
    {
      try
      {
		  
        //it is possible to generate subseq from currentpointer
        s2 = Line.substr( Temp_Start_Pointer->Start_point + ((Distance * Repeats_Counter) + (Window_Size+1)) ,Distance - (Window_Size + 1));
		
      }
      catch (const std::out_of_range& oor)
      {		  
        if(Repeats_Counter >= Minimum_Size_Of_Repeats)
        {
          Push_To_Trs_List(Temp_Start_Pointer->Start_point, Temp_Start_Pointer->Start_point + (Distance)*Repeats_Counter, Distance, Repeats_Counter);
          return current_Pointer;
        }
        else
        {
          return NULL;
        }
      }
      
	  int equality = 0;
      equality = Str_Cmpr(s1,s2);
      if(equality)
      {
		
		
        current_Pointer = current_Pointer->Next_Start;
        Repeats_Counter++;
        Temp_Count_Of_Potentials--;
		
        if(Temp_Count_Of_Potentials == 1 && Repeats_Counter >= Minimum_Size_Of_Repeats)
        {
			
          Push_To_Trs_List(Temp_Start_Pointer->Start_point, Temp_Start_Pointer->Start_point + (Distance)*Repeats_Counter, Distance, Repeats_Counter);
          return current_Pointer;
        }
      }
      else if(Repeats_Counter >= Minimum_Size_Of_Repeats)
      {
        //insert to interval tree;
        Push_To_Trs_List(Temp_Start_Pointer->Start_point,Temp_Start_Pointer->Start_point + (Distance)*Repeats_Counter, Distance, Repeats_Counter);
        return current_Pointer;
      }
      else
      {
		  
		  return NULL;
	  }

    }
	
   return NULL;
  }
  
 
  return NULL;
}

void Report_TRs()
{
	if( Cores_List.empty() )
		return;
		
	int rows = 0, lists[256];
	
	rows = Cores_List.size();
	
	for(int i = 0; i< rows; i++)
	{
		lists[i] = Cores_List.front();
		Cores_List.pop();
	}
	omp_set_num_threads(1);
	#pragma omp parallel
	{
	#pragma omp for
	for(int i = 0; i< rows; i++)
	{
		Check_List(lists[i]);
	}
	}
	
}


void Check_List(int row)
{

  int Distance = 0, Temp_Count_Of_Potentials = 1,repeat = 1;
  potential_List *Temp_Pointer,*Temp_Start_Pointer, *i, *j, *k, *x;
  Temp_Pointer = Pointer_To_potentials[row][0];


  i = Temp_Pointer;
  j = i->Next_Start;
  if(j != NULL)// for big files we dont need this cndition
  if(j->Next_Start ==  NULL)
  {
	  
    Check_If_Repeat(2, i, j, (j->Start_point)-(i->Start_point));
  }
  else
  {
   while (i->Next_Start != NULL)
   {
     j = i->Next_Start;
     Distance = (j->Start_point) - (i->Start_point);
     if (Distance >= MAX_MOTIF_SIZE)
     {
       i = i->Next_Start;
     }
     else if(Distance >= MIN_MOTIF_SIZE)
     {
       repeat++;
       while (j->Next_Start != NULL)
       {
         k = j->Next_Start;
         if(Distance == (k->Start_point) - (j->Start_point))
         {
           j = j->Next_Start;
           repeat++;
         }
         else
         {
           break;
         }
       }
       if((Distance * repeat) >= TR_SIZE )
			x = Check_If_Repeat(repeat, i, j, Distance);
       repeat = 1;
       if( x != NULL)
       {
         i = i->Next_Start;

       }
       else
       {
         i = i->Next_Start;
       }
     }

   }
  }


}



void inorder(ITNode *root)
{

  if(root == NULL)
    return;

  inorder(root->left);
  Write_Tr(root->i->low, root->i->high, root->i->core );
  inorder(root->right);
}



ITNode *Handel_Interval(ITNode *root, Interval i, int c)
{

  if( root == NULL )
    return newNode(i,c);

  Interval j;


  j.low = root->i->low; j.high = root->i->high;

  if( Is_Subset(j,i) )
  {
    return root;
  }
  else if( Is_Subset(i,j) == 1 )
  {

    root = Reshape_Tree(root);
    root = Handel_Interval(root, i, c);
    return root;
  }
  else
  {
    if( j.low > i.low )
    {
      root->left = Handel_Interval(root->left, i, c);
      return root;
    }
    else
    {
      root->right = Handel_Interval(root->right, i, c);
      return root;
    }
  }


  return root;
}

int Is_Subset(Interval j, Interval i)
{
  if( ((j.low <= i.low) && (j.high > i.high) ) || ((j.low < i.low) && (j.high >= i.high) ) )
    return 1;

  if( (j.low == i.low) && (j.high == i.high))
    return 2;

  return 0;
}



ITNode *Reshape_Tree(ITNode *root)
{

  ITNode *parent,*child;

  if( (root == NULL ) || ( root->right == NULL ) && ( root->left == NULL ) ){
    return NULL;
  }


  if (root->right != NULL)
  {

    parent = root;
    child = parent->right;
    if( child->left == NULL)
    {
      parent->right = child->right;
      root->i = child->i;
      return root;
    }

    while (child->left != NULL)
    {
      parent = child;
      child = child->left;
    }

    parent->left = child->right;
    root->i = child->i;
    return root;

  }



  if (root->left != NULL)
  {

    parent = root;
    child = parent->left;
    if( child->right == NULL)
    {
      parent->left = child->left;
      root->i = child->i;
      return root;
    }

    while (child->right != NULL)
    {
      parent = child;
      child = child->right;
    }

    parent->right = child->left;
    root->i = child->i;
    return root;

  }

  return root;
}


};

//end of file
