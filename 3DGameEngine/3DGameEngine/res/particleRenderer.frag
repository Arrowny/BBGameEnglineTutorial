#version 330                                                                        
                                                                                    
uniform sampler2D diffuse;                                                        
                                                                                    
in vec2 TexCoord;                                                                   
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(diffuse, TexCoord.xy);                                    
                                                                                    
    if (FragColor.r >= 0.9 && FragColor.g >= 0.9 && FragColor.b >= 0.9) {           
        discard;                                                                    
    }                                                                               
}