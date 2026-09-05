// ==========================================
// Lors Compiler v6 - Single File Compilation Pipeline
// Layer: Driver
// ==========================================

algorithm run_backend_compilation(ll_file : series, out_bin : series, is_obj : state, dbg : state, del_err : state, save_succ : state) -> void
begin
    datum cmd : series = "clang -Wno-override-module ";
    verify (is_obj) then
        cmd = cmd + "-c " + ll_file + " -o " + out_bin;
    otherwise
        cmd = cmd + ll_file + " -lm -o " + out_bin;
    conclude

    datum log_file : series = out_bin + ".log";
    cmd = cmd + " > " + log_file + " 2>&1";

    verify (file_exists(out_bin)) then
        file_remove(out_bin);
    conclude

    execute_system(cmd);

    verify (file_exists(out_bin)) then
        verify (save_succ == false) then
            file_remove(ll_file);
        conclude
        file_remove(log_file);
    otherwise
        verify (dbg) then
            verify (file_exists(log_file)) then
                datum err_txt : series = file_read(log_file);
                reveal(err_txt);
            conclude
        otherwise
            reveal("Error: Backend compilation failed for " + out_bin + ". Use -debug for details.");
        conclude

        file_remove(log_file);
        verify (del_err) then
            file_remove(ll_file);
        conclude
        exit_program(1);
    conclude
end

algorithm compile_single_file(input_file : series, dbg : state, del_err : state, save_succ : state, obj_out : state) -> void
begin
    datum flen : whole = length(input_file);
    verify (flen == 0) then
        reveal("Error: No input file specified.");
        exit_program(1);
    conclude

    verify (path_is_safe(input_file) == false) then
        reveal("Error: Unsafe path: " + input_file);
        exit_program(1);
    conclude

    verify (file_exists(input_file) == false) then
        reveal("Error: File not found: " + input_file);
        exit_program(1);
    conclude

    datum base_name : series = input_file;
    verify (str_ends_with(input_file, ".lr")) then
        base_name = substring(input_file, 0, flen - 3);
    otherwise
        verify (str_ends_with(input_file, ".inc")) then
            base_name = substring(input_file, 0, flen - 4);
        conclude
    conclude

    inc_init();
    datum processed_code : series = "";
    verify (str_ends_with(input_file, ".inc")) then
        verify (str_ends_with(input_file, "constants.inc") == false) then
            processed_code = preprocess_file("src/common/constants.inc") + "\n";
        conclude
        verify (str_ends_with(input_file, "declarations.inc") == false) then
            processed_code = processed_code + preprocess_file("src/common/declarations.inc") + "\n";
        conclude
    conclude
    processed_code = processed_code + preprocess_file(input_file);

    lexer_state_init(processed_code);
    lexer_tokenize();

    ast_init();
    parser_init();
    datum prog_node : whole = parse_program();

    run_semantic_analysis(prog_node);

    datum llvm_ir : series = cg_generate_module(prog_node);
    datum ll_file : series = base_name + ".ll";
    file_write(ll_file, llvm_ir);

    datum out_bin : series = base_name;
    verify (obj_out) then
        out_bin = base_name + ".o";
    conclude

    run_backend_compilation(ll_file, out_bin, obj_out, dbg, del_err, save_succ);
end
