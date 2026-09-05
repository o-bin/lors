// ==========================================
// Modular Math Library - Mathematical Constants
// Subdirectory: core/
// ==========================================

algorithm get_pi_constant() -> precise
begin
    result 3.141592653589793;
end

algorithm get_e_constant() -> precise
begin
    result 2.718281828459045;
end

algorithm degrees_to_radians(deg : precise) -> precise
begin
    result deg * (get_pi_constant() / 180.0);
end
