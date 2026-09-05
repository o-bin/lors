// ==========================================
// Lors Compiler v6 - Batch Compilation (-oall, -iall)
// Layer: Compiler Driver
// ==========================================

algorithm run_batch_compile_all(dbg : state, del_err : state, save_succ : state) -> void
begin
    reveal("Compiling all .lr files to object files (-oall)...");
    execute_system("ls *.lr > .files.tmp 2>/dev/null");

    verify (file_exists(".files.tmp")) then
        datum content : series = file_read(".files.tmp");
        datum clen : whole = length(content);
        datum start_pos : whole = 0;
        datum i : whole = 0;
        cycle (i < clen) do
            datum c : whole = char_at(content, i);
            verify (c == 10) then // '\n'
                datum f : series = substring(content, start_pos, i - start_pos);
                verify (length(f) > 0) then
                    compile_single_file(f, dbg, del_err, save_succ, true);
                conclude
                start_pos = i + 1;
            conclude
            i = i + 1;
        conclude
        verify (start_pos < clen) then
            datum tail_f : series = substring(content, start_pos, clen - start_pos);
            verify (length(tail_f) > 0) then
                compile_single_file(tail_f, dbg, del_err, save_succ, true);
            conclude
        conclude
        file_remove(".files.tmp");
    conclude
end

algorithm run_batch_link_all(target_name : series) -> void
begin
    reveal("Linking all .o object files (-iall)...");
    execute_system("find . -maxdepth 3 -name '*.o' ! -name '.*' > .o_files.tmp 2>/dev/null");

    verify (file_exists(".o_files.tmp")) then
        datum content : series = file_read(".o_files.tmp");
        datum clen : whole = length(content);
        datum cmd : series = "clang ";
        datum has_files : state = false;
        datum start_pos : whole = 0;
        datum i : whole = 0;

        cycle (i < clen) do
            datum c : whole = char_at(content, i);
            verify (c == 10) then
                datum f : series = substring(content, start_pos, i - start_pos);
                verify (length(f) > 0) then
                    cmd = cmd + f + " ";
                    has_files = true;
                conclude
                start_pos = i + 1;
            conclude
            i = i + 1;
        conclude
        verify (start_pos < clen) then
            datum tail_f : series = substring(content, start_pos, clen - start_pos);
            verify (length(tail_f) > 0) then
                cmd = cmd + tail_f + " ";
                has_files = true;
            conclude
        conclude

        verify (has_files) then
            datum out_name : series = "program";
            verify (length(target_name) > 0) then
                out_name = target_name;
            conclude
            cmd = cmd + "-lm -o " + out_name;
            execute_system(cmd);
            verify (file_exists(out_name)) then
                reveal("Success: Linked executable " + out_name);
            otherwise
                reveal("Error: Linking failed");
                exit_program(1);
            conclude
        conclude
        file_remove(".o_files.tmp");
    conclude
end
