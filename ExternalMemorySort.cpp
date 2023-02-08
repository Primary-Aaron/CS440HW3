/* This is skeleton code for the Two-Pass Multi-Way Merge Sort algorithm, you can make modifications as long as you meet 
   all question requirements*/  
// Currently, this program will just load the records into buffers (main memory) and print the records once the buffers 
// are filled. This process will continue until all of Emp.csv is read.

#include <bits/stdc++.h>
using namespace std;

//defines how many buffers are available in the Main Memory 
#define buffer_size 22

struct EmpRecord {
    int eid;
    string ename;
    int age;
    double salary;
};
EmpRecord buffers[buffer_size]; // this structure contains 22 buffers; available as your main memory.

// Grab a single block from the Emp.csv file. In theory, if a block was larger than
// one tuple, this function would return an array of EmpRecords (one block worth) 
// and the entire if-then-else statement would be wrapped in a loop that would read
// tuples in until the block size was hit.
EmpRecord Grab_Emp_Record(fstream &empin) {
    string line, word;
    EmpRecord  emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}

// Print whatever is stored in the buffers of Main Memory 
// Can come in handy to see if you've sorted the records in your main memory properly.
void Print_Buffers(int cur_size) {
    for (int i = 0; i < cur_size; i++)
    {
        cout << i << " " << buffers[i].eid << " " << buffers[i].ename << " " << buffers[i].age << " " << buffers[i].salary << endl;
    }
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(EmpRecord arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  /* create temp arrays */
  EmpRecord L[n1], R[n2];

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
      L[i].eid = arr[l + i].eid;
      L[i].ename = arr[l + i].ename;
      L[i].age = arr[l + i].age;
      L[i].salary = arr[l + i].salary;
  for (j = 0; j < n2; j++)
      R[i].eid = arr[l + i].eid;
      R[i].ename = arr[l + i].ename;
      R[i].age = arr[l + i].age;
      R[i].salary = arr[l + i].salary;

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2) {
      if (L[i].eid <= R[j].eid) {
          arr[k] = L[i];
          i++;
      }
      else {
          arr[k] = R[j];
          j++;
      }
      k++;
  }

  /* Copy the remaining elements of L[], if there
  are any */
  while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
  }

  /* Copy the remaining elements of R[], if there
  are any */
  while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
  }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(EmpRecord arr[], int l, int r)
{
  if (l < r) {
      // Same as (l+r)/2, but avoids overflow for
      // large l and h
      int m = l + (r - l) / 2;

      // Sort first and second halves
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);

      merge(arr, l, m, r);
  }
}


// Sort the buffers in main memory based on 'eid' and then store those sorted records in
// a temporary file on disk (create a run and store it as a file on disk).
// You can change the return type and arguments as you see fit. 
void Sort_in_Main_Memory(EmpRecord empin[], int cur_size){
    cout << "Sorting..." << endl;
    mergeSort(empin, 0, cur_size);
    return;
}

// Merges your M-1 runs (from disk) using the buffers in main memory and stores them in 
// a sorted file called 'EmpSorted.csv'(The Final Output File).
// You can change the return type and arguments as you see fit.
void Merge_Runs_in_Main_Memory(){
    cout << "Merging Not Implemented" << endl;
}

int main() {
  // open file streams to read and write
  fstream input_file;
  input_file.open("Emp.csv", ios::in);
 
  // flags to check when relations are done being read
  bool flag = true;
  int cur_size = 0;
  
  /*First Pass: The following loop will read each block, put it into main_memory,
    sort them, and then will put write them to a temporary file (as a run) for 2nd pass */
  while (flag) {
      // FOR BLOCK IN RELATION EMP

      // grabs a block
      EmpRecord  single_EmpRecord  = Grab_Emp_Record(input_file);
      // checks if filestream is empty
      if (single_EmpRecord.eid == -1) {
          flag = false;
          Print_Buffers(cur_size); // The main_memory is not filled up but there are some leftover tuples that need to be sorted.
      }
      if(cur_size + 1 <= buffer_size){
          // Memory is not full. Store the current record into a buffer.
          buffers[cur_size] = single_EmpRecord ;
          cur_size += 1;
      }
      else{
          // Memory is now full. Sort the tuples in Main Memory and store them in a temporary file (runs)
          cout << "Main Memory is full. Time to sort and store sorted blocks in a temporary file" << endl;
          Print_Buffers(buffer_size);
          Sort_in_Main_Memory(single_EmpRecord, cur_size);
          
          // After sorting, start again. Clear memory and put the current tuple into main memory.
          cur_size = 0;
          buffers[cur_size] = single_EmpRecord;
          cur_size += 1;
      }
      
  }
  input_file.close();
  
  /* Implement 2nd Pass: Read the temporary sorted files (runs) and sort them as discussed in class. 
	 Write the final output (fully sorted Emp relation) to EmpSorted.csv*/

  // Uncomment when you are ready to store the sorted relation
  // fstream sorted_file;  
  // sorted_file.open("EmpSorted.csv", ios::out | ios::app);

  // Pseudocode
  bool flag_sorting_done = false;
  while(!flag_sorting_done){
      Merge_Runs_in_Main_Memory();
      break;
  }
  
  // You can delete the temporary sorted files (runs) after you're done in order to keep things clean and tidy.

  return 0;
}
