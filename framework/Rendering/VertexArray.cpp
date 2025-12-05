#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_vertexArrayID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

// Adds new VertexBuffer and sets the attribute pointer for the BufferAttributes
void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
{
	VertexBuffers.push_back(vertexBuffer);
	vertexBuffer->Bind();
	SetVertexAttributePointer(VertexBuffers.size() - 1);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
	IdxBuffer = indexBuffer;
}

// Check if the index is for a vaild buffer and enables it
void VertexArray::EnableVertexArray(GLuint i)
{
	int numberOfBuffers = VertexBuffers.size();

	for (auto var : VertexBuffers)
	{
		numberOfBuffers += var->GetLayout().GetAttributes().size();
	}

	if (i >= 0 && i < numberOfBuffers)
	{
		glEnableVertexAttribArray(i);
	}
}

void VertexArray::SetVertexAttributePointer(GLuint i)
{
	ASSERT(i >= 0 && i < VertexBuffers.size(), "Index to set Vertex Attribute Data is out of range.");

	BufferLayout layout = VertexBuffers[i]->GetLayout();

	std::vector<BufferAttribute> attributes = layout.GetAttributes();
	// Sets the vertex attribute pointer for each BufferAttribute
	for (GLuint j = 0; j < attributes.size(); j++)
	{
		BufferAttribute attribute = attributes[j];
		GLuint index = i + j; // Index for the vertex attribute array

		EnableVertexArray(index);
		glVertexAttribPointer(index, ShaderDataTypeComponentCount(attribute.Type), ShaderDataTypeToOpenGLBaseType(attribute.Type), attribute.Normalized, layout.GetStride(), reinterpret_cast<void *>(static_cast<uintptr_t>(attribute.Offset)));
	}
}