package main;

import java.io.IOException;

import lexer.Lexer;
import lexer.Token;

/// 程序函数入口
public class Main {
	public static void main(String[] args) throws IOException {
		/// 使用 lexer 处理读入直到 '\n'
		Lexer lexer = new Lexer();
		// char c;
		do {
			Token token = lexer.scan();
			switch (token.tag) {
			/// 依据 tag 的值，识别当前的 token 的类型，依此输出类型
			case 270:
			case 272:
				System.out.println("(NUM , " + token.toString() + ")");
				break;
			case 264:
				System.out.println("(ID , " + token.toString() + ")");
				break;
			case 256:
			case 257:
			case 258:
			case 259:
			case 260:
			case 265:
			case 274:
			case 275:
				System.out.println("(KEY , " + token.toString() + ")");
				break;
			case 13:
				break;
			/** custom */
			case 300:
				System.out.println("(STR , " + token.toString() + ")");
				break;
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 306:
			case 307:
			case 308:
			case 309:
			case 310:
			case 311:
			case 312:
			case 313:
			case 314:
			case 315:
			case 316:
			case 317:
				System.out.println("(KEY , " + token.toString() + ")");
				break;

			case 400:
				return;

			default:
				System.out.println("(SYM , " + token.toString() + ")");
				break;
			}

		} while (lexer.getPeek() != '\n');
	}
}
