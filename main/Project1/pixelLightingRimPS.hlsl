#include "common.hlsl"

Texture2D g_Texture : register(t0);

SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal); //�s�N�Z���̖@���𐳋K��
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz) * 0.5; //�����v�Z������

	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light; //���邳����Z
	outDiffuse.a *= In.Diffuse.a; //���ɖ��邳�͊֌W�Ȃ��̂ŕʌv�Z

	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K������

	//���̔��˃x�N�g�����v�Z
	float3 halfv = eyev + Light.Direction.xyz;
	halfv = normalize(halfv); //���K������

	float specular = -dot(halfv, normal.xyz); //���ʔ��˂̌v�Z
	specular = saturate(specular); //�l���T�`�����[�g

	specular = pow(specular, 30); //�����ł͂R�O�悵�Ă݂�
	outDiffuse.rgb += specular;//�X�y�L�����l���f�t���[�Y�Ƃ��đ�������

	//�������C�g
	float rim = dot(eyev, normal.xyz) + 1.0f;
	rim = saturate(rim);
	rim = pow(rim, 3) * 2.0f;

	outDiffuse.rgb += rim;
}