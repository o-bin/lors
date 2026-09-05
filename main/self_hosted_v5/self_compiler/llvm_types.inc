// Symbol Table and Type Inference
datum sym_names : sequence<series>;
datum sym_types : sequence<series>;
datum sym_scopes : sequence<whole>;
datum current_scope : whole = 0;

datum func_names : sequence<series>;
datum func_ret_types : sequence<series>;

algorithm push_scope() -> void
begin
    current_scope = current_scope + 1;
end

algorithm pop_scope() -> void
begin
    // Remove symbols from the current scope
    datum i : whole = length(sym_names) - 1;
    cycle (i >= 0 and sym_scopes[i] == current_scope) do
        // Pop elements
        datum new_names : sequence<series>;
        datum new_types : sequence<series>;
        datum new_scopes : sequence<whole>;
        datum j : whole = 0;
        cycle (j < i) do
            append(new_names, sym_names[j]);
            append(new_types, sym_types[j]);
            append(new_scopes, sym_scopes[j]);
            j = j + 1;
        conclude
        sym_names = new_names;
        sym_types = new_types;
        sym_scopes = new_scopes;
        i = i - 1;
    conclude
    current_scope = current_scope - 1;
end

algorithm add_symbol(name : series, type : series) -> void
begin
    append(sym_names, name);
    append(sym_types, type);
    append(sym_scopes, current_scope);
end

algorithm get_symbol_type(name : series) -> series
begin
    datum i : whole = length(sym_names) - 1;
    cycle (i >= 0) do
        verify (sym_names[i] == name) then
            result sym_types[i];
        conclude
        i = i - 1;
    conclude

    // Check if it's a global function (first class citizens?)
    // Actually, functions might be stored separately.
    result "unknown";
end

algorithm get_symbol_scope(name : series) -> whole
begin
    datum i : whole = length(sym_names) - 1;
    cycle (i >= 0) do
        verify (sym_names[i] == name) then
            result sym_scopes[i];
        conclude
        i = i - 1;
    conclude
    result -1;
end

algorithm add_func(name : series, ret_type : series) -> void
begin
    append(func_names, name);
    append(func_ret_types, ret_type);
end

algorithm get_func_ret_type(name : series) -> series
begin
    datum i : whole = length(func_names) - 1;
    cycle (i >= 0) do
        verify (func_names[i] == name) then
            result func_ret_types[i];
        conclude
        i = i - 1;
    conclude
    result "unknown";
end

// Struct Tables
datum struct_names : sequence<series>;
datum struct_field_parent : sequence<whole>;
datum struct_field_names : sequence<series>;
datum struct_field_types : sequence<series>;

algorithm add_struct(name : series) -> whole
begin
    datum idx : whole = length(struct_names);
    append(struct_names, name);
    result idx;
end

algorithm get_struct_idx(name : series) -> whole
begin
    datum i : whole = length(struct_names) - 1;
    cycle (i >= 0) do
        verify (struct_names[i] == name) then
            result i;
        conclude
        i = i - 1;
    conclude
    result -1;
end

algorithm add_struct_field(s_idx : whole, fname : series, ftype : series) -> void
begin
    append(struct_field_parent, s_idx);
    append(struct_field_names, fname);
    append(struct_field_types, ftype);
end

algorithm get_struct_field_type(s_name : series, f_name : series) -> series
begin
    datum s_idx : whole = get_struct_idx(s_name);
    verify (s_idx == -1) then
        result "unknown";
    conclude
    
    datum i : whole = length(struct_field_names) - 1;
    cycle (i >= 0) do
        verify (struct_field_parent[i] == s_idx) then
            verify (struct_field_names[i] == f_name) then
                result struct_field_types[i];
            conclude
        conclude
        i = i - 1;
    conclude
    result "unknown";
end

// Forward declarations
algorithm map_type_node(node_idx : whole) -> series;
algorithm propagate_block(node_idx : whole) -> void;

// Helper to retrieve previously propagated type during codegen phase
algorithm get_expr_type(node_idx : whole) -> series
begin
    verify (node_idx == -1) then result "void"; conclude
    datum node : ASTNode = node_heap[node_idx];
    verify (node.resolved_type != "") then result node.resolved_type; conclude

    datum k : whole = node.kind;

    verify (k == NODE_LITERAL) then
        verify (node.value_type == "whole") then result "i64"; conclude
        verify (node.value_type == "precise") then result "double"; conclude
        verify (node.value_type == "series") then result "i8*"; conclude
        verify (node.value_type == "state") then result "i1"; conclude
        result "i64"; // Default;
    conclude

    verify (k == NODE_IDENTIFIER) then
        datum t : series = get_symbol_type(node.text_val);
        verify (t != "unknown") then result t; conclude
        result "i64"; // Default fallback;
    conclude

    verify (k == NODE_BINARY_OP) then
        datum op : series = node.op;
        datum lt : series = get_expr_type(node.left);
        datum rt : series = get_expr_type(node.right);

        // Logical
        datum is_logical_op : state = false;
        verify (op == "not") then is_logical_op = true; conclude
        verify (op == "and") then is_logical_op = true; conclude
        verify (op == "or") then is_logical_op = true; conclude
        verify (op == "==") then is_logical_op = true; conclude
        verify (op == "!=") then is_logical_op = true; conclude
        verify (op == "<") then is_logical_op = true; conclude
        verify (op == ">") then is_logical_op = true; conclude
        verify (op == "<=") then is_logical_op = true; conclude
        verify (op == ">=") then is_logical_op = true; conclude

        verify (is_logical_op) then
            result "i1";
        conclude

        // Math / string concatenation
        datum is_ptr_op : state = false;
        verify (lt == "i8*") then is_ptr_op = true; conclude
        verify (rt == "i8*") then is_ptr_op = true; conclude
        verify (is_ptr_op) then result "i8*"; conclude // String concatenation;

        datum is_dbl_op : state = false;
        verify (lt == "double") then is_dbl_op = true; conclude
        verify (rt == "double") then is_dbl_op = true; conclude
        verify (is_dbl_op) then result "double"; conclude

        result "i64";
    conclude

    verify (k == NODE_FUNC_CALL) then
        datum fname : series = node.text_val;

        // Built-ins
        datum is_str_fn : state = false;
        verify (fname == "to_string") then is_str_fn = true; conclude
        verify (fname == "substring") then is_str_fn = true; conclude
        verify (fname == "to_upper") then is_str_fn = true; conclude
        verify (fname == "to_lower") then is_str_fn = true; conclude
        verify (fname == "reverse") then is_str_fn = true; conclude
        verify (fname == "character") then is_str_fn = true; conclude
        verify (fname == "file_read") then is_str_fn = true; conclude
        verify (fname == "env_get") then is_str_fn = true; conclude
        verify (fname == "arg_value") then is_str_fn = true; conclude

        datum is_dbl_fn : state = false;
        verify (fname == "power") then is_dbl_fn = true; conclude
        verify (fname == "root") then is_dbl_fn = true; conclude
        verify (fname == "sine") then is_dbl_fn = true; conclude
        verify (fname == "cosine") then is_dbl_fn = true; conclude
        verify (fname == "tangent") then is_dbl_fn = true; conclude
        verify (fname == "absolute") then is_dbl_fn = true; conclude
        verify (fname == "to_precise") then is_dbl_fn = true; conclude

        datum is_bool_fn : state = false;
        verify (fname == "file_exists") then is_bool_fn = true; conclude
        verify (fname == "is_digit") then is_bool_fn = true; conclude
        verify (fname == "is_alpha") then is_bool_fn = true; conclude
        verify (fname == "is_alnum") then is_bool_fn = true; conclude
        verify (fname == "is_space") then is_bool_fn = true; conclude
        verify (fname == "is_upper") then is_bool_fn = true; conclude
        verify (fname == "is_lower") then is_bool_fn = true; conclude

        datum is_int_fn : state = false;
        verify (fname == "length") then is_int_fn = true; conclude
        verify (fname == "to_integer") then is_int_fn = true; conclude
        verify (fname == "arg_count") then is_int_fn = true; conclude
        verify (fname == "char_at") then is_int_fn = true; conclude

        datum is_void_fn : state = false;
        verify (fname == "reveal") then is_void_fn = true; conclude
        verify (fname == "file_write") then is_void_fn = true; conclude
        verify (fname == "file_remove") then is_void_fn = true; conclude
        verify (fname == "execute_system") then is_void_fn = true; conclude
        verify (fname == "append") then is_void_fn = true; conclude
        verify (fname == "exit_program") then is_void_fn = true; conclude
        
        verify (is_str_fn) then result "i8*"; conclude
        verify (is_dbl_fn) then result "double"; conclude
        verify (is_bool_fn) then result "i1"; conclude
        verify (is_int_fn) then result "i64"; conclude
        verify (is_void_fn) then result "void"; conclude

        datum t : series = get_func_ret_type(fname);
        verify (t != "unknown") then result t; conclude
        result "i64";
    conclude

    verify (k == NODE_ARRAY_ACCESS) then
        // If it's an array, it's a pointer to the sub-type
        datum arr_t : series = get_symbol_type(node.text_val);
        // E.g. "i64*" -> "i64"
        verify (substring(arr_t, length(arr_t) - 1, 1) == "*") then
            result substring(arr_t, 0, length(arr_t) - 1);
        conclude
        result "i64";
    conclude

    verify (k == NODE_MEMBER_ACCESS) then
        // Complex to track without struct definitions in type table.
        // We'll need a struct_fields table, but for now fallback to i64.
        // Actually, we must track struct types.
        result "i64";
    conclude

    result "i64";
end

// --- AST Type Propagation Pass ---

algorithm type_error(msg : series) -> void
begin
    reveal("Type Error: " + msg);
    exit_program(1);
end

algorithm propagate_type(node_idx : whole) -> series
begin
    verify (node_idx == -1) then result "void"; conclude

    datum node : ASTNode = node_heap[node_idx];
    datum k : whole = node.kind;

    verify (node.resolved_type != "") then
        result node.resolved_type;
    conclude

    datum res_type : series = "void";

    verify (k == NODE_LITERAL) then
        verify (node.value_type == "whole") then res_type = "i64"; conclude
        verify (node.value_type == "precise") then res_type = "double"; conclude
        verify (node.value_type == "series") then res_type = "i8*"; conclude
        verify (node.value_type == "state") then res_type = "i1"; conclude
    conclude

    verify (k == NODE_IDENTIFIER) then
        res_type = get_symbol_type(node.text_val);
        verify (res_type == "unknown") then
            // Check if it's a function name
            res_type = get_func_ret_type(node.text_val);
            verify (res_type == "unknown") then
                type_error("Undeclared identifier: " + node.text_val);
            conclude
        conclude
    conclude

    verify (k == NODE_BINARY_OP) then
        datum lt : series = propagate_type(node.left);
        datum rt : series = propagate_type(node.right);

        datum op : series = node.op;
        datum is_logical_op : state = false;
        verify (op == "not") then is_logical_op = true; conclude
        verify (op == "and") then is_logical_op = true; conclude
        verify (op == "or") then is_logical_op = true; conclude
        verify (op == "==") then is_logical_op = true; conclude
        verify (op == "!=") then is_logical_op = true; conclude
        verify (op == "<") then is_logical_op = true; conclude
        verify (op == ">") then is_logical_op = true; conclude
        verify (op == "<=") then is_logical_op = true; conclude
        verify (op == ">=") then is_logical_op = true; conclude

        datum is_ptr_op : state = false;
        verify (lt == "i8*") then is_ptr_op = true; conclude
        verify (rt == "i8*") then is_ptr_op = true; conclude

        datum is_dbl_op : state = false;
        verify (lt == "double") then is_dbl_op = true; conclude
        verify (rt == "double") then is_dbl_op = true; conclude

        res_type = "i64";
        verify (is_dbl_op) then res_type = "double"; conclude
        verify (is_ptr_op) then res_type = "i8*"; conclude
        verify (is_logical_op) then res_type = "i1"; conclude
    conclude

    verify (k == NODE_FUNC_CALL) then
        // Resolve arguments first
        datum i : whole = 0;
        datum args : sequence<whole> = node.children;
        datum len : whole = length(args);
        cycle (i < len) do
            propagate_type(args[i]);
            i = i + 1;
        conclude

        datum fname : series = node.text_val;

        // Built-ins
        datum is_str_fn : state = false;
        verify (fname == "to_string") then is_str_fn = true; conclude
        verify (fname == "substring") then is_str_fn = true; conclude
        verify (fname == "to_upper") then is_str_fn = true; conclude
        verify (fname == "to_lower") then is_str_fn = true; conclude
        verify (fname == "reverse") then is_str_fn = true; conclude
        verify (fname == "character") then is_str_fn = true; conclude
        verify (fname == "file_read") then is_str_fn = true; conclude
        verify (fname == "env_get") then is_str_fn = true; conclude
        verify (fname == "arg_value") then is_str_fn = true; conclude

        datum is_int_fn : state = false;
        verify (fname == "length") then is_int_fn = true; conclude
        verify (fname == "to_integer") then is_int_fn = true; conclude
        verify (fname == "arg_count") then is_int_fn = true; conclude
        verify (fname == "char_at") then is_int_fn = true; conclude

        datum is_dbl_fn : state = false;
        verify (fname == "power") then is_dbl_fn = true; conclude
        verify (fname == "root") then is_dbl_fn = true; conclude
        verify (fname == "sine") then is_dbl_fn = true; conclude
        verify (fname == "cosine") then is_dbl_fn = true; conclude
        verify (fname == "tangent") then is_dbl_fn = true; conclude
        verify (fname == "absolute") then is_dbl_fn = true; conclude
        verify (fname == "to_precise") then is_dbl_fn = true; conclude

        datum is_bool_fn : state = false;
        verify (fname == "file_exists") then is_bool_fn = true; conclude
        verify (fname == "is_digit") then is_bool_fn = true; conclude
        verify (fname == "is_alpha") then is_bool_fn = true; conclude
        verify (fname == "is_alnum") then is_bool_fn = true; conclude
        verify (fname == "is_space") then is_bool_fn = true; conclude
        verify (fname == "is_upper") then is_bool_fn = true; conclude
        verify (fname == "is_lower") then is_bool_fn = true; conclude

        datum s_idx : whole = get_struct_idx(fname);

        datum is_builtin : state = false;
        verify (is_str_fn) then is_builtin = true; res_type = "i8*"; conclude
        datum is_void_fn : state = false;
        verify (fname == "reveal") then is_void_fn = true; conclude
        verify (fname == "file_write") then is_void_fn = true; conclude
        verify (fname == "file_remove") then is_void_fn = true; conclude
        verify (fname == "execute_system") then is_void_fn = true; conclude
        verify (fname == "append") then is_void_fn = true; conclude
        verify (fname == "exit_program") then is_void_fn = true; conclude

        verify (is_str_fn) then is_builtin = true; res_type = "i8*"; conclude
        verify (is_int_fn) then is_builtin = true; res_type = "i64"; conclude
        verify (is_dbl_fn) then is_builtin = true; res_type = "double"; conclude
        verify (is_bool_fn) then is_builtin = true; res_type = "i1"; conclude
        verify (is_void_fn) then is_builtin = true; res_type = "void"; conclude

        verify (not is_builtin) then
            verify (s_idx != -1) then
                 res_type = "%struct." + fname;
            otherwise
                 res_type = get_func_ret_type(fname);
                 verify (res_type == "unknown") then
                      type_error("Undeclared function: " + fname);
                 conclude
            conclude
        conclude
    conclude

    verify (k == NODE_ARRAY_LITERAL) then
        datum els : sequence<whole> = node.children;
        datum len : whole = length(els);
        verify (len > 0) then
             datum i : whole = 0;
             cycle (i < len) do
                 propagate_type(els[i]);
                 i = i + 1;
             conclude
        conclude
        res_type = "i8*"; // Opaque pointer;
    conclude

    verify (k == NODE_ARRAY_ACCESS) then
        datum base_t : series = get_symbol_type(node.text_val);
        propagate_type(node.condition); // Evaluate index;

        verify (substring(base_t, length(base_t) - 1, 1) == "*") then
            res_type = substring(base_t, 0, length(base_t) - 1);
        otherwise
            type_error("Cannot index into non-array type: " + base_t);
        conclude
    conclude

    verify (k == NODE_MEMBER_ACCESS) then
        datum base_t : series = propagate_type(node.left);

        verify (substring(base_t, length(base_t) - 1, 1) == "*") then
            base_t = substring(base_t, 0, length(base_t) - 1);
        conclude

        verify (substring(base_t, 0, 8) == "%struct.") then
            datum s_name : series = substring(base_t, 8, length(base_t) - 8);
            res_type = get_struct_field_type(s_name, node.text_val);
            verify (res_type == "unknown") then
                type_error("Struct " + s_name + " has no field '" + node.text_val + "'");
            conclude
        otherwise
            type_error("Cannot access member of non-struct type: " + base_t);
        conclude
    conclude

    verify (k == NODE_INQUIRE) then
        // If it was already set by a VAR_DECL or ASSIGN, use that.
        // Otherwise default to i64 (whole)
        res_type = node_heap[node_idx].resolved_type;
        verify (res_type == "") then
            res_type = "i64";
        conclude
    conclude

    node_heap[node_idx].resolved_type = res_type;
    result res_type;
end

algorithm propagate_stmt(node_idx : whole) -> void
begin
    verify (node_idx == -1) then result; conclude
    datum node : ASTNode = node_heap[node_idx];
    datum k : whole = node.kind;

    verify (k == NODE_VAR_DECL) then
        datum t : series = map_type_node(node.type_node);
        add_symbol(node.text_val, t);
        verify (node.initializer != -1) then
            // Set type of inquire based on variable type
            verify (node_heap[node.initializer].kind == NODE_INQUIRE) then
                node_heap[node.initializer].resolved_type = t;
            conclude
            propagate_type(node.initializer);
        conclude
    conclude

    verify (k == NODE_ASSIGN) then
        datum var_t : series = get_symbol_type(node.text_val);
        // Set type of inquire based on target type
        verify (node_heap[node.initializer].kind == NODE_INQUIRE) then
            node_heap[node.initializer].resolved_type = var_t;
        conclude
        propagate_type(node.initializer);
        // We could verify assignment type compatibility here
    conclude

    verify (k == NODE_ARRAY_ASSIGN) then
        datum arr_t : series = get_symbol_type(node.text_val);
        propagate_type(node.initializer);
        propagate_type(node.condition); // The index;
    conclude

    verify (k == NODE_MEMBER_ASSIGN) then
        propagate_type(node.left); // Propagate the base pointer;
        propagate_type(node.initializer);
    conclude

    verify (k == NODE_EXPR_STMT) then
        verify (node.initializer != -1) then
            propagate_type(node.initializer);
        conclude
    conclude

    verify (k == NODE_RETURN) then
        verify (node.initializer != -1) then
            propagate_type(node.initializer);
        conclude
    conclude

    verify (k == NODE_IF) then
        propagate_type(node.condition);
        propagate_block(node.then_branch);
        verify (node.else_branch != -1) then
            propagate_block(node.else_branch);
        conclude
    conclude

    verify (k == NODE_WHILE) then
        propagate_type(node.condition);
        propagate_block(node.then_branch);
    conclude

    verify (k == NODE_BLOCK) then
        propagate_block(node_idx);
    conclude
end

algorithm propagate_block(node_idx : whole) -> void
begin
    push_scope();
    datum blk : ASTNode = node_heap[node_idx];
    datum i : whole = 0;
    datum stmts : sequence<whole> = blk.children;
    datum len : whole = length(stmts);
    cycle (i < len) do
        propagate_stmt(stmts[i]);
        i = i + 1;
    conclude
    pop_scope();
end

// Main Entry Point for Type Propagation
algorithm run_type_propagation(prog_idx : whole) -> void
begin
    datum i : whole = 0;
    datum children : sequence<whole> = node_heap[prog_idx].children;
    datum len : whole = length(children);

    // First Pass: Collect all global functions and structs to allow forward references
    cycle (i < len) do
        datum decl_idx : whole = children[i];
        datum k : whole = node_heap[decl_idx].kind;

        verify (k == NODE_STRUCT_DECL) then
            datum sname : series = node_heap[decl_idx].text_val;
            datum s_idx : whole = add_struct(sname);

            datum j : whole = 0;
            datum schildren : sequence<whole> = node_heap[decl_idx].children;
            datum flen : whole = length(schildren);
            cycle (j < flen) do
                datum fidx : whole = schildren[j];
                datum fname : series = node_heap[fidx].text_val;
                datum ftype : series = map_type_node(node_heap[fidx].type_node);
                add_struct_field(s_idx, fname, ftype);
                j = j + 1;
            conclude
        conclude

        verify (k == NODE_FUNC_DECL) then
            datum fname : series = node_heap[decl_idx].text_val;
            datum rtype : series = map_type_node(node_heap[decl_idx].type_node);
            verify (fname == "genesis") then rtype = "i32"; conclude
            add_func(fname, rtype);
        conclude

        i = i + 1;
    conclude

    // Second Pass: Propagate types in all bodies
    i = 0;
    cycle (i < len) do
        datum decl_idx : whole = children[i];
        datum k : whole = node_heap[decl_idx].kind;

        verify (k == NODE_VAR_DECL) then
            datum t : series = map_type_node(node_heap[decl_idx].type_node);
            add_symbol(node_heap[decl_idx].text_val, t);
            verify (node_heap[decl_idx].initializer != -1) then
                propagate_type(node_heap[decl_idx].initializer);
            conclude
        conclude

        datum is_func_decl_with_body : state = false;
        verify (k == NODE_FUNC_DECL) then
            verify (node_heap[decl_idx].then_branch != -1) then
                is_func_decl_with_body = true;
            conclude
        conclude

        verify (is_func_decl_with_body) then
            push_scope();
            // Add params to scope
            datum j : whole = 0;
            datum fchildren : sequence<whole> = node_heap[decl_idx].children;
            datum plen : whole = length(fchildren);
            cycle (j < plen) do
                datum pidx : whole = fchildren[j];
                datum pname : series = node_heap[pidx].text_val;
                datum ptype : series = map_type_node(node_heap[pidx].type_node);
                add_symbol(pname, ptype);
                j = j + 1;
            conclude

            // Propagate block directly to avoid duplicate scope pushing
            datum blk : ASTNode = node_heap[node_heap[decl_idx].then_branch];
            datum bi : whole = 0;
            datum bstmts : sequence<whole> = blk.children;
            datum blen : whole = length(bstmts);
            cycle (bi < blen) do
                propagate_stmt(bstmts[bi]);
                bi = bi + 1;
            conclude

            pop_scope();
        conclude

        i = i + 1;
    conclude
end
