#version 400                                                                        
                                                                                    
uniform sampler2D diffuse;                                                        
                                                                                    
in vec2 TexCoord;                                                                   
out vec4 FragColor;                                                                 
             
uniform vec3 color;
                                                                   
void main()                                                                         
{              
	vec4 color0 = vec4( color, 1.0 );                                                              
    FragColor = texture2D(diffuse, TexCoord.xy) * color0;                                    
     
		                                                                            
 //   if (FragColor.r >= 0.9 && FragColor.g >= 0.9 && FragColor.b >= 0.9) {           
  //      discard;                                                                    
  //  }                                                                               
}