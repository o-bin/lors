// ==========================================
// Lors Compiler v6 - Codegen Environment & Register Allocation
// Layer: Code Generation
// ==========================================

datum cg_temp_count : whole = 0;
datum cg_label_count : whole = 0;

datum cg_var_names_data : series;
datum cg_var_ptrs_data : series;
datum cg_var_types_data : series;
datum cg_var_tnames_data : series;
datum cg_var_count : whole = 0;
datum cg_current_func_ret_ltype : series;

datum cg_defined_functions : series;
datum cg_declared_functions : series;
datum cg_external_decls : series;
datum cg_external_globals : series;
datum cg_defined_globals : series;

algorithm cg_env_module_init() -> void
begin
    cg_defined_functions = ";";
    cg_declared_functions = ";";
    cg_external_decls = "";
    cg_external_globals = ";";
    cg_defined_globals = ";";
end

algorithm cg_env_reset_function() -> void
begin
    cg_temp_count = 0;
    cg_label_count = 0;
    cg_var_names_data = "";
    cg_var_ptrs_data = "";
    cg_var_types_data = "";
    cg_var_tnames_data = "";
    cg_var_count = 0;
    cg_current_func_ret_ltype = "void";
end

algorithm cg_new_temp() -> series
begin
    datum tname : series = "%t" + to_string(cg_temp_count);
    cg_temp_count = cg_temp_count + 1;
    result tname;
end

algorithm cg_new_label(prefix : series) -> series
begin
    datum lname : series = prefix + "_" + to_string(cg_label_count);
    cg_label_count = cg_label_count + 1;
    result lname;
end

algorithm cg_register_var(name : series, ptr_reg : series, llvm_type : series, tname : series) -> void
begin
    cg_var_names_data = str_list_add(cg_var_names_data, name);
    cg_var_ptrs_data = str_list_add(cg_var_ptrs_data, ptr_reg);
    cg_var_types_data = str_list_add(cg_var_types_data, llvm_type);
    cg_var_tnames_data = str_list_add(cg_var_tnames_data, tname);
    cg_var_count = cg_var_count + 1;
end

algorithm cg_get_var_ptr(name : series) -> series
begin
    datum i : whole = cg_var_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(cg_var_names_data, i);
        verify (n == name) then
            result str_list_get(cg_var_ptrs_data, i);
        conclude
        i = i - 1;
    conclude

    verify (str_contains(cg_defined_globals, ";" + name + ";") == false and str_contains(cg_external_globals, ";" + name + ";") == false) then
        cg_external_globals = cg_external_globals + name + ";";
    conclude
    result "@global_" + name;
end

algorithm cg_get_var_type(name : series) -> series
begin
    datum i : whole = cg_var_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(cg_var_names_data, i);
        verify (n == name) then
            result str_list_get(cg_var_types_data, i);
        conclude
        i = i - 1;
    conclude
    datum gtag : whole = sym_get_var_type(name);
    verify (gtag != TYPE_UNKNOWN) then
        datum gtname : series = sym_get_var_type_name(name);
        result llvm_get_type(gtag, gtname);
    conclude

    // Cross-module global variable heuristics
    verify (str_starts_with(name, "cg_") and name != "cg_temp_count" and name != "cg_label_count" and name != "cg_var_count") then
        result "ptr";
    conclude
    verify (str_ends_with(name, "_data") or str_ends_with(name, "_pages") or str_ends_with(name, "_str") or str_ends_with(name, "_name") or str_ends_with(name, "_src") or name == "lex_src" or name == "inc_visited_str" or name == "cli_input_file" or name == "cg_current_func_ret_ltype" or name == "parsed_type_name" or name == "cg_external_globals" or name == "cg_defined_globals" or name == "cg_defined_functions" or name == "cg_declared_functions" or name == "cg_external_decls") then
        result "ptr";
    conclude
    verify (str_starts_with(name, "flag_") or name == "flag_debug" or name == "flag_oall" or name == "flag_iall" or name == "flag_object_output" or name == "flag_delete_on_error" or name == "flag_save_on_success") then
        result "i1";
    conclude

    result "i64";
end

algorithm cg_get_var_struct_name(name : series) -> series
begin
    datum i : whole = cg_var_count - 1;
    cycle (i >= 0) do
        datum n : series = str_list_get(cg_var_names_data, i);
        verify (n == name) then
            result str_list_get(cg_var_tnames_data, i);
        conclude
        i = i - 1;
    conclude
    result "";
end
