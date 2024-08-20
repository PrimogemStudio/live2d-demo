module;
#include <Framework/CubismModelSettingJson.hpp>
#include <Framework/Model/CubismUserModel.hpp>
#include <string>
#include <functional>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <Framework/Physics/CubismPhysics.hpp>
export module Module;

using namespace Live2D::Cubism::Framework;

class TextureManager final
{
public:
	struct TextureInfo
	{
		GLuint id;
		int width;
		int height;
		std::string fileName;
	};
	csmVector<TextureInfo*> textures;

	TextureManager();
	~TextureManager();
	TextureInfo* CreateTextureFromPngFile(const std::string& fileName);
	void ReleaseTextures();
	void ReleaseTexture(csmUint32 textureId);
	void ReleaseTexture(const std::string& fileName);
	TextureInfo* GetTextureInfoById(GLuint textureId) const;

	static inline unsigned int PreMultiply(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		return static_cast<unsigned>(red * (alpha + 1) >> 8 | green * (alpha + 1) >> 8 << 8 | blue * (alpha + 1) >> 8 << 16 | alpha << 24);
	}
};

export class CustomModel final : public CubismUserModel
{
	std::string ModelDirName;
	std::string CurrentModelDirectory;
	csmFloat32 UserTimeSeconds;
	csmVector<CubismIdHandle> EyeBlinkIds;
	csmMap<csmString, ACubismMotion*> Motions;
	csmMap<csmString, ACubismMotion*> Expressions;
	TextureManager* TextureManager;
	const CubismId* AngleX;
	const CubismId* AngleY;
	const CubismId* AngleZ;
	const CubismId* BodyAngleX;
	const CubismId* EyeBallX;
	const CubismId* EyeBallY;

	std::string MakeAssetPath(const std::string& assetFileName);
	void SetAssetDirectory(const std::string& path);
	void LoadAsset(const std::string& file, const std::function<void(csmByte*, csmSizeInt)>& callback);
	void ReleaseModelSetting();
	void Draw(CubismMatrix44& matrix);
	void ModelParamUpdate();
	void SetupTextures();
	void PreloadMotionGroup(const csmChar* group);
public:
	CustomModel(const std::string& modelDirectoryName, const std::string& currentModelDirectory);
	~CustomModel() override;
	void SetupModel();
	void ModelOnUpdate(GLFWwindow* window);
	csmBool HitTest(const csmChar* hitAreaName, csmFloat32 x, csmFloat32 y);
	CubismModelSettingJson* ModelJson;
	CubismMotionQueueEntryHandle StartMotion(const csmChar* group, csmInt32 no, csmInt32 priority, ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = nullptr);
};