package parser;

import inter.Access;
import inter.And;
import inter.Arith;
import inter.Break;
import inter.Constant;
import inter.Do;
import inter.Else;
import inter.Expr;
import inter.For;
import inter.Id;
import inter.If;
import inter.Not;
import inter.Or;
import inter.Rel;
import inter.Seq;
import inter.Set;
import inter.SetElem;
import inter.Stmt;
import inter.Unary;
import inter.While;

import java.io.IOException;

import symbols.Array;
import symbols.Env;
import symbols.Type;
import lexer.Lexer;
import lexer.Tag;
import lexer.Token;
import lexer.Word;
import lexer.Num;

/**
 * Parser：本次实验的核心部分，内含 Lexer ，有多个成员函数负责构建语法树，主要入口为 program()
 */
public class Parser {

	private Lexer lex; // lexical analyzer for this parser
	private Token look; // lookahead tagen
	Env top = null; // current or top symbol table
	int used = 0; // storage used for declarations

	public Parser(Lexer l) throws IOException {
		lex = l;
		move();
	}

	// 获取下一个 token
	void move() throws IOException {
		look = lex.scan();
	}

	void error(String s) {
		throw new Error("near line " + lex.line + ": " + s);
	}

	// 断定下一个 token
	void match(int t) throws IOException {
		if (look.tag == t)
			move();
		else
			error("syntax error");
	}

	// 解析 程序 （即整个文本）
	public void program() throws IOException { // program -> block
		// build the syntax tree
		Stmt s = block();
		// display the syntax tree
		// only display the stmts, without expr
		s.display();
	}

	// 解析 block
	Stmt block() throws IOException { // block -> { decls stmts }
		match('{');
		// 建立新 env
		Env savedEnv = top;
		top = new Env(top);
		decls();
		Stmt s = stmts();
		match('}');
		// 恢复 env
		top = savedEnv;
		return s;
	}

	// 解析变量声明
	void decls() throws IOException {
		// 循环处理声明
		while (look.tag == Tag.BASIC) { // D -> type ID ;
			Type p = type(); // 类型
			Token tok = look;
			match(Tag.ID);
			match(';');
			Id id = new Id((Word) tok, p, used);
			top.put(tok, id); // 保存在 env
			used = used + p.width; // 开辟空间
		}
	}

	// 获取当前类型，单个 or 数组
	Type type() throws IOException {

		Type p = (Type) look; // expect look.tag == Tag.BASIC
		match(Tag.BASIC);
		if (look.tag != '[')
			return p; // T -> basic
		else
			return dims(p); // return array type
	}

	// 获取数组大小 并返回 Array
	Type dims(Type p) throws IOException {
		match('[');
		Token tok = look;
		match(Tag.NUM);
		match(']');
		if (look.tag == '[')
			p = dims(p);
		return new Array(((Num) tok).value, p);
	}

	// 解析多条语句
	Stmt stmts() throws IOException {
		if (look.tag == '}')
			return Stmt.Null;
		else
			return new Seq(stmt(), stmts());
	}

	// 解析单条语句
	Stmt stmt() throws IOException {
		Expr x;
		Stmt s, s1, s2;
		Stmt savedStmt; // save enclosing loop for breaks

		switch (look.tag) {

		case ';':
			move();
			return Stmt.Null;

		case Tag.IF:
			match(Tag.IF);
			match('(');
			x = bool();
			match(')');
			s1 = stmt();
			if (look.tag != Tag.ELSE)
				return new If(x, s1);
			match(Tag.ELSE);
			s2 = stmt();
			return new Else(x, s1, s2);

		case Tag.FOR:// stmt -> for (assign;bool;assign) stmt
			For fornode = new For();
			savedStmt = Stmt.Enclosing;
			Stmt.Enclosing = fornode;
			match(Tag.FOR);
			// inner stmt start
			match('(');
			s1 = assign_without_semi();
			match(';');
			x = bool();
			match(';');
			s2 = assign_without_semi();
			match(')');
			// inner stmt end
			s = stmt();
			fornode.init(s1, x, s2, s);
			Stmt.Enclosing = savedStmt; // reset Stmt.Enclosing
			return fornode;

		case Tag.WHILE:
			While whilenode = new While();
			savedStmt = Stmt.Enclosing;
			Stmt.Enclosing = whilenode;
			match(Tag.WHILE);
			match('(');
			x = bool();
			match(')');
			s1 = stmt();
			whilenode.init(x, s1);
			Stmt.Enclosing = savedStmt; // reset Stmt.Enclosing
			return whilenode;

		case Tag.DO:
			Do donode = new Do();
			savedStmt = Stmt.Enclosing;
			Stmt.Enclosing = donode;
			match(Tag.DO);
			s1 = stmt();
			match(Tag.WHILE);
			match('(');
			x = bool();
			match(')');
			match(';');
			donode.init(s1, x);
			Stmt.Enclosing = savedStmt; // reset Stmt.Enclosing
			return donode;

		case Tag.BREAK:
			match(Tag.BREAK);
			match(';');
			return new Break();

		case '{':
			return block();

		default:
			return assign();
		}
	}

	// 赋值语句
	Stmt assign() throws IOException {
		Stmt stmt;
		Token t = look;
		match(Tag.ID);
		Id id = top.get(t);
		if (id == null)
			error(t.toString() + " undeclared");

		if (look.tag == '=') { // S -> id = E ;
			move();
			stmt = new Set(id, bool());
		} else { // S -> L = E ;
			Access x = offset(id);
			match('=');
			stmt = new SetElem(x, bool());
		}
		match(';');
		return stmt;
	}

	// 赋值语句 无分号
	// 用于 for 语句
	Stmt assign_without_semi() throws IOException {
		Stmt stmt;
		Token t = look;
		match(Tag.ID);
		Id id = top.get(t);
		if (id == null)
			error(t.toString() + " undeclared");

		if (look.tag == '=') { // S -> id = E ;
			move();
			stmt = new Set(id, bool());
		} else { // S -> L = E ;
			Access x = offset(id);
			match('=');
			stmt = new SetElem(x, bool());
		}
		return stmt;
	}

	// bool 表达式
	// 处理 or
	Expr bool() throws IOException {
		Expr x = join();
		while (look.tag == Tag.OR) {
			Token tok = look;
			move();
			x = new Or(tok, x, join());
		}
		return x;
	}

	// 处理 and
	Expr join() throws IOException {
		Expr x = equality();
		while (look.tag == Tag.AND) {
			Token tok = look;
			move();
			x = new And(tok, x, equality());
		}
		return x;
	}

	// 处理 相等/不等
	Expr equality() throws IOException {
		Expr x = rel();
		while (look.tag == Tag.EQ || look.tag == Tag.NE) {
			Token tok = look;
			move();
			x = new Rel(tok, x, rel());
		}
		return x;
	}

	// 处理比较
	Expr rel() throws IOException {
		Expr x = expr();
		switch (look.tag) {
		case '<':
		case Tag.LE:
		case Tag.GE:
		case '>':
			Token tok = look;
			move();
			return new Rel(tok, x, expr());
		default:
			return x;
		}
	}

	// 处理加减
	Expr expr() throws IOException {
		Expr x = term();
		while (look.tag == '+' || look.tag == '-') {
			Token tok = look;
			move();
			x = new Arith(tok, x, term());
		}
		return x;
	}

	// 处理乘除
	Expr term() throws IOException {
		Expr x = unary();
		while (look.tag == '*' || look.tag == '/') {
			Token tok = look;
			move();
			x = new Arith(tok, x, unary());
		}
		return x;
	}

	// 处理一元运算符
	Expr unary() throws IOException {
		if (look.tag == '-') {
			move();
			return new Unary(Word.minus, unary());
		} else if (look.tag == '!') {
			Token tok = look;
			move();
			return new Not(tok, unary());
		} else
			return factor();
	}

	// 处理 括号/常量
	Expr factor() throws IOException {
		Expr x = null;
		switch (look.tag) {
		case '(':
			move();
			x = bool();
			match(')');
			return x;
		case Tag.NUM:
			x = new Constant(look, Type.Int);
			move();
			return x;
		case Tag.REAL:
			x = new Constant(look, Type.Float);
			move();
			return x;
		case Tag.TRUE:
			x = Constant.True;
			move();
			return x;
		case Tag.FALSE:
			x = Constant.False;
			move();
			return x;
		default:
			error("syntax error");
			return x;
		case Tag.ID:
			String s = look.toString();
			Id id = top.get(look);
			if (id == null)
				error(look.toString() + " undeclared");
			move();
			if (look.tag != '[')
				return id;
			else
				return offset(id);
		}
	}

	Access offset(Id a) throws IOException { // I -> [E] | [E] I
		Expr i;
		Expr w;
		Expr t1, t2;
		Expr loc; // inherit id

		Type type = a.type;
		match('[');
		i = bool();
		match(']'); // first index, I -> [ E ]
		type = ((Array) type).of;
		w = new Constant(type.width);
		t1 = new Arith(new Token('*'), i, w);
		loc = t1;
		while (look.tag == '[') { // multi-dimensional I -> [ E ] I
			match('[');
			i = bool();
			match(']');
			type = ((Array) type).of;
			w = new Constant(type.width);
			t1 = new Arith(new Token('*'), i, w);
			t2 = new Arith(new Token('+'), loc, t1);
			loc = t2;
		}

		return new Access(a, loc, type);
	}
}
