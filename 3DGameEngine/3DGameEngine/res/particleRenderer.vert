#version 400

layout (location = 0) in int Type;                                                
layout (location = 1) in vec3 Position; 

out int Type0;                                             
                                                                        
void main()                                                                         
{                                                                                   
    gl_Position = vec4(Position, 1.0);  
	Type0 = Type;                                        
}     