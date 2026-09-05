// ==========================================
// Lors Compiler v6 - Error Reporting
// ==========================================

datum err_total_count : whole = 0;
datum err_warn_count : whole = 0;
datum err_current_file : series;

algorithm error_init(filename : series) -> void
begin
    err_total_count = 0;
    err_warn_count = 0;
    err_current_file = filename;
end

algorithm error_report(msg : series, line : whole, col : whole) -> void
begin
    err_total_count = err_total_count + 1;
    datum loc : series = err_current_file;
    verify (length(loc) > 0) then
        loc = loc + ":";
    conclude
    loc = loc + to_string(line) + ":" + to_string(col) + ": ";
    reveal("Error: " + loc + msg);
end

algorithm warning_report(msg : series, line : whole, col : whole) -> void
begin
    err_warn_count = err_warn_count + 1;
    datum loc : series = err_current_file;
    verify (length(loc) > 0) then
        loc = loc + ":";
    conclude
    loc = loc + to_string(line) + ":" + to_string(col) + ": ";
    reveal("Warning: " + loc + msg);
end

algorithm error_fatal(msg : series, line : whole, col : whole) -> void
begin
    error_report(msg, line, col);
    exit_program(1);
end

algorithm error_has_occurred() -> state
begin
    verify (err_total_count > 0) then
        result true;
    conclude
    result false;
end

algorithm error_get_count() -> whole
begin
    result err_total_count;
end
