#include "VertexArray.h"

VertexArray::VertexArray() {

	glGenVertexArrays(1, &ID);
}

void VertexArray::linkAttrib(VertexBuffer& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {

	vertexBuffer.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vertexBuffer.Unbind();


}

void VertexArray::Bind(){

	glBindVertexArray(ID);
}

void VertexArray::Unbind(){

	glBindVertexArray(0);
}

void VertexArray::Delete() {

	glDeleteVertexArrays(1, &ID);

}