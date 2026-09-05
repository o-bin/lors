@.str.newline = linkonce_odr unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.fmt_i64 = linkonce_odr unnamed_addr constant [6 x i8] c"%lld\0A\00", align 1
@.str.fmt_f64 = linkonce_odr unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.fmt_str = linkonce_odr unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.read_mode = linkonce_odr unnamed_addr constant [3 x i8] c"rb\00", align 1
@.str.write_mode = linkonce_odr unnamed_addr constant [3 x i8] c"wb\00", align 1
@.str.sprintf_i64 = linkonce_odr unnamed_addr constant [5 x i8] c"%lld\00", align 1
@.str.sprintf_f64 = linkonce_odr unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.scanf_i64 = linkonce_odr unnamed_addr constant [5 x i8] c"%lld\00", align 1
@.str.scanf_f64 = linkonce_odr unnamed_addr constant [4 x i8] c"%lf\00", align 1
@.str.scanf_str = linkonce_odr unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.empty = linkonce_odr unnamed_addr constant [1 x i8] zeroinitializer, align 1
@__argc = internal global i32 0
@__argv = internal global i8** null
; ModuleID = 'lors_module'

declare i32 @printf(i8*, ...)
declare i8* @malloc(i64)
declare void @free(i8*)
declare i8* @strcpy(i8*, i8*)
declare i8* @strcat(i8*, i8*)
declare i64 @strlen(i8*)
declare i32 @strcmp(i8*, i8*)
declare i32 @sprintf(i8*, i8*, ...)
declare i8* @strstr(i8*, i8*)
declare i8* @strncpy(i8*, i8*, i64)
declare i8* @fopen(i8*, i8*)
declare i64 @fread(i8*, i64, i64, i8*)
declare i64 @fwrite(i8*, i64, i64, i8*)
declare i32 @fclose(i8*)
declare i32 @fseek(i8*, i64, i32)
declare i64 @ftell(i8*)
declare i32 @remove(i8*)
declare i32 @scanf(i8*, ...)
declare i32 @system(i8*)
declare void @exit(i32)
declare i32 @access(i8*, i32)
declare i8* @getenv(i8*)
declare double @pow(double, double)
declare double @sqrt(double)
declare double @sin(double)
declare double @cos(double)
declare double @tan(double)
declare double @abs(double)
declare double @atof(i8*)
declare i32 @toupper(i32)
declare i32 @tolower(i32)
declare i32 @isalnum(i32)
declare i32 @isalpha(i32)
declare i32 @isdigit(i32)
declare i32 @isspace(i32)
declare i32 @islower(i32)
declare i32 @isupper(i32)


define linkonce_odr i8* @__to_upper(i8* %str) {
entry:
    %len = call i64 @strlen(i8* %str)
    %sz_plus = add i64 %len, 1
    %mem = call i8* @malloc(i64 %sz_plus)
    br label %cond
cond:
    %i = phi i64 [ 0, %entry ], [ %i_next, %body ]
    %cmp = icmp slt i64 %i, %len
    br i1 %cmp, label %body, label %end
body:
    %src_ptr = getelementptr inbounds i8, i8* %str, i64 %i
    %char = load i8, i8* %src_ptr
    %char_ext = zext i8 %char to i32
    %upper_i32 = call i32 @toupper(i32 %char_ext)
    %upper_char = trunc i32 %upper_i32 to i8
    %dst_ptr = getelementptr inbounds i8, i8* %mem, i64 %i
    store i8 %upper_char, i8* %dst_ptr
    %i_next = add i64 %i, 1
    br label %cond
end:
    %null_ptr = getelementptr inbounds i8, i8* %mem, i64 %len
    store i8 0, i8* %null_ptr
    ret i8* %mem
}

define linkonce_odr i8* @__to_lower(i8* %str) {
entry:
    %len = call i64 @strlen(i8* %str)
    %sz_plus = add i64 %len, 1
    %mem = call i8* @malloc(i64 %sz_plus)
    br label %cond
cond:
    %i = phi i64 [ 0, %entry ], [ %i_next, %body ]
    %cmp = icmp slt i64 %i, %len
    br i1 %cmp, label %body, label %end
body:
    %src_ptr = getelementptr inbounds i8, i8* %str, i64 %i
    %char = load i8, i8* %src_ptr
    %char_ext = zext i8 %char to i32
    %lower_i32 = call i32 @tolower(i32 %char_ext)
    %lower_char = trunc i32 %lower_i32 to i8
    %dst_ptr = getelementptr inbounds i8, i8* %mem, i64 %i
    store i8 %lower_char, i8* %dst_ptr
    %i_next = add i64 %i, 1
    br label %cond
end:
    %null_ptr = getelementptr inbounds i8, i8* %mem, i64 %len
    store i8 0, i8* %null_ptr
    ret i8* %mem
}

define linkonce_odr i1 @__is_alnum_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @isalnum(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr void @__append(i8** %dest_ptr, i8* %src) {
entry:
    %ptr_is_null = icmp eq i8** %dest_ptr, null
    br i1 %ptr_is_null, label %early_exit, label %do_append

do_append:
    %dest = load i8*, i8** %dest_ptr
    %cmp1 = icmp eq i8* %dest, null
    %safe_dest = select i1 %cmp1, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %dest
    %cmp2 = icmp eq i8* %src, null
    %safe_src = select i1 %cmp2, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %src
    %len1 = call i64 @strlen(i8* %safe_dest)
    %len2 = call i64 @strlen(i8* %safe_src)
    %total_len = add i64 %len1, %len2
    %total_size = add i64 %total_len, 1
    %mem = call i8* @malloc(i64 %total_size)
    call i8* @strcpy(i8* %mem, i8* %safe_dest)
    call i8* @strcat(i8* %mem, i8* %safe_src)
    store i8* %mem, i8** %dest_ptr
    br label %early_exit

early_exit:
    ret void
}

define linkonce_odr i1 @__is_digit_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @isdigit(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr i1 @__is_lower_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @islower(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr i1 @__is_upper_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @isupper(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr i1 @__is_alpha_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @isalpha(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr i1 @__is_space_whole(i64 %c) {
entry:
    %c_trunc = trunc i64 %c to i32
    %res = call i32 @isspace(i32 %c_trunc)
    %cmp = icmp ne i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr i8* @__str_concat(i8* %s1, i8* %s2) {
entry:
    %cmp1 = icmp eq i8* %s1, null
    %safe_s1 = select i1 %cmp1, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %s1
    %cmp2 = icmp eq i8* %s2, null
    %safe_s2 = select i1 %cmp2, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %s2
    %len1 = call i64 @strlen(i8* %safe_s1)
    %len2 = call i64 @strlen(i8* %safe_s2)
    %total_len = add i64 %len1, %len2
    %total_size = add i64 %total_len, 1
    %mem = call i8* @malloc(i64 %total_size)
    call i8* @strcpy(i8* %mem, i8* %safe_s1)
    call i8* @strcat(i8* %mem, i8* %safe_s2)
    ret i8* %mem
}
define linkonce_odr i8* @__to_string_whole(i64 %val) {
entry:
    %mem = call i8* @malloc(i64 32)
    call i32 (i8*, i8*, ...) @sprintf(i8* %mem, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.sprintf_i64, i64 0, i64 0), i64 %val)
    ret i8* %mem
}
define linkonce_odr i8* @__to_string_precise(double %val) {
entry:
    %mem = call i8* @malloc(i64 64)
    call i32 (i8*, i8*, ...) @sprintf(i8* %mem, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.sprintf_f64, i64 0, i64 0), double %val)
    ret i8* %mem
}
define linkonce_odr i8* @__file_read(i8* %path) {
entry:
    %fp = call i8* @fopen(i8* %path, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.read_mode, i64 0, i64 0))
    %isnull = icmp eq i8* %fp, null
    br i1 %isnull, label %error, label %ok
ok:
    call i32 @fseek(i8* %fp, i64 0, i32 2)
    %size = call i64 @ftell(i8* %fp)
    call i32 @fseek(i8* %fp, i64 0, i32 0)
    %sz_plus = add i64 %size, 1
    %buf = call i8* @malloc(i64 %sz_plus)
    call i64 @fread(i8* %buf, i64 1, i64 %size, i8* %fp)
    call i32 @fclose(i8* %fp)
    %end_ptr = getelementptr inbounds i8, i8* %buf, i64 %size
    store i8 0, i8* %end_ptr
    ret i8* %buf
error:
    %errbuf = call i8* @malloc(i64 1)
    store i8 0, i8* %errbuf
    ret i8* %errbuf
}
define linkonce_odr void @__file_write(i8* %path, i8* %content) {
entry:
    %fp = call i8* @fopen(i8* %path, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.write_mode, i64 0, i64 0))
    %isnull = icmp eq i8* %fp, null
    br i1 %isnull, label %error, label %ok
ok:
    %len = call i64 @strlen(i8* %content)
    call i64 @fwrite(i8* %content, i64 1, i64 %len, i8* %fp)
    call i32 @fclose(i8* %fp)
    ret void
error:
    ret void
}

define linkonce_odr i64 @arg_count() {
entry:
    %val = load i32, i32* @__argc
    %ext = sext i32 %val to i64
    ret i64 %ext
}

define linkonce_odr i8* @arg_value(i64 %i) {
entry:
    %ptr = load i8**, i8*** @__argv
    %item_ptr = getelementptr i8*, i8** %ptr, i64 %i
    %val = load i8*, i8** %item_ptr
    ret i8* %val
}

define linkonce_odr void @exit_program(i64 %code) {
entry:
    %trunc = trunc i64 %code to i32
    call void @exit(i32 %trunc)
    unreachable
}

define linkonce_odr void @execute_system(i8* %cmd) {
entry:
    call i32 @system(i8* %cmd)
    ret void
}

define linkonce_odr i1 @file_exists(i8* %path) {
entry:
    %res = call i32 @access(i8* %path, i32 0)
    %cmp = icmp eq i32 %res, 0
    ret i1 %cmp
}

define linkonce_odr void @file_remove(i8* %path) {
entry:
    call i32 @remove(i8* %path)
    ret void
}

define linkonce_odr i64 @__length(i8* %str) {
entry:
    %cmp = icmp eq i8* %str, null
    %safe_str = select i1 %cmp, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %str
    %len = call i64 @strlen(i8* %safe_str)
    ret i64 %len
}

define linkonce_odr i64 @__char_at(i8* %str, i64 %idx) {
entry:
    %ptr = getelementptr inbounds i8, i8* %str, i64 %idx
    %val = load i8, i8* %ptr
    %res = zext i8 %val to i64
    ret i64 %res
}

define linkonce_odr i8* @__env_get(i8* %key) {
entry:
    %res = call i8* @getenv(i8* %key)
    %isnull = icmp eq i8* %res, null
    br i1 %isnull, label %is_null, label %is_ok
is_null:
    %empty = getelementptr inbounds [1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0
    ret i8* %empty
is_ok:
    ret i8* %res
}

define linkonce_odr i64 @__index_of(i8* %str, i8* %sub) {
entry:
    %cmp_str = icmp eq i8* %str, null
    %safe_str = select i1 %cmp_str, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %str
    %cmp_sub = icmp eq i8* %sub, null
    %safe_sub = select i1 %cmp_sub, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %sub
    %res = call i8* @strstr(i8* %safe_str, i8* %safe_sub)
    %isnull = icmp eq i8* %res, null
    br i1 %isnull, label %not_found, label %found
not_found:
    ret i64 -1
found:
    %p1 = ptrtoint i8* %res to i64
    %p2 = ptrtoint i8* %safe_str to i64
    %diff = sub i64 %p1, %p2
    ret i64 %diff
}

define linkonce_odr i8* @__substring(i8* %str, i64 %start, i64 %len) {
entry:
    %cmp = icmp eq i8* %str, null
    %safe_str = select i1 %cmp, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %str
    %sz_plus = add i64 %len, 1
    %mem = call i8* @malloc(i64 %sz_plus)
    %src_ptr = getelementptr inbounds i8, i8* %safe_str, i64 %start
    call i8* @strncpy(i8* %mem, i8* %src_ptr, i64 %len)
    %null_ptr = getelementptr inbounds i8, i8* %mem, i64 %len
    store i8 0, i8* %null_ptr
    ret i8* %mem
}

define linkonce_odr i8* @__reverse(i8* %str) {
entry:
    %cmp = icmp eq i8* %str, null
    %safe_str = select i1 %cmp, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.empty, i64 0, i64 0), i8* %str
    %len = call i64 @strlen(i8* %safe_str)
    %sz_plus = add i64 %len, 1
    %mem = call i8* @malloc(i64 %sz_plus)
    %isnull = icmp eq i64 %len, 0
    br i1 %isnull, label %end, label %cond
cond:
    %i = phi i64 [ 0, %entry ], [ %i_next, %body ]
    %cmp2 = icmp slt i64 %i, %len
    br i1 %cmp2, label %body, label %end
body:
    %i_rev = sub i64 %len, 1
    %i_src = sub i64 %i_rev, %i
    %src_ptr = getelementptr inbounds i8, i8* %safe_str, i64 %i_src
    %char = load i8, i8* %src_ptr
    %dst_ptr = getelementptr inbounds i8, i8* %mem, i64 %i
    store i8 %char, i8* %dst_ptr
    %i_next = add i64 %i, 1
    br label %cond
end:
    %null_ptr = getelementptr inbounds i8, i8* %mem, i64 %len
    store i8 0, i8* %null_ptr
    ret i8* %mem
}

define i32 @main(i32 %argc, i8** %argv) {
entry:
    store i32 %argc, i32* @__argc
    store i8** %argv, i8*** @__argv
    %my_str = alloca %struct.string_type
    ret i32 0
    ret i32 0
}
