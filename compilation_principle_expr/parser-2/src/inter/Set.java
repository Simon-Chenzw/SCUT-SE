package inter;

import symbols.Type;

// 赋值语句 Node
public class Set extends Stmt {

   public Id id; public Expr expr;

   public Set(Id i, Expr x) {
      id = i; expr = x;
      // 检查变量声明的类型与右侧表达式的值是否相同
      if ( check(id.type, expr.type) == null ) error("type error");
   }

   // 检查 p1 与 p2 是否满足赋值语句的类型要求
   public Type check(Type p1, Type p2) {
      if ( Type.numeric(p1) && Type.numeric(p2) ) return p2;
      else if ( p1 == Type.Bool && p2 == Type.Bool ) return p2;
      else return null;
   }

   public void gen(int b, int a) {
      emit( id.toString() + " = " + expr.gen().toString() );
   }
}