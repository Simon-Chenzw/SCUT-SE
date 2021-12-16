run: bin/main/Main.class
	java -cp bin main.Main

test1: bin/main/Main.class
	java -cp bin main.Main < test1.decaf

test2: bin/main/Main.class
	java -cp bin main.Main < test2.decaf

test3: bin/main/Main.class
	java -cp bin main.Main < test3.decaf

test4: bin/main/Main.class
	java -cp bin main.Main < test4.decaf

bin/main/Main.class: $(wildcard src/**/*)
	javac -d bin src/*/*.java
