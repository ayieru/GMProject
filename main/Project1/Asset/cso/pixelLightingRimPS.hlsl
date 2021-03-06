#include "common.hlsl"

Texture2D g_Texture : register(t0);

SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal); //ピクセルの法線を正規化
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz) * 0.5; //光源計算をする

	//テクスチャのピクセル色を取得
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light; //明るさを乗算
	outDiffuse.a *= In.Diffuse.a; //αに明るさは関係ないので別計算

	//カメラからピクセルへ向かうベクトル
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化する

	//光の反射ベクトルを計算
	float3 halfv = eyev + Light.Direction.xyz;
	halfv = normalize(halfv); //正規化する

	float specular = -dot(halfv, normal.xyz); //鏡面反射の計算
	specular = saturate(specular); //値をサチュレート

	specular = pow(specular, 30); //ここでは３０乗してみる
	outDiffuse.rgb += specular;//スペキュラ値をデフューズとして足しこむ

	//リムライト
	float rim = dot(eyev, normal.xyz) + 1.0f;
	rim = saturate(rim);
	rim = pow(rim, 3) * 2.0f;

	outDiffuse.rgb += rim;
}