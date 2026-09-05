// ==========================================
// Modular Math Library - Types & Structures
// Subdirectory: core/
// ==========================================

structure Vector2D
begin
    datum x : precise;
    datum y : precise;
end

structure Vector3D
begin
    datum x : precise;
    datum y : precise;
    datum z : precise;
end

structure StatsResult
begin
    datum count : whole;
    datum min_val : precise;
    datum max_val : precise;
    datum mean : precise;
    datum variance : precise;
    datum std_dev : precise;
end
