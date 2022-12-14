
#include "headerfiles/camera.h"



void SimpleCamera::MoveForward(float Scale)
{
	ForwardScale = Scale;
}

GLuint SimpleCamera::getPolygonMode()
{
	return polygonMode;
}


void SimpleCamera::setPolygonMode()
{

	if (isWireframe == true)
	{
		polygonMode = GL_FILL;

	}else{
		polygonMode = GL_LINE;
	}
	isWireframe = !isWireframe;
}




void SimpleCamera::MoveRight(float Scale)
{
	RightScale = Scale;
}

void SimpleCamera::MouseMove(float X, float Y)
{
	if (bEnableMouseMovement)
	{
		glm::vec2 CurrentCursor{ X, Y };
		glm::vec2 Delta = (CurrentCursor - PreviousCursor) / 10.0f;

		if (glm::length(Delta) < 5.0f)
		{
			glm::vec3 Right = glm::cross(Direction, Up);

			glm::mat4 RotationRight = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-Delta.y), Right);
			glm::mat4 RotationUp = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-Delta.x), Up);
			glm::mat4 Rotation = RotationRight * RotationUp;

			Up = Rotation * glm::vec4{ Up, 0.0f };
			Direction = Rotation * glm::vec4{ Direction, 0.0f };
		}

		PreviousCursor = CurrentCursor;
	}
}

void SimpleCamera::Update(float DeltaTime)
{
	glm::vec3 Right = glm::cross(Direction, Up);

	Location += Direction * ForwardScale * DeltaTime;
	Location += Right * RightScale * DeltaTime;
}

glm::mat4 SimpleCamera::GetView()
{
	return glm::lookAt(Location, Location + Direction, Up);
}

glm::mat4 SimpleCamera::GetViewProjection()
{
	glm::mat4 View = GetView();
	glm::mat4 Projection = glm::perspective(FieldOfView, AspectRatio, Near, Far);
	return Projection * View;
}


