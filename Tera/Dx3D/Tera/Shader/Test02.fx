float4x4 matWorld : World;
float4x4 matView : View;
float4x4 matProjection : Projection;
float    fTime : Time0_X;



struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

     Output.Position = mul( Input.Position, matWorld );
     Output.Position = mul( Output.Position, matView ); 
     Output.Position = mul( Output.Position, matProjection );
     
     Output.TexCoord = Input.TexCoord + float2(0, fTime * 0.2);
   
   return( Output );
   
}




texture DiffuseMap_Tex
<
   string ResourceName = "..\\objEx\\A_DistortrrrBall001_emis.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};


struct PS_INPUT
{
   float2 TexCoord : TEXCOORD0;

};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
   //float albedo.r;
   //float2 albedo.rg;
   //albedo.rg = albedo.xy;
   //if albedo is colorInfo, use rgba for Comfortable reading
   float c = ((albedo.r + albedo.g + albedo.b) / 3);
   return( float4(c, c, c, 1));
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

