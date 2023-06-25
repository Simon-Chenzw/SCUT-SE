run: bin/main/Main.class
	java -cp bin main.Main

test1: bin/main/Main.class
	java -cp bin main.Main < test1.decaf

test2: bin/main/Main.class
	java -cp bin main.Main < test2.decaf

bin/main/Main.class: $(wildcard src/**/*)
	javac -d bin src/*/*.java
