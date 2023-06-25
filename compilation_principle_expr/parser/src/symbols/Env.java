package symbols;

import inter.Id;

import java.util.Hashtable;

import lexer.Token;

// 储存 token -> id
public class Env {
	// 当前键值
	private Hashtable<Token, Id> table;

	// 父 env
	protected Env prev;

	public Env(Env n) {
		table = new Hashtable<Token, Id>();
		prev = n;
	}

	// 添加键值
	public void put(Token w, Id i) {
		table.put(w, i);
	}

	// 递归获取键值
	public Id get(Token w) {
		for (Env e = this; e != null; e = e.prev) {
			Id found = (Id) (e.table.get(w));
			if (found != null)
				return found;
		}
		return null;
	}
}
