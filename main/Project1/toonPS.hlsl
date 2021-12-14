//�s�N�Z���V�F�[�_�[

#include "common.hlsl"	//�K���C���N���[�h

//
//in�͓��͂���Ă���f�[�^�[
//out�͏o�͂���f�[�^
//

Texture2D g_Texture : register(t0);

SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);//�e�N�X�`�����擾
	outDiffuse.a *= In.Diffuse.a; //���l�̏���

	float light = -dot(normal.xyz, Light.Direction.xyz);//�����v�Z

	//�v���O������ ���邳���Z���h�蕗�ɕϊ� if����light�̒l��3�i�K�ɒ���
	if (light > 0.6) 
		light = 1.0;
	else if (light > 0.4)
		light = 0.8;
	else
		light = 0.6;
	outDiffuse.rgb *= saturate(In.Diffuse.rgb * light); //�e�N�X�`�������_�F�����邳

	//�G�b�W�̍쐬
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //�����x�N�g�������
	eyev = normalize(eyev); //�����x�N�g���𐳋K������
	float d = dot(eyev, normal.xyz); //�@���Ǝ����x�N�g���̓���
	if (d > -0.3) //d�̒l�𔻒�
	{
		outDiffuse.rgb *= 0.2; //�K����臒l�Ŗ��x�𗎂Ƃ�
	}
}