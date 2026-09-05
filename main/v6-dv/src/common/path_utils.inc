// ==========================================
// Lors Compiler v6 - Path Utilities
// Layer: Common
// ==========================================

algorithm path_dirname(filepath : series) -> series
begin
    datum flen : whole = length(filepath);
    verify (flen == 0) then
        result ".";
    conclude
    datum last_slash : whole = -1;
    datum i : whole = flen - 1;
    cycle (i >= 0) do
        datum c : whole = char_at(filepath, i);
        verify (c == 47) then // '/'
            last_slash = i;
            i = -1;
        otherwise
            i = i - 1;
        conclude
    conclude

    verify (last_slash == -1) then
        result ".";
    conclude
    verify (last_slash == 0) then
        result "/";
    conclude
    datum dir : series = substring(filepath, 0, last_slash);
    result dir;
end

algorithm path_basename(filepath : series) -> series
begin
    datum flen : whole = length(filepath);
    verify (flen == 0) then
        result "";
    conclude
    datum last_slash : whole = -1;
    datum i : whole = flen - 1;
    cycle (i >= 0) do
        datum c : whole = char_at(filepath, i);
        verify (c == 47) then
            last_slash = i;
            i = -1;
        otherwise
            i = i - 1;
        conclude
    conclude

    verify (last_slash == -1) then
        result filepath;
    conclude
    datum base : series = substring(filepath, last_slash + 1, flen - (last_slash + 1));
    result base;
end

algorithm path_is_safe(filepath : series) -> state
begin
    datum flen : whole = length(filepath);
    datum i : whole = 0;
    cycle (i < flen) do
        datum c : whole = char_at(filepath, i);
        // Disallow dangerous shell characters
        verify (c == 59 or c == 38 or c == 124 or c == 96 or c == 36) then
            result false;
        conclude
        i = i + 1;
    conclude
    result true;
end

algorithm path_join(dir : series, file : series) -> series
begin
    datum cur_dir : series = dir;
    datum cur_file : series = file;

    cycle (str_starts_with(cur_file, "../")) do
        cur_dir = path_dirname(cur_dir);
        datum flen : whole = length(cur_file);
        cur_file = substring(cur_file, 3, flen - 3);
    conclude

    cycle (str_starts_with(cur_file, "./")) do
        datum flen2 : whole = length(cur_file);
        cur_file = substring(cur_file, 2, flen2 - 2);
    conclude

    datum dlen : whole = length(cur_dir);
    verify (dlen == 0 or cur_dir == ".") then
        result cur_file;
    conclude
    datum last_c : whole = char_at(cur_dir, dlen - 1);
    verify (last_c == 47) then
        result cur_dir + cur_file;
    conclude
    result cur_dir + "/" + cur_file;
end
