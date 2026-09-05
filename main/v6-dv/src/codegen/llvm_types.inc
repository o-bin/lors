// ==========================================
// Lors Compiler v6 - LLVM Type Mapping
// Layer: Code Generation
// ==========================================

algorithm llvm_get_type(tag : whole, tname : series) -> series
begin
    verify (tag == TYPE_WHOLE) then
        result "i64";
    conclude
    verify (tag == TYPE_PRECISE) then
        result "double";
    conclude
    verify (tag == TYPE_SERIES) then
        result "ptr";
    conclude
    verify (tag == TYPE_STATE) then
        result "i1";
    conclude
    verify (tag == TYPE_VOID) then
        result "void";
    conclude
    verify (tag == TYPE_SEQUENCE) then
        result "ptr";
    conclude
    verify (tag == TYPE_STRUCT) then
        result "ptr";
    conclude

    // Check by name if tag was unknown
    verify (tname == "whole") then result "i64"; conclude
    verify (tname == "precise") then result "double"; conclude
    verify (tname == "series") then result "ptr"; conclude
    verify (tname == "state") then result "i1"; conclude
    verify (tname == "void") then result "void"; conclude
    verify (str_starts_with(tname, "sequence<")) then result "ptr"; conclude

    verify (length(tname) > 0) then
        result "ptr";
    conclude

    result "i64";
end

algorithm llvm_get_raw_struct_type(struct_name : series) -> series
begin
    result "%struct." + struct_name;
end
