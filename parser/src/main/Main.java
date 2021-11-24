package main;

import java.io.IOException;

import parser.Parser;
import lexer.Lexer;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Lexer lex = new Lexer();
		Parser parser = new Parser(lex);
		parser.program();
		System.out.print("\n");
	}

}
