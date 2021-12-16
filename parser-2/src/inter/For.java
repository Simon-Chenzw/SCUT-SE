package inter;

import symbols.Type;

public class For extends Stmt {
	Expr expr; Stmt stmt1; Stmt stmt2; Stmt stmt3; 
	
	public For() { expr = null; stmt1 = null; stmt2 = null; stmt3 = null; }
	
	public void init(Stmt s1, Expr x, Stmt s2, Stmt s3) {
		expr = x; stmt1 = s1; stmt2 = s2; stmt3 = s3;
		//此处添加对for语句的条件表达式的类型检查，有类型错误时提示for语句语义错误
		// 检查控制语句中的表达式为 bool
		if (expr.type != Type.Bool)
			expr.error("boolean required in while");
		// 初始化语句应为 Set or SetElem
		if (!(stmt1 instanceof Set || stmt1 instanceof SetElem))
			stmt1.error("stmt1 must be a assign");
		// 步增语句应为 Set or SetElem
		if (!(stmt2 instanceof Set || stmt2 instanceof SetElem))
			stmt2.error("stmt2 must be a assign");
	}

	// 实验四 中间代码生成
	public void gen(int b, int a) {
		int init_lb = newlabel();
		int expr_lb = newlabel();
		int stmt_lb = newlabel();
		int step_lb = newlabel();
		// init
		emitlabel(init_lb);
		stmt1.gen(init_lb, expr_lb);
		// check expr
		emitlabel(expr_lb);
		expr.jumping(0, a);
		// stmt
		emitlabel(stmt_lb);
		stmt3.gen(stmt_lb, step_lb);
		// step
		emitlabel(step_lb);
		stmt2.gen(step_lb, expr_lb);
		emit("goto L" + expr_lb);
	}

}
