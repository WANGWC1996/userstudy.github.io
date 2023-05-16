Readme (Interactive Mining with Ordered and Unordered Attributes)
=========================
This package contains all source codes for 
a. Algorithm DI 
	1. It only works for the special case of IOU
	2. The code is in folder DI
b. Algorithm EDI 
	1. It works for the general case of IOU. 
	2. The code is in folder EDI
c. Algorithm BS 
	1. It works for the general case of IOU.
	2. The code is in folder BS
d. Algorithm RH 
	1. It is an adapted existing algorithm.
	2. The code is in folder RH.
e. Algorithm ActiveRanking 
	1. It is an adapted existing algorithm.
	2. The code is in folder ActiveRanking.
f. Algorithm UtilityApprox 
	1. It is an adapted existing algorithm.
	2. The code is in folder UtilityApprox.
g. Algorithm UH-Random 
	1. It is an adapted existing algorithm.
	2. The code is in folder UH.

Make sure there is a folder called "input/", a folder called "output/" and a file called 
"config.txt" under the working directory.
They will be used for storing the input/output files, some intermediate results and the 
input parameters.

Usage Step
==========
a. Compilation
	mkdir build
	cd build
	cmake ..
	make

	You will need to install the GLPK package (for solving LPs) at first.
	See GLPK webpage <http://www.gnu.org/software/glpk/glpk.html>.
	Then update the path in CMakeLists.txt
		set(INC_DIR /usr/local/Cellar/glpk/5.0/include)
		set(LINK_DIR /usr/local/Cellar/glpk/5.0/lib)
	Update path "/usr/local/Cellar/glpk/5.0" to the path you install the GLPK package
	
b. Execution
	./run

c. Config
	The config file contains the input parameters (whose format will be described in Appendix A).

c. Input
	The input file contains the dataset (whose format will be described in Appendix B).
	
d. Output
	The output will be shown on the console (whose format will be described in Appendix C).

Example
=======
Sample input (input/11d.txt) are provided. The dataset is described by one ordered 
attribute and one unordered attribute
Try: ./run



Appendix A. Format of Config File
------------------------------------
The format is: DatasetName d e[1] e[2] ... e[d]
DatasetName - the name of the dataset
d - the number of attributes in the dataset
e[1] - the first attribute value of the user's expected point 
e[2] - the second attribute value of the user's expected point
...
e[d] - the d-th attribute value of the user's expected point
For example, you might see
-----------------------
11d.txt  2  1000  370 
-----------------------


Appendix B. Format of Input File
------------------------------------
The format of the first line is: n d_o d_u
n - the dataset size, integer
d_o - the number of ordered attributes in the dataset, integer
d_u - the number of unordered attributes in the dataset, integer
The format of the following n lines is
-----------------------------------------------------------------
<ordered attribute 1> <ordered attribute 2> ... <<ordered attribute d_o> 
<unordered attribute 1> <unordered attribute 2> ... <unordered attribute d_u> 
-----------------------------------------------------------------
Each line corresponds to a point.


Appendix C. Format of Console Output
-----------------------------------------------------------------
The format of the output is
-----------------------------------------------------------------------------------
|      Algorithm | # of Questions |  Preprocessing |    Interaction | Point #ID |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|   Ground Truth |              - |              - |              - |    PtID-0 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             DI |      Q-count-1 |      PreTime-1 |    InterTime-1 |    PtID-1 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|            EDI |      Q-count-2 |      PreTime-2 |    InterTime-2 |    PtID-2 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             BS |      Q-count-3 |      PreTime-3 |    InterTime-3 |    PtID-3 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             RH |      Q-count-4 |      PreTime-4 |    InterTime-4 |    PtID-4 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|  ActiveRanking |      Q-count-5 |      PreTime-5 |    InterTime-5 |    PtID-5 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|  UtilityApprox |      Q-count-6 |      PreTime-6 |    InterTime-6 |    PtID-6 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|      UH-Random |      Q-count-7 |      PreTime-7 |    InterTime-7 |    PtID-7 |
-----------------------------------------------------------------------------------
where PtID-0 is the point ID of the user's favorite point (ground truth),
PtID-1 is the point ID of the user's favorite point returned by algorithm DI,
PtID-2 is the point ID of the user's favorite point returned by algorithm EDI,
PtID-3 is the point ID of the user's favorite point returned by algorithm BS,
PtID-4 is the point ID of the user's favorite point returned by algorithm RH,
PtID-5 is the point ID of the user's favorite point returned by algorithm ActiveRanking,
PtID-6 is the point ID of the user's favorite point returned by algorithm UtilityApprox,
PtID-7 is the point ID of the user's favorite point returned by algorithm UH-Random,
Q-count-1 is the number of questions asked by algorithm DI,
Q-count-2 is the number of questions asked by algorithm EDI,
Q-count-3 is the number of questions asked by algorithm BS,
Q-count-4 is the number of questions asked by algorithm RH,
Q-count-5 is the number of questions asked by algorithm ActiveRanking,
Q-count-6 is the number of questions asked by algorithm UtilityApprox,
Q-count-7 is the number of questions asked by algorithm UH-Random,
PreTime-1 is the preprocessing time of algorithm DI,
PreTime-2 is the preprocessing time of algorithm EDI,
PreTime-3 is the preprocessing time of algorithm BS,
PreTime-4 is the preprocessing time of algorithm RH,
PreTime-5 is the preprocessing time of algorithm ActiveRanking,
PreTime-6 is the preprocessing time of algorithm UtilityApprox,
PreTime-7 is the preprocessing time of algorithm UH-Random,
InterTime-1 is the interaction time of algorithm DI,
InterTime-2 is the interaction time of algorithm EDI,
InterTime-3 is the interaction time of algorithm BS,
InterTime-4 is the interaction time of algorithm RH,
InterTime-5 is the interaction time of algorithm ActiveRanking,
InterTime-6 is the interaction time of algorithm UtilityApprox,
InterTime-7 is the interaction time of algorithm UH-Random.

For example, you might see:
-----------------------------------------------------------------------------------
|      Algorithm | # of Questions |  Preprocessing |    Interaction | Point #ID |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|   Ground Truth |              - |              - |              - |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             DI |              6 |       6.679741 |       0.000019 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|            EDI |              7 |       6.776209 |       0.000053 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             BS |              7 |       6.812528 |       0.000082 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|             RH |              8 |       9.794044 |       0.003288 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|  ActiveRanking |             41 |       6.549757 |       0.011926 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|  UtilityApprox |             10 |       0.009483 |       0.101203 |      9607 |
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
|      UH-Random |              8 |       6.810175 |       0.018738 |      9607 |
-----------------------------------------------------------------------------------
