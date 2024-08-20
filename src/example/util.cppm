module;
#include <fstream>
#include <vector>
#include <Framework/CubismFramework.hpp>
#include <GLFW/glfw3.h>
export module Util;

using namespace std;
using namespace Csm;

export vector<char> LoadFile(const char* path)
{
	ifstream in(path, ios::binary);
	in.seekg(0, ios::end);
	auto size = (int)in.tellg();
	in.seekg(0, ios::beg);
	vector<char> buff(size);
	in.read(buff.data(), size);
	return buff;
}

export class Timer final
{
	static double s_currentFrame;
	static double s_lastFrame;
	static double s_deltaTime;
public:
	static csmFloat32 GetDeltaTime() { return static_cast<csmFloat32>(s_deltaTime); }
	static void UpdateTime()
	{
		s_currentFrame = glfwGetTime();
		s_deltaTime = s_currentFrame - s_lastFrame;
		s_lastFrame = s_currentFrame;
	}
};

export namespace Constants
{
	constexpr csmFloat32 ViewScale = 1.0f;
	constexpr csmFloat32 ViewMaxScale = 2.0f;
	constexpr csmFloat32 ViewMinScale = 0.8f;
	constexpr csmFloat32 ViewLogicalLeft = -1.0f;
	constexpr csmFloat32 ViewLogicalRight = 1.0f;
	constexpr csmFloat32 ViewLogicalBottom = -1.0f;
	constexpr csmFloat32 ViewLogicalTop = -1.0f;
	constexpr csmFloat32 ViewLogicalMaxLeft = -2.0f;
	constexpr csmFloat32 ViewLogicalMaxRight = 2.0f;
	constexpr csmFloat32 ViewLogicalMaxBottom = -2.0f;
	constexpr csmFloat32 ViewLogicalMaxTop = 2.0f;
	const csmChar* MotionGroupIdle = "Idle";
	const csmChar* MotionGroupTapBody = "TapBody";
	const csmChar* HitAreaNameHead = "Head";
	const csmChar* HitAreaNameBody = "Body";
	constexpr csmInt32 PriorityNone = 0;
	constexpr csmInt32 PriorityIdle = 1;
	constexpr csmInt32 PriorityNormal = 2;
	constexpr csmInt32 PriorityForce = 3;
	constexpr csmBool MocConsistencyValidationEnable = true;
	constexpr csmBool DebugLogEnable = true;
	constexpr csmBool DebugTouchLogEnable = false;
	constexpr CubismFramework::Option::LogLevel CubismLoggingLevel = CubismFramework::Option::LogLevel_Verbose;
	constexpr csmInt32 RenderTargetWidth = 1900;
	constexpr csmInt32 RenderTargetHeight = 1000;
}

double Timer::s_currentFrame;
double Timer::s_lastFrame;
double Timer::s_deltaTime;