<h1>Tiny Machine - CDA3103 Project</h1>

<br>Using C programming language write a program that simulates a variant of the Tiny Machine 
Architecture. In this implementation memory (RAM) is split into Instruction Memory (IM) and Data 
Memory (DM). Your code must implement the basic instruction set architecture (ISA) of the Tiny 
Machine Architecture:<br><br>

1 -> LOAD<br>
2 -> ADD<br>
3 -> STORE<br>
4 -> SUB<br>
5 -> IN<br>
6 -> OUT<br>
7 -> END<br>
8 -> JMP<br>
9 -> SKIPZ<br><br>

Each piece of the architecture must be accurately represented in your code (Instruction Register, Program 
Counter, Memory Address Registers, Instruction Memory, Data Memory, Memory Data Registers, and 
Accumulator). Data Memory will be represented by an integer array. Your Program Counter will begin 
pointing to the first instruction of the program. 
For the sake of simplicity Instruction Memory (IM) and Data Memory (DM) may be implemented 
as separate arrays.<br><br>

<b>Hint: Implementing a struct for your Instructions and an array of these structs as your Instruction 
Memory greatly simplifies this program.</b><br><br>

Example: 
typedef struct{
  int opCode, device Or Address;
} Instruction;
Instruction IM[MAXPROGRAMSIZE]; <br><br>

<b>Note: IM, MDR1, and IR are of type Instruction. All other CPU registers and Data Memory (DM) are of 
type int.</b><br><br>

<b>Input Specifications</b><br>
Your simulator must run from the command line with a single input file as a parameter to main. This file 
will contain a sequence of instructions for your simulator to store in “Instruction Memory” and then run 
via the fetch/execute cycle. In the input file each instruction is represented with two integers: the first one 
represents the opcode and the second one a memory address or a device number depending on the 
instruction.<br><br>

Example:<br>
Input File<br>
5 5    //IN 5<br>
6 7    //OUT 7<br>
3 0    //STORE 0<br>
5 5    //IN 5<br>
6 7    //OUT 7<br>
3 1    //STORE 1<br>
1 0    //LOAD 0<br>
4 1    //SUB 1<br>
3 0    //STORE 0<br>
6 7    //OUT 7<br>
1 1    //LOAD 1<br>
6 7    //OUT 7<br>
7 0    //END<br><br>

<b>Output Specifications</b><br>
Your simulator should provide output according to the input file. Along with this output your program 
should provide status messages identifying details on the workings of your simulator. Output text does 
not have to reflect my example word-for-word, but please provide detail on the program as it runs in a 
readable format that does not conflict with the actual output of your simulator. After each instruction print 
the current state of the Program Counter, Accumulator, and Data Memory. The INPUT instruction is the 
only one that should prompt an interaction from the user.<br><br>

Example:<br>
Assembling Program...<br>
Program Assembled.<br>
Run.<br>
PC = 10 | A = NULL | DM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]<br>
/* input value */<br>
X<br>
PC = 11 | A = X | DM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]<br>
/* outputting accumulator to screen */<br>
X<br>
PC = 12 | A = X | DM = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]<br>
/* storing accumulator to memory location 0 */<br>
PC = 13 | A = X | DM = [X, 0, 0, 0, 0, 0, 0, 0, 0, 0]<br>
... etc<br>
Program complete.<br><br>

<b>Grading</b><br>
Your simulator will be graded on the above criteria. Your program should compile and run from the 
command line with one input file parameter. Please note that your program will not just be graded on 
whether or not it runs successfully; accurate simulation and a thorough demonstration of your 
understanding on the workings of this architecture will constitute a large portion of this grade. As that is 
the case it is in your best interest to comment your program in a concise and readable way. However, if 
your program does not run or compile the maximum points possible will be 30.<br><br>

For instance, to implement FETCH and instruction LOAD you must implement each step:<br>
FETCH  <br>
MAR -> PC<br>
PC -> PC + 1 <br>
MDR -> IM [MAR] // IM stands for Instruction Memory (program memory) <br>
IR -> MDR<br>
Case IR.OP = 1 Load is executed.<br>
LOAD (Execute cycle)<br>
MAR2 -> IR.ADDR <br>
MDR2 -> DM [MAR2] //DM stands for Data Memory<br>
A ->  MDR2<br><br>

<b>Note: Lecture 1 describes the instruction set architecture of the Tiny Machine.</b><br>

<b>Submission</b><br>
Your program must be submitted as a C file. For example: NameMyProgram.c 
Please check and double check your submission.<br><br>

<b>Note: you can use one or two MARs, MAR for IM and MAR2 for DM.</b><br><br>

Tiny Machine ISA:<br>
FETCH  <br>
MAR -> PC<br>
PC -> PC + 1 <br>
MDR -> IM [MAR] // IM stands for Instruction Memory (program memory) <br>
IR MDR -> IM [MAR] // IM stands for Instruction Memory (program memory) MDR<br>
Depending on IR.OP  one of the following instructions will be executed:<br>
(Execute cycle)<br>
LOAD    <br>
MAR2 -> IR.ADDR <br>
MDR2 -> DM[MAR2]   <br>
A ->  MDR2  <br>
ADD      <br>
MAR2 -> IR.ADDR <br>
MDR2 -> DM[MAR2]   <br>
A ->  A + MDR2  <br>
STORE     <br>
MAR2 -> IR.ADDR<br>
MDR2 -> A  <br>
DM[MAR2] -> MDR2<br>
SUB     <br> 
MAR2 -> IR.ADDR <br>
MDR2 -> DM[MAR2]   <br>
A ->  A - MDR2   <br>
IN  <br>
A -> Input value from keyboard <br>
 
OUT <br>
Screen -> A  <br>
END <br>
Run -> 0   // In your program Run must be initialized to 1 to control the instruction cycle.<br>
JMP     <br>
PC -> IR.ADDR <br>
 
SKIP      <br>
IF (A == 0) PC  PC + 1 <br>
