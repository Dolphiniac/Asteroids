#include "Engine/Renderer/UniformBlock.hpp"
#include "Engine/Core/EngineSystemManager.hpp"
#include "Engine/Renderer/OpenGLExtensions.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/Math/Matrix44.hpp"
#include "Engine/Core/StringUtils.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"


//-----------------------------------------------------------------------------------------------
GLuint UniformBlock::s_currentBindingPoint = 0;
std::map<std::string, UniformBlock*> UniformBlock::s_uniformBlocks;


//-----------------------------------------------------------------------------------------------
void UniformBlock::GenerateBuffer()
{
	size_t totalSize = 0;
	for each (auto ps in m_posAndSize)
	{
		totalSize += std::get<1>(ps.second);
	}

	m_uboID = The.Renderer->CreateRenderBuffer(nullptr, 1, totalSize, R_DYNAMIC_DRAW, R_UNIFORM_BUFFER);
}


//-----------------------------------------------------------------------------------------------
std::tuple<int, int> UniformBlock::GetPosAndSize(const std::string& fieldName) const
{
	auto fieldIter = m_posAndSize.find(fieldName);
	GUARANTEE_OR_DIE(fieldIter != m_posAndSize.end(), Stringf("Field name %s is not an existing field in uniform block %s", fieldName.c_str(), m_name.c_str()));

	return fieldIter->second;
}


//-----------------------------------------------------------------------------------------------
int UniformBlock::GetTotalOffset() const
{
	int result = 0;

	for each (auto ps in m_posAndSize)
	{
		//Add the size of each existing element to the total offset
		result += std::get<1>(ps.second);	
	}

	return result;
}


//-----------------------------------------------------------------------------------------------
void UniformBlock::SetField(const std::string& blockName, const std::string& fieldName, void* toSet)
{
	UniformBlock* block = GetBlock(blockName);
	std::tuple<int, int> posAndSize = block->GetPosAndSize(fieldName);

	glBindBufferBase(GL_UNIFORM_BUFFER, block->m_bindingPoint, block->m_uboID);
	glBufferSubData(GL_UNIFORM_BUFFER, std::get<0>(posAndSize), std::get<1>(posAndSize), toSet);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}


//-----------------------------------------------------------------------------------------------
UniformBlock* UniformBlock::GetBlock(const std::string& blockName)
{
	auto blockIter = s_uniformBlocks.find(blockName);
	GUARANTEE_OR_DIE(blockIter != s_uniformBlocks.end(), Stringf("Block name %s is not an existing uniform block", blockName.c_str()));
	
	return blockIter->second;
}


//-----------------------------------------------------------------------------------------------
void UniformBlock::InitializeUniformBlocks()
{
	std::string currName;
	UniformBlock* currBlock;

	currName = "GlobalMatrices";
	currBlock = new UniformBlock(currName);
	currBlock->PushBackMat4("gView");
	currBlock->PushBackMat4("gProj");
	currBlock->GenerateBuffer();
	s_uniformBlocks[currName] = currBlock;

	currName = "Time";
	currBlock = new UniformBlock(currName);
	currBlock->PushBackFloat("gTime");
	currBlock->GenerateBuffer();
	s_uniformBlocks[currName] = currBlock;

	currName = "EffectState";
	currBlock = new UniformBlock(currName);
	currBlock->PushBackInt("gEffectState");
	currBlock->GenerateBuffer();
	s_uniformBlocks[currName] = currBlock;
}


//-----------------------------------------------------------------------------------------------
void UniformBlock::DestroyUniformBlocks()
{
	for (std::pair<const std::string, UniformBlock*>& p : s_uniformBlocks)
	{
		delete p.second;
	}
	s_uniformBlocks.clear();
}