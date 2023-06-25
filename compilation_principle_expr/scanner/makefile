run: bin/main/Main.class
	java -cp bin main.Main

bin/main/Main.class: $(wildcard src/**/*)
	javac -d bin src/*/*.java
