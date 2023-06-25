package inter;

import lexer.Lexer;

/**
 * 语法树中的基础类型，inter 中所有类型的基类。所有类型的继承关系详见： inter.gv / inter.png
 */
public class Node {
	int lexline = 0;

	Node() {
		lexline = Lexer.line;
	}

	void error(String s) {
		throw new Error("near line " + lexline + ": " + s);
	}

	static int labels = 0;

	public int newlabel() {
		return ++labels;
	}

	public void emitlabel(int i) {
		System.out.print("L" + i + ":");
	}

	public void emit(String s) {
		System.out.println("\t" + s);
	}
}
