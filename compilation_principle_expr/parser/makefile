run: bin/main/Main.class
	java -cp bin main.Main

example: bin/main/Main.class
	java -cp bin main.Main < example.decaf

example2: bin/main/Main.class
	java -cp bin main.Main < example2.decaf

bin/main/Main.class: $(wildcard src/**/*)
	javac -d bin src/*/*.java
