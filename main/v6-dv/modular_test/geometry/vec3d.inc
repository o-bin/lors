// ==========================================
// Modular Math Library - 3D Vector Operations
// Subdirectory: geometry/
// ==========================================

incorporate "../core/types.inc"

algorithm vec3_create(x : precise, y : precise, z : precise) -> Vector3D
begin
    result Vector3D(x, y, z);
end

algorithm vec3_add(v1 : Vector3D, v2 : Vector3D) -> Vector3D
begin
    result Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
end

algorithm vec3_sub(v1 : Vector3D, v2 : Vector3D) -> Vector3D
begin
    result Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
end

algorithm vec3_scale(v : Vector3D, factor : precise) -> Vector3D
begin
    result Vector3D(v.x * factor, v.y * factor, v.z * factor);
end

algorithm vec3_dot(v1 : Vector3D, v2 : Vector3D) -> precise
begin
    result v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
end

algorithm vec3_cross(v1 : Vector3D, v2 : Vector3D) -> Vector3D
begin
    datum cx : precise = v1.y * v2.z - v1.z * v2.y;
    datum cy : precise = v1.z * v2.x - v1.x * v2.z;
    datum cz : precise = v1.x * v2.y - v1.y * v2.x;
    result Vector3D(cx, cy, cz);
end

algorithm vec3_mag_sq(v : Vector3D) -> precise
begin
    result v.x * v.x + v.y * v.y + v.z * v.z;
end

algorithm vec3_mag(v : Vector3D) -> precise
begin
    datum sq : precise = vec3_mag_sq(v);
    result root(sq);
end
