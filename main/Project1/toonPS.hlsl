//ピクセルシェーダー

#include "common.hlsl"	//必ずインクルード

//
//inは入力されてくるデーター
//outは出力するデータ
//

Texture2D g_Texture : register(t0);

SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);//テクスチャを取得
	outDiffuse.a *= In.Diffuse.a; //α値の処理

	float light = -dot(normal.xyz, Light.Direction.xyz);//光源計算

	//プログラム版 明るさをセル塗り風に変換 if文でlightの値を3段階に調整
	if (light > 0.6) 
		light = 1.0;
	else if (light > 0.4)
		light = 0.8;
	else
		light = 0.6;
	outDiffuse.rgb *= saturate(In.Diffuse.rgb * light); //テクスチャ＊頂点色＊明るさ

	//エッジの作成
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //視線ベクトルを作る
	eyev = normalize(eyev); //視線ベクトルを正規化する
	float d = dot(eyev, normal.xyz); //法線と視線ベクトルの内積
	if (d > -0.3) //dの値を判定
	{
		outDiffuse.rgb *= 0.2; //適当な閾値で明度を落とす
	}
}