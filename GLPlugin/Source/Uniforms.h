/*
 ==============================================================================
 
 Ross Hoyt
 Uniforms.h
 ==============================================================================
 */

#pragma once

//==============================================================================
// Class that manages the uniform values that the shaders use.
struct Uniforms
{
    Uniforms (OpenGLContext& openGLContext, OpenGLShaderProgram& shader)
    {
        projectionMatrix = std::unique_ptr<OpenGLShaderProgram::Uniform> (createUniform (openGLContext, shader, "projectionMatrix"));
        viewMatrix       = std::unique_ptr<OpenGLShaderProgram::Uniform> (createUniform (openGLContext, shader, "viewMatrix"));
        texture          = std::unique_ptr<OpenGLShaderProgram::Uniform> (createUniform (openGLContext, shader, "demoTexture"));
        lightPosition    = std::unique_ptr<OpenGLShaderProgram::Uniform> (createUniform (openGLContext, shader, "lightPosition"));
    }
    
    std::unique_ptr<OpenGLShaderProgram::Uniform> projectionMatrix, viewMatrix, texture, lightPosition;
    
private:
    static OpenGLShaderProgram::Uniform* createUniform (OpenGLContext& openGLContext,
                                                        OpenGLShaderProgram& shader,
                                                        const char* uniformName)
    {
        if (openGLContext.extensions.glGetUniformLocation (shader.getProgramID(), uniformName) < 0)
            return nullptr;
        
        return new OpenGLShaderProgram::Uniform (shader, uniformName);
    }
};
