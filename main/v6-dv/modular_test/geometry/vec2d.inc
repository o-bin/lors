// ==========================================
// Modular Math Library - 2D Vector Operations
// Subdirectory: geometry/
// ==========================================

incorporate "../core/types.inc"
incorporate "../core/constants.inc"

algorithm vec2_create(x : precise, y : precise) -> Vector2D
begin
    result Vector2D(x, y);
end

algorithm vec2_add(v1 : Vector2D, v2 : Vector2D) -> Vector2D
begin
    result Vector2D(v1.x + v2.x, v1.y + v2.y);
end

algorithm vec2_sub(v1 : Vector2D, v2 : Vector2D) -> Vector2D
begin
    result Vector2D(v1.x - v2.x, v1.y - v2.y);
end

algorithm vec2_scale(v : Vector2D, factor : precise) -> Vector2D
begin
    result Vector2D(v.x * factor, v.y * factor);
end

algorithm vec2_dot(v1 : Vector2D, v2 : Vector2D) -> precise
begin
    result v1.x * v2.x + v1.y * v2.y;
end

algorithm vec2_mag_sq(v : Vector2D) -> precise
begin
    result v.x * v.x + v.y * v.y;
end

algorithm vec2_mag(v : Vector2D) -> precise
begin
    datum sq : precise = vec2_mag_sq(v);
    result root(sq);
end

algorithm vec2_dist(v1 : Vector2D, v2 : Vector2D) -> precise
begin
    datum diff : Vector2D = vec2_sub(v1, v2);
    result vec2_mag(diff);
end
