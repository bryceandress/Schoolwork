all: build

.PHONY: build doc test

build:
	javac -d build src/oware/*.java

#play:
	#java -classpath build oware.Game -s

play:
	java -classpath build oware.GUI

doc:
	javadoc -d doc -private -sourcepath src oware

test:
	java -classpath build oware.Board > test/test.out
	diff test/test.out test/test.ref

clean:
	rm -rf build/oware
	rm -rf doc
	rm -f test/test.out
