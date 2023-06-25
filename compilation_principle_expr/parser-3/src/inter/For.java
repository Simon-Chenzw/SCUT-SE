package inter;

import symbols.Type;

public class For extends Stmt {
	Expr expr; Stmt stmt1; Stmt stmt2; Stmt stmt3; 
	
	public For() { expr = null; stmt1 = null; stmt2 = null; stmt3 = null; }
	
	public void init(Stmt s1, Expr x, Stmt s2, Stmt s3) {
		expr = x; stmt1 = s1; stmt2 = s2; stmt3 = s3;
		if( expr.type != Type.Bool ) expr.error("boolean required in do");
	}
	
	// 实验四 中间代码生成
	public void gen(int b, int a) {
		int init_lb = newlabel();
		int expr_lb = newlabel();
		int stmt_lb = newlabel();
		int step_lb = newlabel();
		// init
		emitlabel(init_lb);
		stmt1.gen(b, expr_lb);
		// check expr
		emitlabel(expr_lb);
		expr.jumping(0, a);
		// stmt
		emitlabel(stmt_lb);
		stmt3.gen(expr_lb, step_lb);
		// step
		emitlabel(step_lb);
		stmt2.gen(stmt_lb, expr_lb);
		emit("goto L" + expr_lb);
	}

}
