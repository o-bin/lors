// ==========================================
// Lors Compiler v6 - Symbol Storage
// Layer: Semantic Analysis
// ==========================================

datum sym_names_data : series;
datum sym_type_tags_data : series;
datum sym_type_names_data : series;
datum sym_scopes_data : series;
datum sym_count : whole = 0;
datum sym_current_scope : whole = 0;

datum fn_names_data : series;
datum fn_ret_tags_data : series;
datum fn_ret_names_data : series;
datum fn_param_counts_data : series;
datum fn_count : whole = 0;
