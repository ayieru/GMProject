//���_�V�F�[�_�[

#include "common.hlsl"	//�K���C���N���[�h

//
//in�͓��͂���Ă���f�[�^�[
//out�͏o�͂���f�[�^
//
void main(in VS_IN In, out PS_IN Out)
{
	//�P���_���̃f�[�^���󂯎��A�������āA�o�͂���

	//���_�ϊ����� �K���K�v
	matrix	wvp;						//�s��ϐ����쐬
	wvp = mul(World, View);				//wvp = ���[���h�s�񁖃J�����s��
	wvp = mul(wvp, Projection);			//wvp = wvp *�v���W�F�N�V�����s��
	Out.Position = mul(In.Position, wvp); //���_��ϊ����ďo��

	float4 worldNormal, normal; //�@�������[���h�s��ŉ�]
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal); //�ϊ������@���𐳋K��
	Out.Normal = worldNormal; //���[���h�ϊ������@�����o��

	//���̑��o��
	Out.Diffuse = In.Diffuse;
	Out.TexCoord = In.TexCoord;

	//���[���h�ϊ��������_���W���o��
	Out.WorldPosition = mul(In.Position, World);

}