//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Cube.x";

//float4x4 matViewProjection;
float4x4 matWorld : World;
float4x4 matView : View;
float4x4 matProjection : Projection;
float    fTime;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
   //FVFô| L$   
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
     Output.TexCoord = Input.TexCoord + float2(fTime * 0.2, 0);
   
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
   //if colorInfo, use rgba for Comfortable reading
   //float c = ((albedo.r + albedo.g + albedo.b) / 3);
   return( float4(albedo.r, albedo.g, albedo.b, albedo.a));
   //ø$À” =@  Ì| 8œä
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

