/*
 ==============================================================================
 
 Ross Hoyt
 Attributes.h
 This class manages the attributes that the shaders use
 ==============================================================================
 */

#pragma once
#include "Vertex.h"

//==============================================================================
struct Attributes
{
    Attributes (OpenGLContext& openGLContext, OpenGLShaderProgram& shader)
    {
        position      = std::unique_ptr<OpenGLShaderProgram::Attribute> (createAttribute (openGLContext, shader, "position"));
        normal        = std::unique_ptr<OpenGLShaderProgram::Attribute> (createAttribute (openGLContext, shader, "normal"));
        sourceColour  = std::unique_ptr<OpenGLShaderProgram::Attribute> (createAttribute (openGLContext, shader, "sourceColour"));
        texureCoordIn = std::unique_ptr<OpenGLShaderProgram::Attribute> (createAttribute (openGLContext, shader, "texureCoordIn"));
    }
    
    void enable (OpenGLContext& openGLContext)
    {
        if (position != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (position->attributeID, 3, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, sizeof (Vertex), 0);
            openGLContext.extensions.glEnableVertexAttribArray (position->attributeID);
        }
        
        if (normal != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (normal->attributeID, 3, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 3));
            openGLContext.extensions.glEnableVertexAttribArray (normal->attributeID);
        }
        
        if (sourceColour != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (sourceColour->attributeID, 4, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 6));
            openGLContext.extensions.glEnableVertexAttribArray (sourceColour->attributeID);
        }
        
        if (texureCoordIn != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (texureCoordIn->attributeID, 2, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 10));
            openGLContext.extensions.glEnableVertexAttribArray (texureCoordIn->attributeID);
        }
    }
    
    void disable (OpenGLContext& openGLContext)
    {
        if (position != nullptr)       openGLContext.extensions.glDisableVertexAttribArray (position->attributeID);
        if (normal != nullptr)         openGLContext.extensions.glDisableVertexAttribArray (normal->attributeID);
        if (sourceColour != nullptr)   openGLContext.extensions.glDisableVertexAttribArray (sourceColour->attributeID);
        if (texureCoordIn != nullptr)  openGLContext.extensions.glDisableVertexAttribArray (texureCoordIn->attributeID);
    }
    
    std::unique_ptr<OpenGLShaderProgram::Attribute> position, normal, sourceColour, texureCoordIn;
    
private:
    static OpenGLShaderProgram::Attribute* createAttribute (OpenGLContext& openGLContext,
                                                            OpenGLShaderProgram& shader,
                                                            const char* attributeName)
    {
        if (openGLContext.extensions.glGetAttribLocation (shader.getProgramID(), attributeName) < 0)
            return nullptr;
        
        return new OpenGLShaderProgram::Attribute (shader, attributeName);
    }
};
