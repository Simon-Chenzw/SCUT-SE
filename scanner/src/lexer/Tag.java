package lexer;

public class Tag {
	/// 硬编码各种 tag
	public final static int AND = 256, BASIC = 257, BREAK = 258, DO = 259, ELSE = 260, EQ = 261, FALSE = 262, GE = 263,
			ID = 264, IF = 265, INDEX = 266, LE = 267, MINUS = 268, NE = 269, NUM = 270, OR = 271, REAL = 272,
			TEMP = 273, TRUE = 274, WHILE = 275,
			/** custom */
			STR = 300, VOID = 301, INT = 302, DOUBLE = 303, BOOL = 304, STRING = 305, CLASS = 306, NULL = 307,
			THIS = 308, EXTENDS = 309, FOR = 310, RETURN = 311, NEW = 312, NEWARRAY = 313, PRINT = 314, READINT = 315,
			READLINE = 316, STATIC = 317, EOF = 400;
}
