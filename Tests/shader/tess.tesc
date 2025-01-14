#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(vertices = 3) out;

void main(void) {
  const int inner = 3;
  const int outer = 2;

  if(gl_InvocationID==0) {
    gl_TessLevelInner[0] = inner;
    gl_TessLevelInner[1] = inner;

    gl_TessLevelOuter[0] = outer;
    gl_TessLevelOuter[1] = outer;
    gl_TessLevelOuter[2] = outer;
    gl_TessLevelOuter[3] = outer;
    }

  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  }
