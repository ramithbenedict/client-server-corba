cd obj
g++ -c ../src/*.cpp -I ../include -I ../lib/omniorb/include --std=c++1y -Wall
g++ -o ../bin/projet *.o -Wl,-rpath,'$ORIGIN' -L../lib/omniorb/lib -lCOS4 -lCOSDynamic4 -lomniCodeSets4 -lomniConnectionMgmt4 -lomniORB4 -lomnithread -lomniZIOP4 -lomniZIOPDynamic4 -lomniDynamic4
cd ..