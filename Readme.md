# Analysis 1:- Major Contributing pollutant for wildfires
To compile:-
g++ -o main.exe 
C:\Users\016915509\Desktop\21feb275\275_mini2\src\main\main.cpp 
C:\Users\016915509\Desktop\21feb275\275_mini2\src\data_loading\loadData.cpp 
C:\Users\016915509\Desktop\21feb275\275_mini2\src\data_analysis\analyzeData.cpp 
-I C:\Users\016915509\Desktop\21feb275\275_mini2\src\models 
-I "C:\MS_MPI\SDK\Include" -L "C:\MS_MPI\SDK\Lib\x86" 
-lmsmpi -std=c++17

To run:-
mpiexec -n 4 main
 <!--number of procceses  can be modified accordingly -->

# Analysis 2:- Hotspot Analysis
To compile:-
g++ -o main2.exe C:\Users\016915509\Desktop\21feb275\275_mini2\src\main\main2.cpp C:\Users\016915509\Desktop\21feb275\275_mini2\src\data_loading\loadDataHotspot.cpp  C:\Users\016915509\Desktop\21feb275\275_mini2\src\data_analysis\analyzeHotspot.cpp -I C:\Users\016915509\Desktop\21feb275\275_mini2\src\models -I "C:\MS_MPI\SDK\Include" -L "C:\MS_MPI\SDK\Lib\x86" -lmsmpi -std=c++17

to run:-
mpiexec -n 4 main2
<!--number of procceses  can be modified accordingly -->