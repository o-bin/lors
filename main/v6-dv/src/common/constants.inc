// ==========================================
// Lors Compiler v6 - Token & AST Constants
// ==========================================

// Token Categories
datum TOK_EOF : whole = 0;
datum TOK_IDENT : whole = 1;
datum TOK_INT : whole = 2;
datum TOK_FLOAT : whole = 3;
datum TOK_STRING : whole = 4;
datum TOK_BOOL : whole = 5;

// Keywords
datum TOK_ALGORITHM : whole = 10;
datum TOK_BEGIN : whole = 11;
datum TOK_END : whole = 12;
datum TOK_DATUM : whole = 13;
datum TOK_VERIFY : whole = 14;
datum TOK_THEN : whole = 15;
datum TOK_OTHERWISE : whole = 16;
datum TOK_CONCLUDE : whole = 17;
datum TOK_CYCLE : whole = 18;
datum TOK_DO : whole = 19;
datum TOK_RESULT : whole = 20;
datum TOK_REVEAL : whole = 21;
datum TOK_INCORPORATE : whole = 22;
datum TOK_STRUCTURE : whole = 23;

// Primitive and Builtin Types
datum TOK_TYPE_WHOLE : whole = 30;
datum TOK_TYPE_PRECISE : whole = 31;
datum TOK_TYPE_SERIES : whole = 32;
datum TOK_TYPE_STATE : whole = 33;
datum TOK_TYPE_VOID : whole = 34;
datum TOK_TYPE_SEQUENCE : whole = 35;

// Punctuation & Delimiters
datum TOK_LPAREN : whole = 40;     // (
datum TOK_RPAREN : whole = 41;     // )
datum TOK_LBRACK : whole = 42;     // [
datum TOK_RBRACK : whole = 43;     // ]
datum TOK_LBRACE : whole = 44;     // {
datum TOK_RBRACE : whole = 45;     // }
datum TOK_COLON : whole = 46;      // :
datum TOK_SEMICOLON : whole = 47;  // ;
datum TOK_COMMA : whole = 48;      // ,
datum TOK_DOT : whole = 49;        // .
datum TOK_ARROW : whole = 50;      // ->

// Operators
datum TOK_ASSIGN : whole = 51;     // =
datum TOK_PLUS : whole = 52;       // +
datum TOK_MINUS : whole = 53;      // -
datum TOK_STAR : whole = 54;       // *
datum TOK_SLASH : whole = 55;      // /
datum TOK_PERCENT : whole = 56;    // %
datum TOK_EQ : whole = 57;         // ==
datum TOK_NEQ : whole = 58;        // !=
datum TOK_LT : whole = 59;         // <
datum TOK_LTE : whole = 60;        // <=
datum TOK_GT : whole = 61;         // >
datum TOK_GTE : whole = 62;        // >=
datum TOK_AND : whole = 63;        // and
datum TOK_OR : whole = 64;         // or
datum TOK_NOT : whole = 65;        // not

// AST Node Types
datum AST_INT : whole = 1;
datum AST_FLOAT : whole = 2;
datum AST_STRING : whole = 3;
datum AST_BOOL : whole = 4;
datum AST_IDENT : whole = 5;

datum AST_BINOP : whole = 10;
datum AST_UNOP : whole = 11;
datum AST_CALL : whole = 12;
datum AST_MEMBER : whole = 13;
datum AST_INDEX : whole = 14;
datum AST_ARRAY_LIT : whole = 15;
datum AST_STRUCT_CONSTR : whole = 16;

datum AST_DATUM_DECL : whole = 20;
datum AST_ASSIGN : whole = 21;
datum AST_MEMBER_ASSIGN : whole = 22;
datum AST_INDEX_ASSIGN : whole = 23;
datum AST_VERIFY : whole = 24;
datum AST_CYCLE : whole = 25;
datum AST_RESULT : whole = 26;
datum AST_REVEAL : whole = 27;
datum AST_EXPR_STMT : whole = 28;
datum AST_BLOCK : whole = 29;

datum AST_STRUCT_DECL : whole = 40;
datum AST_ALGORITHM_DECL : whole = 41;
datum AST_GLOBAL_DATUM : whole = 42;
datum AST_PROGRAM : whole = 43;

// Semantic Type Tags
datum TYPE_UNKNOWN : whole = 0;
datum TYPE_WHOLE : whole = 1;
datum TYPE_PRECISE : whole = 2;
datum TYPE_SERIES : whole = 3;
datum TYPE_STATE : whole = 4;
datum TYPE_VOID : whole = 5;
datum TYPE_SEQUENCE : whole = 6;
datum TYPE_STRUCT : whole = 7;
