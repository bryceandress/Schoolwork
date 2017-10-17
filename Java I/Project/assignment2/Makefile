all: build

.PHONY: build doc test

build:
	javac -d build src/oware/*.java

play:
	java -classpath build oware.Game -n

doc:
	javadoc -d doc -private -sourcepath src oware

test:
	java -classpath build oware.Board > test/test.out
	vimdiff test/test.out test/test.ref

clean:
	rm -rf build/oware
	rm -rf doc
	rm -f test/test.out
