build:
	g++ -o curatare curatare.cpp
	g++ -o fortificatii fortificatii.cpp
	g++ -o beamdrone beamdrone.cpp
	g++ -o curse curse.cpp

run-p1:
	./curatare

run-p2:
	./fortificatii

run-p3:
	./beamdrone

run-p4:
	./curse

clean:
	rm curatare
	rm fortificatii
	rm beamdrone
	rm curse
