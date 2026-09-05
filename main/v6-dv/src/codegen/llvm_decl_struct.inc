// ==========================================
// Lors Compiler v6 - Struct Type Codegen
// ==========================================

algorithm cg_emit_struct_definition(node_id : whole) -> void
begin
    datum sname : series = ast_get_s_val(node_id);
    datum cnt : whole = ast_get_child_count(node_id);

    datum fields_str : series = "";
    datum i : whole = 0;
    cycle (i < cnt) do
        datum f_node : whole = ast_get_child(node_id, i);
        datum f_tag : whole = ast_get_type_tag(f_node);
        datum f_tname : series = ast_get_type_name(f_node);
        datum f_ltype : series = llvm_get_type(f_tag, f_tname);

        verify (i > 0) then fields_str = fields_str + ", "; conclude
        fields_str = fields_str + f_ltype;
        i = i + 1;
    conclude

    verify (cnt == 0) then
        fields_str = "i64";
    conclude

    cg_emit_line("%struct." + sname + " = type { " + fields_str + " }");
end
