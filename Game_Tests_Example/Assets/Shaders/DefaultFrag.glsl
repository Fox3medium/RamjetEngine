#version 330 core

layout(location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	vec2 mask_uv;
	float tid;
	float mid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	vec4 texColor = fs_in.color;
	vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}
	if (fs_in.mid > 0.0)
	{
		int mid = int(fs_in.mid - 0.5);
		maskColor = texture(textures[mid], fs_in.mask_uv);
	}
	color = texColor * maskColor; // vec4(1.0 - maskColor.x, 1.0 - maskColor.y, 1.0 - maskColor.z, 1.0);
};
