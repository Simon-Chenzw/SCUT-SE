package lexer;

import java.io.IOException;
import java.util.Hashtable;

public class Lexer {

	public static int line = 1;
	char peek = ' ';
	Hashtable<String, Word> words = new Hashtable<String, Word>();

	/// 将 Word 储存至 Hashtable
	void reserve(Word w) {
		words.put(w.lexeme, w);
	}

	/// 构造函数
	/// 初始化时将关键字储存至 Hashtable 中
	public Lexer() {
		reserve(new Word("if", Tag.IF));
		reserve(new Word("else", Tag.ELSE));
		reserve(new Word("while", Tag.WHILE));
		reserve(new Word("do", Tag.DO));
		reserve(new Word("break", Tag.BREAK));
		reserve(Word.True);
		reserve(Word.False);

		/** custom */
		reserve(new Word("void", Tag.VOID));
		reserve(new Word("int", Tag.INT));
		reserve(new Word("double", Tag.DOUBLE));
		reserve(new Word("bool", Tag.BOOL));
		reserve(new Word("string", Tag.STRING));
		reserve(new Word("class", Tag.CLASS));
		reserve(new Word("null", Tag.NULL));
		reserve(new Word("this", Tag.THIS));
		reserve(new Word("extends", Tag.EXTENDS));
		reserve(new Word("for", Tag.FOR));
		reserve(new Word("return", Tag.RETURN));
		reserve(new Word("new", Tag.NEW));
		reserve(new Word("NewArray", Tag.NEWARRAY));
		reserve(new Word("Print", Tag.PRINT));
		reserve(new Word("ReadInteger", Tag.READINT));
		reserve(new Word("ReadLine", Tag.READLINE));
		reserve(new Word("static", Tag.STATIC));
	}

	/// 获取下一字符，并储存在 peek 中
	public void readch() throws IOException {
		peek = (char) System.in.read();
		// Check for illegal characters
		String illegal = "@";
		if (illegal.indexOf(peek) != -1) {
			System.err.println("illegal characters: " + peek);
			System.exit(1);
		}
	}

	/// 判断下一个字符是否是 c
	boolean readch(char c) throws IOException {
		readch();
		if (peek != c) {
			return false;
		}
		peek = ' ';
		return true;
	}

	/// 核心文本解析函数
	public Token scan() throws IOException {
		/// 过滤空字符
		for (;; readch()) {
			if (peek == ' ' || peek == '\t')
				continue;
			else if (peek == '\n') {
				line += 1;
			} else {
				break;
			}
		}
		/// 识别特殊符号
		switch (peek) {
		case '&':
			if (readch('&'))
				return Word.and;
			else
				return new Token('&');
		case '|':
			if (readch('|'))
				return Word.or;
			else
				return new Token('|');
		case '=':
			if (readch('='))
				return Word.eq;
			else
				return new Token('=');
		case '!':
			if (readch('='))
				return Word.ne;
			else
				return new Token('!');
		case '<':
			if (readch('='))
				return Word.le;
			else
				return new Token('<');
		case '>':
			if (readch('='))
				return Word.ge;
			else
				return new Token('>');
		}
		/// 数字处理
		if (Character.isDigit(peek)) {
			// modify No.1: solve 0xabc
			if (peek == '0') {
				if (readch('x')) {
					readch();
					int v = 0;
					do {
						v = 16 * v + Character.digit(peek, 10);
						readch();
					} while (Character.isDigit(peek));
					return new Num(v);
				} else if (!Character.isDigit(peek)) {
					return new Num(0);
				}
			}
			// End No.1

			int v = 0;
			do {
				v = 10 * v + Character.digit(peek, 10);
				readch();
			} while (Character.isDigit(peek));
			if (peek != '.')
				return new Num(v);
			/// 浮点数处理：
			float x = v;
			float d = 10;
			for (;;) {
				readch();
				if (!Character.isDigit(peek)) {
					/// 浮点数 科学技术法处理
					// modify No.2: solve 1.1E+2
					if (peek == 'E' || peek == 'e') {
						System.out.println(peek);
						readch();
						if (peek == '+' || peek == '-') {
							int pos = peek == '+' ? 1 : -1;
							readch();
							int pow = 0;
							while (Character.isDigit(peek)) {
								pow = 10 * pow + Character.digit(peek, 10);
								readch();
							}
							return new Real(x * (float) Math.pow(10, pow) * pos);
						} else {
							break;
						}
					} else {
						break;
					}
					// End No.2
				}
				x = x + Character.digit(peek, 10) / d;
				d = d * 10;
			}
			return new Real(x);
		}
		/// 关键字处理
		if (Character.isLetter(peek)) {
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek);
				readch();
			} while (Character.isLetterOrDigit(peek));
			String s = b.toString();
			Word w = (Word) words.get(s);
			if (w != null)
				return w;
			w = new Word(s, Tag.ID);
			words.put(s, w);
			return w;
		}

		/// 字符串处理
		// modify No.3: string
		if (peek == '"') {
			String tmp = "";
			readch();
			do {
				if (peek == '\n') {
					System.err.println("There can be no '\\n' in the string literal");
					System.exit(1);
				}
				tmp += peek;
				readch();
			} while (peek != '"');
			readch();
			return new Word(tmp, Tag.STR);
		}
		// End No.3

		/// 注释处理
		// modify No.4: comment
		if (peek == '/') {
			readch();
			if (peek == '/') {
				while (peek != '\n')
					readch();
				readch();
				return scan();
			} else if (peek == '*') {
				readch();
				char last = '\0';
				do {
					last = peek;
					readch();
				} while (last != '*' || peek != '/');
				readch();
				return scan();
			}
		}
		// End No.4

		// eof
		if ((int) peek == 65535) {
			return new Token(Tag.EOF);
		}

		Token tok = new Token(peek);
		peek = ' ';
		return tok;
	}

	public void out() {
		System.out.println(words.size());
	}

	public char getPeek() {
		return peek;
	}

	public void setPeek(char peek) {
		this.peek = peek;
	}

}
