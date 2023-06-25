package inter;

import symbols.Array;
import symbols.Type;
import lexer.Token;

// 关系运算 Node
// 运算的左右两端应该具有相同的类型
public class Rel extends Logical {

   public Rel(Token tok, Expr x1, Expr x2) { super(tok, x1, x2); }

   // 检查左右两端的类型
   public Type check(Type p1, Type p2) {
      // 数组不应存在于关系运算
      if ( p1 instanceof Array || p2 instanceof Array ) return null;
      // 检查是否相同
      else if( p1 == p2 ) return Type.Bool;
      else return null;
   }

   public void jumping(int t, int f) {
      Expr a = expr1.reduce();
      Expr b = expr2.reduce();
      String test = a.toString() + " " + op.toString() + " " + b.toString();
      emitjumps(test, t, f);
   }
}
