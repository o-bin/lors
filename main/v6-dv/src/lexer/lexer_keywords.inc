// ==========================================
// Lors Compiler v6 - Keyword Recognition
// Layer: Lexer
// ==========================================

algorithm lexer_match_keyword(ident : series) -> whole
begin
    verify (ident == "algorithm") then result TOK_ALGORITHM; conclude
    verify (ident == "begin") then result TOK_BEGIN; conclude
    verify (ident == "end") then result TOK_END; conclude
    verify (ident == "datum") then result TOK_DATUM; conclude
    verify (ident == "verify") then result TOK_VERIFY; conclude
    verify (ident == "then") then result TOK_THEN; conclude
    verify (ident == "otherwise") then result TOK_OTHERWISE; conclude
    verify (ident == "conclude") then result TOK_CONCLUDE; conclude
    verify (ident == "cycle") then result TOK_CYCLE; conclude
    verify (ident == "do") then result TOK_DO; conclude
    verify (ident == "result") then result TOK_RESULT; conclude
    verify (ident == "reveal") then result TOK_REVEAL; conclude
    verify (ident == "incorporate") then result TOK_INCORPORATE; conclude
    verify (ident == "structure") then result TOK_STRUCTURE; conclude

    verify (ident == "whole") then result TOK_TYPE_WHOLE; conclude
    verify (ident == "precise") then result TOK_TYPE_PRECISE; conclude
    verify (ident == "series") then result TOK_TYPE_SERIES; conclude
    verify (ident == "state") then result TOK_TYPE_STATE; conclude
    verify (ident == "void") then result TOK_TYPE_VOID; conclude
    verify (ident == "sequence") then result TOK_TYPE_SEQUENCE; conclude

    verify (ident == "and") then result TOK_AND; conclude
    verify (ident == "or") then result TOK_OR; conclude
    verify (ident == "not") then result TOK_NOT; conclude

    verify (ident == "true" or ident == "false") then result TOK_BOOL; conclude

    result TOK_IDENT;
end
