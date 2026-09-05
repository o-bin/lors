// graphic.inc - Lors Graphics Library Experiment

// OpenGL Constants
datum GL_COLOR_BUFFER_BIT : whole = 16384;
datum GL_DEPTH_BUFFER_BIT : whole = 256;

// OpenGL Function Declarations (External)
algorithm glClear(mask : whole) -> void;
algorithm glClearColor(r : precise, g : precise, b : precise, a : precise) -> void;
algorithm glFlush() -> void;

// Higher level abstractions
algorithm graphics_init_color(r : precise, g : precise, b : precise) -> void
begin
    glClearColor(r, g, b, 1.0);
end

algorithm graphics_clear_screen() -> void
begin
    glClear(GL_COLOR_BUFFER_BIT);
end
