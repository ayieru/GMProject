//頂点シェーダー

#include "common.hlsl"	//必ずインクルード

//
//inは入力されてくるデーター
//outは出力するデータ
//
void main(in VS_IN In, out PS_IN Out)
{
	//１頂点分のデータを受け取り、処理して、出力する

	//頂点変換処理 必ず必要
	matrix	wvp;						//行列変数を作成
	wvp = mul(World, View);				//wvp = ワールド行列＊カメラ行列
	wvp = mul(wvp, Projection);			//wvp = wvp *プロジェクション行列
	Out.Position = mul(In.Position, wvp); //頂点を変換して出力

	float4 worldNormal, normal; //法線をワールド行列で回転
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal); //変換した法線を正規化
	Out.Normal = worldNormal; //ワールド変換した法線を出力

	//その他出力
	Out.Diffuse = In.Diffuse;
	Out.TexCoord = In.TexCoord;

	//ワールド変換した頂点座標を出力
	Out.WorldPosition = mul(In.Position, World);

}