// ==========================================
// Lors Compiler v6 - Main Driver Genesis
// ==========================================

algorithm genesis() -> whole
begin
    cli_parse_options();

    verify (flag_oall) then
        run_batch_compile_all(flag_debug, flag_delete_on_error, flag_save_on_success);
        result 0;
    conclude

    verify (flag_iall) then
        run_batch_link_all(flag_ns_name);
        result 0;
    conclude

    verify (length(cli_input_file) == 0) then
        reveal("Usage: compiler <script>.lr [-debug] [-d] [-s] [-o] | -oall | -iall [-ns <name>]");
        result 0;
    conclude

    compile_single_file(cli_input_file, flag_debug, flag_delete_on_error, flag_save_on_success, flag_object_output);
    result 0;
end
