package inter;

import symbols.Type;
import lexer.Token;

// expr 中的算数运算 Node
public class Arith extends Op {

	   public Expr expr1, expr2;

	   // tok 为运算符
	   // x1 x2 为运算符两端
	   // 通过 Type.max 计算 x1 x2 的类型是否兼容
	   // 以及隐式转换为何种类型
	   public Arith(Token tok, Expr x1, Expr x2)  {
	      super(tok, null); expr1 = x1; expr2 = x2;
	      type = Type.max(expr1.type, expr2.type);
	      if (type == null ) error("type error");
	   }

	   public Expr gen() {
	      return new Arith(op, expr1.reduce(), expr2.reduce());
	   }

	   public String toString() {
	      return expr1.toString()+" "+op.toString()+" "+expr2.toString();
	   }
	}
