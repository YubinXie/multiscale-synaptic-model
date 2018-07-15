do

mkdir "d"$fname
cp Model_8-9-Normal-Initial.cps "d"$fname"/Model_8-9-Normal_"$fname".cps"

# cd into directory corresponding to that file and submit Copasi run to queue
cd "d"$fname
#select appropriate directory
qsub -o log.txt -cwd ~/s1507524/CopasiSE "/Model_8-9-Normal_"$f".cps"  cd ..

done
