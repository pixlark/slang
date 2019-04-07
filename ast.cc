#define PRETTY_INDENT_MULT 4

enum Expr_Kind {
	EXPR_INTEGER,
};

struct Expr {
	Expr_Kind kind;
	union {
		int integer;
	};
	static Expr * with_kind(Expr_Kind kind)
	{
		Expr * expr = (Expr*) malloc(sizeof(Expr));
		expr->kind = kind;
		return expr;
	}
	char * _to_string(int indent)
	{
		String_Builder builder;
		for (int i = 0; i < indent * PRETTY_INDENT_MULT; i++) {
			builder.append(" ");
		}

		switch (kind) {
		case EXPR_INTEGER: {
			char * s = itoa(integer);
			builder.append(s);
			free(s);
		} break;
		default:
			fatal_internal("Incomplete switch: Expr._to_string()");
		}
		
		return builder.final_string();
	}
	char * to_string()
	{
		return this->_to_string(0);
	}
};

enum Stmt_Kind {
	STMT_LET,
};

struct Stmt_Let {
	Symbol left;
	Expr * right;
};

struct Stmt {
	Stmt_Kind kind;
	union {
		Stmt_Let let;
	};
	static Stmt * with_kind(Stmt_Kind kind)
	{
		Stmt * stmt = (Stmt*) malloc(sizeof(Stmt));
		stmt->kind = kind;
		return stmt;
	}
	char * _to_string(int indent)
	{
		String_Builder builder;
		for (int i = 0; i < indent * PRETTY_INDENT_MULT; i++) {
			builder.append(" ");
		}
		switch (kind) {
		case STMT_LET: {
			char buf[512];
			sprintf(buf, "let %s = \n", let.left);
			builder.append(buf);
			
			char * right_s = let.right->_to_string(indent + 1);
			builder.append(right_s);
			free(right_s);
		} break;
		default:
			fatal_internal("Incomplete switch: Stmt._to_string()");
		}
		return builder.final_string();
	}
	char * to_string()
	{
		return this->_to_string(0);
	}
};
