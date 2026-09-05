// ==========================================
// Lors Compiler v6 - CLI Options Parser
// Layer: Driver
// ==========================================

datum flag_debug : state;
datum flag_delete_on_error : state;
datum flag_save_on_success : state;
datum flag_object_output : state;
datum flag_oall : state;
datum flag_iall : state;
datum flag_ns_name : series;
datum cli_input_file : series;

algorithm cli_parse_options() -> void
begin
    flag_debug = false;
    flag_delete_on_error = false;
    flag_save_on_success = false;
    flag_object_output = false;
    flag_oall = false;
    flag_iall = false;
    flag_ns_name = "";
    cli_input_file = "";

    datum argc : whole = arg_count();
    datum i : whole = 1;

    cycle (i < argc) do
        datum arg : series = arg_value(i);
        datum handled : state = false;

        verify (arg == "-debug") then flag_debug = true; handled = true; conclude
        verify (arg == "-d") then flag_delete_on_error = true; handled = true; conclude
        verify (arg == "-s") then flag_save_on_success = true; handled = true; conclude
        verify (arg == "-o") then flag_object_output = true; handled = true; conclude
        verify (arg == "-oall") then flag_oall = true; handled = true; conclude
        verify (arg == "-iall") then flag_iall = true; handled = true; conclude

        verify (arg == "-ns") then
            verify (i + 1 < argc) then
                flag_ns_name = arg_value(i + 1);
                i = i + 1;
                handled = true;
            otherwise
                reveal("Error: -ns requires a name parameter");
                exit_program(1);
            conclude
        conclude

        verify (handled == false and str_starts_with(arg, "-")) then
            reveal("Error: Unknown flag: " + arg);
            exit_program(1);
        conclude

        verify (handled == false) then
            cli_input_file = arg;
        conclude

        i = i + 1;
    conclude
end
