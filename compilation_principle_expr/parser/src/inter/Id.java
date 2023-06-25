package inter;

import symbols.Type;
import lexer.Word;

// 变量
public class Id extends Expr {

	public int offset; // 内存中的位移

	// 名字 类型 位移
	public Id(Word id, Type p, int b) {
		super(id, p);
		offset = b;
	}
}
