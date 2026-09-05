// ==========================================
// Lors Compiler v6 - File Reader
// ==========================================

algorithm read_source_file(filepath : series) -> series
begin
    verify (file_exists(filepath) == false) then
        reveal("Error: File not found: " + filepath);
        exit_program(1);
    conclude
    datum content : series = file_read(filepath);
    result content;
end
