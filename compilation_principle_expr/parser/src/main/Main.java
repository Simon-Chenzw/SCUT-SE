package main;

import java.io.IOException;

import parser.Parser;
import lexer.Lexer;
import lexer.Token;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Lexer lex = new Lexer();
		Parser parser = new Parser(lex);
		parser.program();
		System.out.print("\n");
	}

	// public static void main(String[] args) throws IOException {
	// Lexer lexer = new Lexer();
	// Token token = lexer.scan();
	// while (token.tag != 65535) {
	// System.out.println("(" + Integer.toString(token.tag) + ", " +
	// token.toString() + " )");
	// token = lexer.scan();
	// }
	// }
}
