build: buildArbori buildIntersectii buildPozitie

buildArbori:
	gcc -o arboriTest arboriTest.c arbori_intervale.c -Wall -g

buildIntersectii:
	gcc -o intersectiiTest intersectiiTest.c arbori_intervale.c intersectii.c -Wall -g

buildPozitie:
	gcc -o pozitieTest pozitieTest.c arbori_intervale.c pozitie_libera.c -Wall -g

runTestArbori:
	./arboriTest

runTestIntersectii:
	./intersectiiTest

runTestPozitie:
	./pozitieTest

clean:
	rm -rf arboriTest pozitieTest intersectiiTest *.o