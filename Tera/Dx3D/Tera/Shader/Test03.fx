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
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\TexturedCube.3ds";

float4x4 matWorld : World;
float4x4 matView : View;
float4x4 matProjection : ViewProjection;
float4   vLightPosition
<
   string UIName = "vLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 50.00, 500.00, 500.00, 1.00 );
float4   vViewPosition : ViewPosition;
float    fTime
<
   string UIName = "fTime";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.00 );

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float4 Normal : NORMAL;
   float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   //float4 Normal : NORMAL;
   float2 TexCoord : TEXCOORD0;
   float4 Diffuse : TEXCOORD1;
   float3 Reflection : TEXCOORD2;
   float3 ViewDirection : TEXCOORD3;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   Output.Position = mul( Input.Position, matWorld );
   
   float3 vLightDir = Output.Position.xyz - vLightPosition.xyz;
   
   Output.ViewDirection = normalize(Output.Position.xyz - vViewPosition.xyz);
   
   Output.Position = mul( Output.Position, matView );
   Output.Position = mul( Output.Position, matProjection );
   
   float3 vWorldNormal = mul(Input.Normal, matWorld);
   
   vLightDir = normalize(vLightDir);
   vWorldNormal = normalize(vWorldNormal);
   //float fSpecular = dot(Output.Reflection, -Output.ViewDirection);
   
   Output.Reflection = normalize(reflect(vLightDir, vWorldNormal));
   
   //fSpecular = pow(fSpecular, 20);
   
   float fDiffuse = dot(-vLightDir, vWorldNormal);
   Output.Diffuse.rgb = fDiffuse;
   Output.Diffuse.a = 1.0f;
   Output.TexCoord = Input.TexCoord + float2(fTime * 0.2, 0);
   
   return( Output );
}




texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

struct PS_INPUT
{
   //float4 Position : POSITION0;
   //float4 Normal : NORMAL;
   float2 TexCoord : TEXCOORD0;
   float4 Diffuse : TEXCOORD1;
   float3 Reflection : TEXCOORD2;
   float3 ViewDirection : TEXCOORD3; 
};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
   
   float3 diffuse = saturate(Input.Diffuse.xyz);
   float3 ref = normalize(Input.Reflection);
   float3 viewDir = normalize(Input.ViewDirection);
   float3 specular = 0.0f;
   if(diffuse.x > 0) 
   {
      specular = dot(ref, -viewDir);
      specular = pow(specular, 20);
   }
   
   float3 ambient = float3(0.1f, 0.1f, 0.1f);
   float3 color = ambient + diffuse + specular;
   color = color * albedo;
   
   return( float4(color, 1.0f) );
   
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

