package inter;

import symbols.Type;

public class For extends Stmt {

    Stmt first;
    Expr second;
    Stmt third;

    Stmt stmt;

    public For() {
        first = null;
        second = null;
        third = null;
        stmt = null;
    }

    public void init(Stmt fir, Expr sec, Stmt thi, Stmt st) {
        first = fir;
        second = sec;
        third = thi;
        stmt = st;

        // first - Set or SetElem
        if (!(first instanceof Set || first instanceof SetElem))
            first.error("first stmt must be a assign");
        // second - bool
        if (second.type != Type.Bool)
            second.error("second expr must be a boolean");
        // third - Set or SetElem
        if (!(third instanceof Set || third instanceof SetElem))
            third.error("third stmt must be a assign");
    }

    public void display() {
        emit("stmt : for begin");
        stmt.display();
        emit("stmt : for end");
    }
}
