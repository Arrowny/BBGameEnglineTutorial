#version 330

layout (location = 0) in vec3 Position;                                             
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = vec4(Position, 1.0);   
	//gl_Position = vec4(0.0,0.0,0.0,1.0);                                           
}     