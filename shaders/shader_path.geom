#version 430
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main()
{
    // Pass through the input geometry to the output without modifying it
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();
}